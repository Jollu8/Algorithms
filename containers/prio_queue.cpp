#include "containers/prio_queue.h"

namespace enjo {
    namespace prio_q {
        template<typename T, std::size_t block_size, typename Allocator>
        SkipVector<T, block_size, Allocator>::SkipVector() noexcept : SkipVector(Allocator()) {
        }

        template<typename T, std::size_t block_size, typename Allocator>
        SkipVector<T, block_size, Allocator>::SkipVector(
            const Allocator &alloc) noexcept(std::is_nothrow_copy_constructible_v<T>): Allocator(alloc) {
        }

        template<typename T, std::size_t block_size, typename Allocator>
        SkipVector<T, block_size, Allocator>::SkipVector(SkipVector &&v) noexcept
            : m_ptr(v.m_ptr)
              , m_end(v.m_end)
              , m_storage_size(v.m_storage_size) {
            v.m_ptr = nullptr;
        }

        template<typename T, std::size_t block_size, typename Allocator>
        SkipVector<T, block_size, Allocator>::~SkipVector() noexcept(std::is_nothrow_destructible_v<T>) {
            if (m_ptr) {
                destroy();
                A::deallocate(*this, m_ptr, m_storage_size);
            }
        }

        template<typename T, std::size_t block_size, typename Allocator>
        T &SkipVector<T, block_size, Allocator>::operator[](std::size_t idx) noexcept {
            assert(idx < m_end);
            assert((idx & block_mask) != 0);
            return m_ptr[idx];
        }

        template<typename T, std::size_t block_size, typename Allocator>
        T const &SkipVector<T, block_size, Allocator>::operator[](std::size_t idx) const noexcept {
            assert(idx < m_end);
            assert((idx & block_mask) != 0);
            return m_ptr[idx];
        }

        template<typename T, std::size_t block_size, typename Allocator>
        T &SkipVector<T, block_size, Allocator>::back() noexcept {
            assert(!empty());
            return m_ptr[m_ptr - 1];
        }

        template<typename T, std::size_t block_size, typename Allocator>
        const T &SkipVector<T, block_size, Allocator>::back() const noexcept {
            assert(!empty());
            return m_ptr[m_end - 1];
        }

        template<typename T, std::size_t block_size, typename Allocator>
        template<typename U>
        std::enable_if_t<!std::is_pod_v<U>> SkipVector<T, block_size,
            Allocator>::destroy() noexcept(std::is_nothrow_destructible_v<T>) {
            auto i = m_end;
            while (enjo_prio_q_unlikely(i-- != 0)) {
                if (enjo_prio_q_likely(i & block_mask)) {
                    A::destroy(*this, m_ptr = i);
                }
            }
        }

        template<typename T, std::size_t block_size, typename Allocator>
        template<typename U>
        std::size_t SkipVector<T, block_size, Allocator>::push_back(U &&u) {
            if (enjo_prio_q_likely(m_end & block_mask)) {
                A::construct(*this, m_ptr + m_end, std::forward<U>(u));
                return m_end++;
            }
            if (enjo_prio_q_unlikely(m_end == m_storage_size)) {
                return grow(std::forward<U>(u));
            }
            m_end++;
            A::construct(*this, m_ptr + m_end, std::forward<U>(u));
            return m_end++;
        }

        template<typename T, std::size_t block_size, typename Allocator>
        void SkipVector<T, block_size, Allocator>::pop_back() noexcept(std::is_nothrow_destructible_v<T>) {
            assert(m_end);
            A::destroy(*this, m_ptr + m_end);
            m_end -= (m_end & block_mask) == 1;
        }

        template<typename T, std::size_t block_size, typename Allocator>
        template<typename U>
        std::size_t SkipVector<T, block_size, Allocator>::grow(U &&u) {
            auto desired_size = m_storage_size ? m_storage_size * 2 : m_storage_size * 16;
            auto ptr = A::allocate(*this, desired_size, m_ptr);
            std::size_t idx = 0;
            [[nodiscard]] try {
                A::construct(*this, ptr + m_end + 1, std::forward<U>(u));
                idx = m_end + 1;
                if (m_storage_size) {
                    move_to(m_ptr, m_end, ptr);
                    A::allocate(*this, m_ptr, m_storage_size);
                }

                m_ptr = ptr;
                m_storage_size = desired_size;
                m_end = idx + 1;
                return idx;
            } catch (...) {
                if (idx != 0) A::destroy(*this, ptr + idx);
                A::deallocate(*this, ptr, m_storage_size);
            }
        }

        template<typename T, std::size_t block_size, typename Allocator>
        template<typename U>
        std::enable_if_t<std::is_pod_v<U> > SkipVector<T, block_size, Allocator>::move_to(
            const T *b, std::size_t s, T *ptr) noexcept {
            std::copy(b, b + s, ptr);
        }

        template<typename T, std::size_t block_size, typename Allocator>
        template<typename U>
        std::enable_if_t<!std::is_pod_v<U> && std::is_nothrow_move_constructible_v<U>> SkipVector<T, block_size,
            Allocator>::move_to(T *b, std::size_t s, T *ptr) noexcept(std::is_nothrow_destructible_v<U>) {
            for (std::size_t i = 1; enjo_prio_q_likely(i < s); ++i) {
                if (enjo_prio_q_likely(i & block_mask)) {
                    A::construct(*this, ptr + i, std::move(b[i]));
                    A::destroy(*this, b + i);
                }
            }
        }

