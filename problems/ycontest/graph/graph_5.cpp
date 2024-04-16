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


class Solution {
    vector<vector<int>> adj;
    vector<bool> visited;
public:
    explicit Solution(int v) : adj(v), visited(v, false) {

    }

    void add(int v, int w) {
        adj[v].emplace_back(w);
        adj[w].emplace_back(v);
    }

    void dfs(int v) {
        visited[v] = true;
        for (auto u: adj[v])
            if (!visited[u]) dfs(u);
    }

    int squads() {
        int ans{};
        for (int i = 0; i < adj.size(); ++i) {
            if (!visited[i]) {
                dfs(i);
                ++ans;
            }
        }
        return ans;
    }
};


int main() {

    ifstream in("input.txt");
    int N, M;
    in >> N >> M;
    Solution s(N - 1);

    // Заполнение списка смежности
    for (int i = 0; i < M; ++i) {
        int u, v;
        in >> u >> v;
        --u; // уменьшаем на 1, так как нумерация идет с 1
        --v; // уменьшаем на 1, так как нумерация идет с 1
        s.add(u, v);
    }
    ofstream out("output.txt");
    out << s.squads();
}
