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
#include <stack>

using namespace std;


class Solution {
    vector<vector<int>> adj;
    vector<bool> visited;
public:
    explicit Solution(int v) : adj(v), visited(v, false) {

    }

    void add(int v, int w) {
        adj[v].emplace_back(w);
//        adj[w].emplace_back(v);
    }

    void dfs_rec(int v) {
        visited[v] = true;
        for (auto u: adj[v])
            if (!visited[u]) dfs_rec(u);
    }

    void dfs_iter(int v) {
        stack<int> st;
        st.push(v);
        while (!st.empty()) {
            v = st.top();
            st.pop();
            if (!visited[v]) {
                visited[v] = true;
                for (auto i: adj[v])
                    if (!visited[i]) st.push(i);

            }
        }


    }

    bool is_path(int a, int b) {
        fill(visited.begin(), visited.end(), false);
        dfs_iter(a);
        return visited[b];
    }
};


int main() {
    int N, M;
    cin >> N;
    cin >> M;
    Solution s(N);

    // Заполнение списка смежности
    for (int i = 0; i < M; ++i) {
        int u, v;
        cin >> u >> v;
        --u; // уменьшаем на 1, так как нумерация идет с 1
        --v; // уменьшаем на 1, так как нумерация идет с 1
        s.add(u, v);
    }

    int u, v;
    cin >> M;
    vector<bool> ans(M, false);
    for (int i = 0; i < M; ++i) {
        cin >> u >> v;
        ans[i] = s.is_path(u - 1, v - 1);
    }
    for (auto i: ans) std::cout << ((i) ? "Yes\n" : "No\n");

}

