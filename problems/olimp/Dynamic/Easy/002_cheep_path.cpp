//
// Created by Jollu Emil
//


#include <iostream>
#include <vector>
#include <climits>

int min(int x, int y) {
    return (x < y) ? x : y;
}
// noone recursive
int minPath(std::vector<std::vector<int>> &cost, int m, int n) {
    std::vector<std::vector<int>> dp(m+1, std::vector<int>(n+1, INT_MAX));
    dp[0][0] = cost[0][0];
    for (int i = 1; i <= m; ++i) {
        dp[i][0] = dp[i-1][0] + cost[i][0];
    }
    for (int j = 1; j <= n; ++j) {
        dp[0][j] = dp[0][j-1] + cost[0][j];
    }
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            dp[i][j] = min(dp[i-1][j], dp[i][j-1]) + cost[i][j];
        }
    }
    return dp[m][n];
}

int main() {
    int m, n;
    std::cin >> m >> n;
    std::vector<std::vector<int>> cost(m, std::vector<int>(n));
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cin >> cost[i][j];
        }
    }
    std::cout << minPath(cost, m-1, n-1) << std::endl;
    return 0;
}