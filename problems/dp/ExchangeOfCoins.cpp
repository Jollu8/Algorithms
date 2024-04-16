///// @Jollu
// ExchangeOfCoins

#include <vector>
#include <limits>
#include <algorithm>

template<typename T, template<class> typename V>
T exchange_sub_recursive_func(V<T> &values, const V<T> &coins, const T coins_amount) {
    if (coins_amount < 0) return std::numeric_limits<T>::max() - 1;
    if (coins_amount == 0)return 0;
    if (values.at(coins_amount) != 0) return values.at(coins_amount);

    T min_count = std::numeric_limits<T>::max() - 1;
    for (const auto &i: coins)
        min_count = std::min(min_count, exchange_sub_recursive_func(values, coins, coins_amount - 1) + 1);

    values.at(coins_amount) = min_count;
    return min_count;
}

template<typename T, typename =typename std::enable_if<std::is_arithmetic<T>::value>::type, template<class> typename V>
T exchange_by_min_count_coins_recursive(const V<T> &coins, const T coins_amount) {
    V<T> values(coins_amount + 1, 0);
    return exchange_sub_recursive_func(values, coins, coins_amount);
};

template<typename T, typename = typename std::enable_if_t<std::is_arithmetic_v<T>>, template<class> typename V>
T exchange_by_min_count_non_recursive(const V<T> &coins, const T coins_amount) {
    V<T> values(coins_amount + 1, 0);

    for (auto i = 1; i < values.size(); i++) {
        values.at(i) = std::numeric_limits<T>::max() - 1;
        for (const auto coin: coins) {
            if (values.at(i) - coin >= 0)
                values.at(i) = std::min(values.at(i), values.at(i - coin) + 1);
        }
    }
    return values.at(coins_amount);
}

#include <iostream>

int main() {
    const std::vector<int> coins = {1, 3, 4};
    std::cout << exchange_by_min_count_coins_recursive(coins, 10) << std::endl;
    std::cout << exchange_by_min_count_non_recursive(coins, 10) << std::endl;
}