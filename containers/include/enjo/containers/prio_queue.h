/// @author https://github.com/rollbear/prio_queue

/// B-heap priority queue

#pragma once

#include <cstddef>
#include <memory>
#include <type_traits>
#include <vector>
#include <cassert>
#include <tools/defs.h>

#ifdef __GNUC__
#define enjo_prio_q_likely(x)       __builtin_expect(!!(x), 1)
#define enjo_prio_q_unlikely(x)     __builtin_expect(!!(x), 0)
#else
  #define enjo_prio_q_likely(x) x
  #define enjo_prio_q_unlikely(x) x
#endif

namespace enjo {
    namespace prio_q {
        template<typename T, std::size_t block_size, typename Allocator = std::allocator<T>>
        class SkipVector : public Allocator {
            using A = std::allocator_traits<Allocator>;
            static constexpr std::size_t block_mask = block_size - 1;

        public:
            SkipVector() noexcept;

            explicit SkipVector(const Allocator &alloc) noexcept (std::is_nothrow_copy_constructible_v<T>);

            SkipVector(SkipVector &&) noexcept;

            ~SkipVector() noexcept(std::is_nothrow_destructible_v<T>);

            T &operator[](std::size_t idx) noexcept {
                assert(idx < m_end);
                assert((idx & block_mask) != 0);
                return m_ptr[idx];
            }

            const T &operator[](std::size_t idx) const noexcept;

            T &back() noexcept {
                assert(!empty());
                return m_ptr[m_end - 1];
            }


            const T &back() const noexcept;

            template<typename U>
            std::size_t push_back(U &&u);

            void pop_back() noexcept(std::is_nothrow_destructible_v<T>);

            [[nodiscard]] bool empty() const noexcept;

            [[nodiscard]] std::size_t size() const noexcept;

        private:
            template<typename U = T>
            [[nodiscard]] std::enable_if_t<std::is_pod_v<U> > destroy() noexcept {
            }

            template<typename U = T>
            std::enable_if_t<!std::is_pod_v<U>>
            destroy() noexcept(std::is_nothrow_destructible_v<T>);

            template<typename U>
            std::size_t grow(U &&u) {
                auto desired_size = m_storage_size ? m_storage_size * 2 : block_size * 16;
                auto ptr = A::allocate(*this, desired_size, m_ptr);


                A::construct(*this, ptr + m_end + 1, std::forward<U>(u));
                auto idx = m_end + 1;
                if (m_storage_size) {
                    move_to(m_ptr, m_end, ptr);
                    A::deallocate(*this, m_ptr, m_storage_size);
                }
                m_ptr = ptr;
                m_storage_size = desired_size;
                m_end = idx + 1;
                return idx;

                if (idx != 0) {
                    A::destroy(*this, ptr + idx);
                    A::deallocate(*this, ptr, m_storage_size);
                }
            }

            template<typename U = T>
            std::enable_if_t<std::is_pod_v<U> >
            move_to(const T *b, std::size_t s, T *ptr) noexcept;

            template<typename U =T>
            std::enable_if_t<!std::is_pod_v<U> && std::is_nothrow_move_constructible_v<U>>
            move_to(T *b, std::size_t s, T *ptr) noexcept(std::is_nothrow_destructible_v<U>);

            template<typename U = T>
            std::enable_if_t<!std::is_nothrow_move_constructible_v<U>>
            move_to(const T *b, std::size_t s, T *ptr) noexcept(std::is_nothrow_copy_constructible_v<T>
                                                                && std::is_nothrow_destructible_v<T>);

            T *m_ptr = nullptr;
            std::size_t m_end{};
            std::size_t m_storage_size{};
        };

        template<std::size_t block_size, typename V,
            typename Allocator = std::allocator<V>>
        class Payload {
        public:
            Payload(const Allocator &alloc = Allocator{})
                : m_storage(alloc) {
            }

            template<typename U>
            void push_back(U &&u) { m_storage.push_back(std::forward<U>(u)); }

            void pop_back() {
                m_storage.pop_back();
            }

            V &top() { return m_storage[1]; }
            V &back() { return m_storage.back(); }

            void store(std::size_t idx, V &&v) { m_storage[idx] = std::move(v); };

            void move(std::size_t from, std::size_t to) {
                m_storage[to] = std::move(m_storage[from]);
            }

        private:
            prio_q::SkipVector<V, block_size, Allocator> m_storage;
        };

