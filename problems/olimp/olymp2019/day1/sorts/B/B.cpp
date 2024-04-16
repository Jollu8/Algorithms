#include <iostream>
#include <vector>
#include <algorithm>

struct Elem {
    int val;
    bool open;
};

bool operator <(const Elem &a, Elem &b) {
    if (a.val == b.val) return a.open > b.open;
    return a.val < b.val;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    std::vector<Elem> arr(n * 2);
    for (auto i = 0; i < 2 * n; i += 2) {
        std::cin >> arr[i].val >> arr[i + 1].val;
        arr[i].open = true;
        arr[i + 1].open = false;
    }

    std::sort(arr.begin(), arr.end());
    int ans = 0;
    for (int i = 0, j = 0; i < 2 * n; i++) {
        if (j > 0) ans += (arr[i].val - arr[i - 1].val);
        if (arr[i].open) ++j;
        else --j;
    }

    std::cout << ans << '\n';
}