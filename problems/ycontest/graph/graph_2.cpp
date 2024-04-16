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
using namespace std;


class Solution {
    vector<set<int>> adj;
public:
    void start(int v) {
        adj = vector<set<int>>(v+1);
    }

    void add(int v, int w) {
        adj[v].insert(w);
    }

    void get() const {
        ofstream out("output.txt");
        for (int i = 1; i < adj.size(); ++i) {
            out << i << ": ";
            for(auto j : adj[i]) out << j << ' ';
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
    s.start(n);
    int x, y;
    while (m--) {
        cin >> x >> y;
        s.add(x, y);
    }
    s.get();

}