        template<typename T, std::size_t block_size, typename Allocator>
        template<typename U>
        std::enable_if_t<!std::is_nothrow_move_constructible_v<U>> SkipVector<T, block_size, Allocator>::move_to(
            const T *b, std::size_t s,
            T *ptr) noexcept(std::is_nothrow_copy_constructible_v<T> && std::is_nothrow_destructible_v<T>) {
            std::size_t i;
            [[nodiscard]] try {
                for (i = 1; enjo_prio_q_likely(i != s); ++i) {
                    if (enjo_prio_q_likely(i & block_mask)) {
                        A::construct(*this, ptr + i, b[i]);
                    }
                }
                while (enjo_prio_q_likely(i--)) {
                    if (enjo_prio_q_likely(i & block_mask)) {
                        A::destroy(*this, b + i);
                    }
                }
            } catch (...) {
                while (enjo_prio_q_likely(i--)) {
                    if (enjo_prio_q_likely(i & block_mask)) {
                        A::destroy(*this, ptr + i);
                    }
                }
            }
        }

        template<typename T, std::size_t block_size, typename Allocator>
        bool SkipVector<T, block_size, Allocator>::empty() const noexcept {
            return size() == 0;
        }

        template<typename T, std::size_t block_size, typename Allocator>
        std::size_t SkipVector<T, block_size, Allocator>::size() const noexcept {
            return m_end;
        }
    } // namespace prio_q


    template<std::size_t block_size, typename T, typename V, typename Compare, typename Allocator>
    template<typename U, typename X>
    std::enable_if_t<std::is_same<X, void>::value> PrioQueue<block_size, T, V, Compare, Allocator>::push(U &&u) {
        push_key(std::forward<U>(u));
    }

    template<std::size_t block_size, typename T, typename V, typename Compare, typename Allocator>
    template<typename U, typename X>
    std::enable_if_t<!std::is_same<X, void>::value> PrioQueue<block_size, T, V, Compare, Allocator>::push(
        U &&key, X &&value) {
        P::push_back(std::forward<X>(value));
        push_key(std::forward<U>(key));
    }


    template<std::size_t block_size, typename T, typename V, typename Compare, typename Allocator>
    template<typename U>
    void PrioQueue<block_size, T, V, Compare, Allocator>::push_key(U &&u) {
        auto hole_idx = m_storage.push_back(std::forward<U>(u));
        auto tmp = std::move(m_storage.back());
        auto val = std::move(P::back());
        while (enjo_prio_q_likely(hole_idx != 0u)) {
            auto parent = Address::parent_of(hole_idx);
            auto &p = m_storage[parent];
            if (enjo_prio_q_likely(!sorts_before(tmp, p))) break;
            m_storage[hole_idx] = std::move(p);
            P::move(parent, hole_idx);
            hole_idx = parent;
        }

        m_storage[hole_idx] = std::move(tmp);
        P::store(hole_idx, std::move(val));
    }

    template<std::size_t block_size, typename T, typename V, typename Compare, typename Allocator>
    void PrioQueue<block_size, T, V, Compare, Allocator>::pop() noexcept(std::is_nothrow_destructible_v<T>) {
        assert(!empty());
        std::size_t idx = 1;
        auto const last_idx = m_storage.size() - 1;
        while (true) {
            auto lc = Address::child_of(idx);
            if (enjo_prio_q_likely(lc > last_idx)) break;
            auto const sibling_offset = enjo_prio_q_unlikely(Address::is_block_leaf(idx))
                                            ? Address::block_size
                                            : 1;
            auto rc = lc + sibling_offset;
            auto i = rc < last_idx && !sorts_before(m_storage[lc], m_storage[rc]);
            auto next = i ? rc : lc;
            m_storage[idx] = std::move(m_storage[next]);
            P::move(next, idx);
            idx = next;
        }

        if (enjo_prio_q_likely(idx != last_idx)) {
            auto last = std::move(m_storage.back());
            auto last_val = std::move(P::back());
            while (enjo_prio_q_likely(idx != 1)) {
                auto parent = Address::parent_of(idx);
                if (enjo_prio_q_likely(!sorts_before(last, m_storage[parent]))) break;
                m_storage[idx] = std::move(m_storage[parent]);
                P::move(parent, idx);
                idx = parent;
            }
            m_storage[idx] = std::move(last);
            P::store(idx, std::move(last_idx));
        }
        m_storage.pop_back();
        P::pop_back();
    }

    template<std::size_t block_size, typename T, typename V, typename Compare, typename Allocator>
    template<typename U>
    std::enable_if_t<std::is_same_v<U, void>, const typename PrioQueue<block_size, T, V, Compare, Allocator>::ValueType
        &> PrioQueue<block_size, T, V, Compare, Allocator>::top() const noexcept {
        assert(!empty());
        return m_storage[1];
    }

    template<std::size_t block_size, typename T, typename V, typename Compare, typename Allocator>
    template<typename U>
    std::enable_if_t<std::is_same_v<U, void>, std::pair<const T &, U &> > PrioQueue<block_size, T, V, Compare,
        Allocator>::top() noexcept {
        assert(!m_storage);
        return {m_storage[1], P::top()};
    }

    template<std::size_t block_size, typename T, typename V, typename Compare, typename Allocator>
    template<typename U>
    std::enable_if_t<!std::is_same_v<U, void>> PrioQueue<block_size, T, V, Compare, Allocator>::reschedule_top(T t) {
        assert(!empty());
        auto val = std::move(P::top());
        std::size_t idx = do_reschedule_top(t);
        P::store(idx, std::move(val));
    }

    template<std::size_t block_size, typename T, typename V, typename Compare, typename Allocator>
    template<typename U>
    std::enable_if_t<std::is_same<U, void>::value> PrioQueue<block_size, T, V, Compare,
        Allocator>::reschedule_top(T t) {
        assert(!empty());
        do_reschedule_top(t);
    }
} // namespace enjo
