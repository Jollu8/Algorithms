#include <algorithm>
#include <iostream>
#include <vector>


struct Box {
    int a, b, c;
};


int v(const Box &a) {
    return a.a * a.b * a.c;
}

bool operator<(const Box &a, const Box &b) {
    return v(a) < v(b);
}


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    std::vector<Box> boxs(n);
    for (auto i = 0; i < n; ++i) {
        std::cin >> boxs[i].a >> boxs[i].b >> boxs[i].c;
    }

    std::sort(boxs.begin(), boxs.end());

    for (const auto &b: boxs) {
        std::cout << b.a << ' ' << b.b << ' ' << b.c << '\n';
    }
}