        template<std::size_t blocking>
        struct HeapAddressing {
            static constexpr std::size_t block_size = blocking;
            static constexpr std::size_t block_mask = block_size - 1;
            static_assert((block_size & block_mask) == 0u, "block size must be 2^n for some integer n");

            inline static std::size_t child_of(std::size_t node_no) noexcept {
                if (enjo_prio_q_likely(!is_block_leaf(node_no))) {
                    return node_no + block_ofset(node_no);
                }
                const auto base = block_base(node_no) + 1;
                return base * block_size + child_no(node_no) * block_size * 2 + 1;
            }

            static std::size_t parent_of(std::size_t node_no) noexcept {
                const auto node_root = block_base(node_no);
                if (enjo_prio_q_likely(!is_block_root(node_no))) {
                    return node_root + block_ofset(node_no) / 2;
                }
                const auto parent_base = block_base(node_root / block_size - 1);
                const auto child = ((node_no - block_size) / block_size - parent_base) / 2;
                return parent_base + block_size / 2 + child;
            }

            static bool is_block_root(std::size_t node_no) noexcept {
                return block_ofset(node_no) == 1u;
            }

            static std::size_t block_ofset(std::size_t node_no) noexcept {
                return node_no & block_mask;
            }

            static std::size_t block_base(std::size_t node_no) noexcept {
                return node_no & ~block_mask;
            }

            static bool is_block_leaf(std::size_t node_no) noexcept {
                return (node_no & (block_size >> 1)) != 0u;
            }

            static std::size_t child_no(std::size_t node_no) noexcept {
                assert(is_block_leaf(node_no));
                return node_no & (block_mask >> 1);
            }
        };

        template<std::size_t block_size, typename Allocator>
        class Payload<block_size, void, Allocator> {
        public:
            Payload(const Allocator & = Allocator{}) {
            }


            static constexpr bool back() { return true; }

            static constexpr void store(std::size_t, bool) {
            }

            static constexpr void move(std::size_t, std::size_t) {
            }

