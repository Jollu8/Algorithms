#include <queue>
#include <map>
#include <fstream>
#include <algorithm>


int main() {
    int n, M = 3;
    std::ifstream infile("input.txt");
    std::ofstream outfile("output.txt");
    infile >> n;
    int events[M][n];

    for (int i = 0; i < M; i++){
        for (int j = 0; j < n; j++) infile >> events[i][j];
    }


    auto inSect = [](int event, const auto &map1, const auto &map2) {
        return map1.find(event) != map1.end() && map2.find(event) != map2.end() && map1.at(event) > 0 &&
               map2.at(event) > 0;
    };

    auto decreaseCnt = [](int event, auto &map) {
        if (map.find(event) != map.end()) {
            map[event]--;
            if (!map[event]) map.erase(event);
        }
    };


    std::map<int, int> mapA,mapB,mapC;


    for (int i = 0; i < n; i++) {
        mapA[events[0][i]]++;
        mapB[events[1][i]]++;
        mapC[events[2][i]]++;
    }

    std::vector<bool> removed(n);
    std::queue<int> queue;

    for (int i = 0; i < n; i++) {
        if (!inSect(events[0][i], mapB, mapC) ||
            !inSect(events[1][i], mapA, mapC) ||
            !inSect(events[2][i], mapA, mapB)) {
            queue.push(i);
            removed[i] = true;
        } else removed[i] = false;

    }

    while (!queue.empty()) {
        int index = queue.front();
        queue.pop();

        decreaseCnt(events[0][index], mapA);
        decreaseCnt(events[1][index], mapB);
        decreaseCnt(events[2][index], mapC);

        for (int i = 0; i < n; i++) {
            if (!removed[i] &&
                (!inSect(events[0][i], mapB, mapC) ||
                 !inSect(events[1][i], mapA, mapC) ||
                 !inSect(events[2][i], mapA, mapB))) {
                queue.emplace(i);
                removed[i] = true;
            }
        }
    }
    outfile << std::count_if(removed.begin(), removed.end(), [](auto i) {return i == true;}) << '\n';
    return 0;
}
