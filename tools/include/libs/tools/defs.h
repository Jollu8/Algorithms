/**
 *@athor Jollu8
 */

#pragma once

#include <cstdint>
#include <cstddef>
#include <chrono>
#include <memory>
#include <unordered_map>
#include <unordered_set>

namespace libs {
    template<auto func>
    using Ftor = std::integral_constant<decltype(func), func>;

    using SystemClock = std::chrono::system_clock;
    using SystemTime = SystemClock::time_point;
    using Secs = std::chrono::seconds;
    using Millis = std::chrono::milliseconds;
    using Micros = std::chrono::microseconds;
    using Nanos = std::chrono::nanoseconds;

    template<typename K, typename V>
    using HashMap = std::unordered_map<K, V>;
    template<typename K>
    using HashSet = std::unordered_set<K>;
    template<typename T, auto D>
    using UniquePtr = std::unique_ptr<T, Ftor<D> >;

    template<typename T>
    using AllocatedPtr = UniquePtr<T, &std::free>;
}
