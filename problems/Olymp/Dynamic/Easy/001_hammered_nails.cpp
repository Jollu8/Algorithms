//
// Created by Jollu Emil
//


#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <tuple>

using namespace std;

using line = vector<int>;

int main() {
    // ...
    ios::sync_with_stdio(false);
    int n;
    cin >> n;

    line d(n);
    for (auto &i: d)
        cin >> i;

    sort(d.begin(), d.end());

    line p(n);
    for (int i(1); i < n; i++) {
        p[i] = d[i] - d[i - 1];
    }
    line r(n);

    r[0] = 0;
    r[1] = p[1];

    if (n > 2) {
        r[2] = r[1] + p[2];
        for (int i(3); i < n; i++) {
            r[i] = p[i] + min(r[i - 1], r[i - 2]);
        }
    }

    cout << r[n - 1];

}