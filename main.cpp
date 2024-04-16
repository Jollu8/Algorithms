#include <iostream>
#include <set>
#include <string>

#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> adj; // список смежности
vector<bool> visited; // массив для отметки посещенных вершин
vector<int> squad; // текущий отряд

// Функция DFS
void dfs(int v) {
    visited[v] = true;
    squad.push_back(v);
    for (int u : adj[v]) {
        if (!visited[u])
            dfs(u);
    }
}

int main() {
    int N;
    cin >> N;
    adj.resize(N);
    visited.resize(N, false);

    // Заполнение списка смежности
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            int x;
            cin >> x;
            if (x == 1)
                adj[i].push_back(j);
        }
    }

    // Поиск всех отрядов
    for (int i = 0; i < N; ++i) {
        if (!visited[i]) {
            squad.clear();
            dfs(i);
            cout << "Отряд: ";
            for (int v : squad)
                cout << v + 1 << ' ';
            cout << endl;
        }
    }

    return 0;
}
