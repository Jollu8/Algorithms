//
// Created by Jollu Emil on 4/16/24.
//

#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <numeric>
#include <unordered_map>
#include <fstream>
#include <list>
#include <sstream>
#include <queue>


using namespace std;

int main() {
    int N;
    cin >> N;
    vector<vector<int>> dist(N, vector<int>(N));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> dist[i][j];
        }
    }

    int min_dist = 1e9;
    for (int i = 0; i < N; ++i) {
        for (int j = i + 1; j < N; ++j) {
            for (int k = j + 1; k < N; ++k) {
                int total_dist = dist[i][j] + dist[j][k] + dist[k][i];
                min_dist = min(min_dist, total_dist);
            }
        }
    }

    cout << min_dist << endl;

    return 0;
}