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

            T const back() const noexcept;

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

        template<typename T, std::size_t block_size, typename Allocator>
        SkipVector<T, block_size, Allocator>::SkipVector() noexcept :SkipVector(Allocator()) {}

        template<typename T, std::size_t block_size, typename Allocator>
        SkipVector<T, block_size, Allocator>::SkipVector(const Allocator &alloc) noexcept(std::is_nothrow_copy_constructible_v<T>):
        Allocator(alloc){

        }
        template<typename T, std::size_t block_size, typename Allocator>
        SkipVector<T, block_size, Allocator>::SkipVector(SkipVector &&v) noexcept
        : m_ptr(v.m_ptr)
        , m_end(v.m_end)
        , m_storage_size(v.m_storage_size){
            v.m_ptr = nullptr;
        }

    }
}
