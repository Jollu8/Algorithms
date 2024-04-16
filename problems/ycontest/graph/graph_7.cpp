//
// Created by Jollu Emil on 4/16/24.
//
#include <iostream>
#include <vector>

int main() {
    int N;
    std::cin >> N;
    std::vector<std::vector<int>> bridges(N, std::vector<int>(N));
    std::vector<int> colors(N);

    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            std::cin >> bridges[i][j];

    for (int i = 0; i < N; ++i)
        std::cin >> colors[i];

    int bad_bridges = 0;
    for (int i = 0; i < N; ++i)
        for (int j = i+1; j < N; ++j)
            if (bridges[i][j] && colors[i] != colors[j])
                ++bad_bridges;

    std::cout << bad_bridges << std::endl;

    return 0;
}
