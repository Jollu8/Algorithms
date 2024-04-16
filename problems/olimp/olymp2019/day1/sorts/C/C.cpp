#include <iostream>
#include <vector>
#include <algorithm>


struct Empl {
    int i;
    int first;
    int second;
};

using pi = Empl;

#define F first
#define S second

bool cmp(pi &a, pi &b) {
    if (a.S == b.S) return a.F > b.F;
    return a.S > b.S;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<pi> empls(n);
    for (auto i = 0; i < n; ++i) {
        std::cin >> empls[i].F;
        empls[i].i = i + 1;
    }
    for (auto i = 0; i < n; ++i)
        std::cin >> empls[i].S;

    std::sort(empls.begin(), empls.end(), cmp);

    for (auto &e: empls) std::cout << e.i << ' ';
}
