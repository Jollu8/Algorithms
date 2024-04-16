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

using namespace std;

class Solution {
    vector<vector<int>> adj;
public:
    void set(int v) {
        adj = vector<vector<int>>(v+1, vector<int>(v+1, 0));
    }

    void add(int v, int w) {
        adj[v][w] = 1;
    }

    void get() const {
        ofstream out("output.txt");
        for (int i = 1; i < adj.size(); ++i) {
            for (int j = 1; j < adj[0].size(); ++j) {
                out << adj[i][j] << ' ';
            }
            out << '\n';
        }
    }

};


// Test Case
int main() {
    Solution s;

    int n, m;
    cin >> n;
    cin >> m;
    s.set(n);
    int x, y;
    while (m--) {
        cin >> x >> y;
        s.add(x, y);
    }
    s.get();

}