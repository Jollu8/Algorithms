#pragma GCC optimize("O3")

#include <iostream>
#include <vector>
#include <unordered_map>

int main() {
    int n, b;
    std::cin >> n >> b;

    std::vector<int> a;
    a.resize(n);
    int indexB = -1;

    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
        if (a[i] == b) indexB = i;
    }

    std::unordered_map<int, int> l_Balance;
    int balance{};
    l_Balance[balance] = 1;

    for (int i = indexB - 1; i >= 0; i--) {
        if (a[i] > b) balance++;
        else if (a[i] < b)balance--;

        if (l_Balance.find(balance) != l_Balance.end()) l_Balance[balance]++;
        else l_Balance[balance] = 1;
    }

    balance = 0;
    int result{};

    for (int i = indexB; i < n; i++) {
        if (a[i] > b) balance++;
        else if (a[i] < b) balance--;

        if (l_Balance.find(-balance) != l_Balance.end()) result += l_Balance[-balance];

    }

    std::cout << result << std::endl;
}