            static constexpr void pop_back() {
            };
        };

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
        T const &SkipVector<T, block_size, Allocator>::operator[](std::size_t idx) const noexcept {
            assert(idx < m_end);
            assert((idx & block_mask) != 0);
            return m_ptr[idx];
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
                    A::destroy(*this, m_ptr + i);
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
            A::destroy(*this, m_ptr + --m_end);
            m_end -= (m_end & block_mask) == 1;
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

            while (enjo_prio_q_likely(i--)) {
                if (enjo_prio_q_likely(i & block_mask)) {
                    A::destroy(*this, ptr + i);
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


    template<std::size_t block_size,
        typename T, typename V,
        typename Compare = std::less<T>,
        typename Allocator= std::allocator<T>>
    class PrioQueue : private Compare, private prio_q::Payload<block_size, V> {
        using Address = prio_q::HeapAddressing<block_size>;
        using P = prio_q::Payload<block_size, V>;
        using ValueType = T;
        using PayloadType = V;

    public:
        PrioQueue(const Compare &compare = Compare())
            : Compare(compare) {
        }

        explicit PrioQueue(const Compare &compare, const Allocator &a)
            : Compare(compare)
              , m_storage(a) {
        }

        template<typename U, typename X = V>
        std::enable_if_t<std::is_same_v<X, void> >
        push(U &&u) {
            push_key(std::forward<U>(u));
        }

        template<typename U, typename X>
        std::enable_if_t<!std::is_same_v<X, void>>
        push(U &&key, X &&value) {
            P::push_back(std::forward<X>(value));
            push_key(std::forward<U>(key));
        }


        template<typename U = V>
        std::enable_if_t<std::is_same_v<U, void>, const ValueType &>
        top() const noexcept {
            assert(!empty());
            return m_storage[1];
        }

        template<typename U = V>
        std::enable_if_t<!std::is_same_v<U, void>, std::pair<const T &, U &> >
        top() noexcept {
            assert(!empty());
            return {m_storage[1], P::top()};
        }

        inline void pop()
            noexcept(std::is_nothrow_destructible_v<T>) {
            assert(!empty());
            std::size_t idx = 1;
            auto const last_idx = m_storage.size() - 1;
            for (; ;) {
                auto lc = Address::child_of(idx);
                if (enjo_prio_q_unlikely(lc > last_idx)) break;
                auto const sibling_offset = enjo_prio_q_unlikely(Address::is_block_leaf(idx))
                                                ? Address::block_size
                                                : 1;
                auto rc = lc + sibling_offset;
                auto i =
                        rc < last_idx && !sorts_before(m_storage[lc], m_storage[rc]);
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
                    if (enjo_prio_q_likely(!sorts_before(last, m_storage[parent]))) {
                        break;
                    }
                    m_storage[idx] = std::move(m_storage[parent]);
                    P::move(parent, idx);
                    idx = parent;
                }
                m_storage[idx] = std::move(last);
                P::store(idx, std::move(last_val));
            }
            m_storage.pop_back();
            P::pop_back();
        }

        template<typename U = V>
        void
        reschedule_top(T t) requires (!std::is_same_v<U, void>) {
            assert(!empty());
            auto val = std::move(P::top());
            size_t idx = do_reschedule_top(t);
            P::store(idx, std::move(val));
        }

        template<typename U=V>
        inline void
        reschedule_top(T t) requires (std::is_same_v<U, void>) {
            assert(!empty());
            do_reschedule_top(t);
        }

        [[nodiscard]] bool empty() const noexcept;

        [[nodiscard]] std::size_t size() const noexcept;

    private:
        template<typename U>
        void push_key(U &&u);

        bool sorts_before(const ValueType &lv, const ValueType &rv) const noexcept;

        prio_q::SkipVector<T, block_size, Allocator> m_storage;

        std::size_t do_reschedule_top(T t) noexcept (noexcept(std::declval<T &>() = std::declval<T &&>()));
    };

    template<std::size_t block_size, typename T, typename V, typename Compare, typename Allocator>
    template<typename U>
    void PrioQueue<block_size, T, V, Compare, Allocator>::push_key(U &&u) {
        auto hole_idx = m_storage.push_back(std::forward<U>(u));
        auto tmp = std::move(m_storage.back());
        auto val = std::move(P::back());

        while (enjo_prio_q_likely(hole_idx != 1U)) {
            auto parent = Address::parent_of(hole_idx);
            auto &p = m_storage[parent];
            if (enjo_prio_q_likely(!sorts_before(tmp, p))) {
                break;
            }
            m_storage[hole_idx] = std::move(p);
            P::move(parent, hole_idx);
            hole_idx = parent;
        }
        m_storage[hole_idx] = std::move(tmp);
        P::store(hole_idx, std::move(val));
    }


    template<std::size_t block_size, typename T, typename V, typename Compare, typename Allocator>
    std::size_t PrioQueue<block_size, T, V, Compare, Allocator>::do_reschedule_top(
        T t) noexcept(noexcept(std::declval<T &>() = std::declval<T &&>())) {
        std::size_t idx = 1;
        auto const last_idx = m_storage.size() - 1;
        while (true) {
            auto lc = Address::child_of(idx);
            if (enjo_prio_q_unlikely(lc > last_idx)) {
                break;
            }

            auto const sibling_offset = enjo_prio_q_unlikely(Address::is_block_leaf(idx)) ? Address::block_size : 1;
            auto rc = lc + sibling_offset;
            auto i = rc <= last_idx && !sorts_before(m_storage[lc], m_storage[rc]);
            auto next = i ? rc : lc;
            if (sorts_before(t, m_storage[next])) {
                break;
            }
            m_storage[idx] = std::move(m_storage[next]);
            P::move(next, idx);
            idx = next;
        }

        m_storage[idx] = std::move(t);
        return idx;
    }

    template<std::size_t block_size, typename T, typename V, typename Compare, typename Allocator>
    bool PrioQueue<block_size, T, V, Compare, Allocator>::empty() const noexcept {
        return m_storage.empty();
    }

    template<std::size_t block_size, typename T, typename V, typename Compare, typename Allocator>
    std::size_t PrioQueue<block_size, T, V, Compare, Allocator>::size() const noexcept {
        return m_storage.size() - (m_storage.size() + Address::block_size - 1) / Address::block_size;
    }

    template<std::size_t BLOCK_SIZE, typename T, typename V, typename Compare, typename Allocator>
    bool PrioQueue<BLOCK_SIZE, T, V, Compare, Allocator>::sorts_before(const ValueType &lv,
                                                                       const ValueType &rv) const noexcept {
        const Compare &c = *this;
        return c(lv, rv);
    }
} // namespace enjo
