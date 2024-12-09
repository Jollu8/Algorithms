#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int MOD = 1000000007;
const int TYPE = 3;
using ll = long long;
using vv = vector<vector<bool>>;

int numMatchingTypes(int l, int k, const vv& open, const vv& close) {
    int count = 0;
    for (int t = 0; t < TYPE; t++) {
        if (open[l][t] && close[k][t]) count++;
    }
    return count;
}

int main() {
    int n;
    cin >> n;
    cin.ignore();
    string s;
    getline(cin, s);

    vector<vector<ll>> dp(n, vector<ll>(n, 0));
    vv open(n, vector<bool>(TYPE, false));
    vv close(n, vector<bool>(TYPE, false));

    for (int i = 0; i < n; i++) {
        char ch = s[i];
        switch (ch) {
            case '(':
                open[i][0] = true;
                break;
            case '{':
                open[i][1] = true;
                break;
            case '[':
                open[i][2] = true;
                break;
            case ')':
                close[i][0] = true;
                break;
            case '}':
                close[i][1] = true;
                break;
            case ']':
                close[i][2] = true;
                break;
            case '?':
                open[i][0] = open[i][1] = open[i][2] = true;
                close[i][0] = close[i][1] = close[i][2] = true;
                break;
        }
    }

    for (int len = 2; len <= n; len++) {
        for (int left = 0; left + len <= n; left++) {
            int right = left + len - 1;
            dp[left][right] = 0;

            for (int mid = left + 1; mid <= right; mid += 2) {
                int numMatches = numMatchingTypes(left, mid, open, close);

                if (numMatches == 0) {
                    continue;
                }

                ll leftWays = (left + 1 <= mid - 1) ? dp[left + 1][mid - 1] : 1;
                ll rightWays = (mid + 1 <= right) ? dp[mid + 1][right] : 1;

                ll totalWays = (leftWays * rightWays) % MOD;
                totalWays = (totalWays * numMatches) % MOD;

                dp[left][right] = (dp[left][right] + totalWays) % MOD;
            }
        }
    }

    cout << dp[0][n - 1] << endl;

    return 0;
}
