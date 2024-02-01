/// @author https://github.com/rollbear/prio_queue

/// B-heap priority queue

#pragma once

#include <cstddef>
#include <memory>
#include <type_traits>
#include <vector>
#include <cassert>
#include <tuple>
#include <cstdint>
#include <fmt/format.h>
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

            T &operator[](std::size_t idx) noexcept;

            T const &operator[](std::size_t idx) const noexcept;

            T &back() noexcept;

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
            std::size_t grow(U &&u);

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
        struct HeapAddressin {
            static constexpr std::size_t block_size = blocking;
            static constexpr std::size_t block_mask = block_size - 1;
            static_assert((block_size & block_mask) == 0u, "block size must be 2^n for some integer n");

            static std::size_t child_of(std::size_t node_no) noexcept;

            static std::size_t parent_of(std::size_t node_no) noexcept;

            static bool is_block_root(std::size_t node_no) noexcept;

            static std::size_t block_ofset(std::size_t node_no) noexcept;

            static std::size_t block_base(std::size_t node_no) noexcept;

            static bool is_block_leaf(std::size_t node_no) noexcept;

            static std::size_t child_no(std::size_t node_no) noexcept;
        };

        template<std::size_t block_size, typename Allocator>
        class Payload<block_size, void, Allocator> {
        public:
            Payload(Allocator const & = Allocator{}) {
            }

            constexpr bool back() const { return true; }

            constexpr void store(std::size_t, bool) const {
            }

            constexpr void move(std::size_t, std::size_t) const {
            }

            constexpr void pop_back() const {
            };
        };
    } // namespace prio_q

    template<std::size_t block_size,
        typename T, typename V,
        typename Compare = std::less<T>,
        typename Allocator= std::allocator<T>>
    class PrioQueue : private Compare, private prio_q::Payload<block_size, V> {
        using Address = prio_q::HeapAddressin<block_size>;
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
        std::enable_if_t<std::is_same<X, void>::value>
        push(U &&u);

        template<typename U, typename X>
        std::enable_if_t<!std::is_same<X, void>::value>
        push(U &&key, X &&value);


        template<typename U = V>
        std::enable_if_t<std::is_same_v<U, void>, const ValueType &>
        top() const noexcept;

        template<typename U = V>
        std::enable_if_t<std::is_same_v<U, void>, std::pair<const T &, U &> >
        top() noexcept;

        void pop() noexcept (std::is_nothrow_destructible_v<T>);

        template<typename U = V>
        std::enable_if_t<!std::is_same_v<U, void>>
        reschedule_top(T t);

        template<typename U=V>
        inline std::enable_if_t<std::is_same<U, void>::value>
        reschedule_top(T t);

        [[nodiscard]] bool empty() const noexcept;

        std::size_t size() const noexcept;

    private:
        template<typename U>
        void push_key(U &&u);

        bool sorts_before(const ValueType &lv, const ValueType &rv) const noexcept;

        prio_q::SkipVector<T, block_size, Allocator> m_storage;

        std::size_t do_reschedule_top(T t) noexcept (noexcept(std::declval<T &>() = std::declval<T &&>()));
    };
} // namespace enjo
