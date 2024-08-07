#include <iostream>
#include <vector>
#include <algorithm>

//

int main(){

    int n;
    std::pair<int, int> points;

    std::cin >> n;
    std::vector<std::pair<int, int>> coord(n);

    for (int i = 0; i < n; ++i)
        std::cin >> coord[i].first >> coord[i].second;

    std::sort(coord.begin(), coord.end(), [](std::pair<int, int>& a, std::pair<int, int>& b)
                                            {
                                                return std::min(a.first, a.second) < std::min(b.first, b.second);
                                            });

    int count = 0;
    for (int i = 1; i < n; ++i) {
        if (((std::max(coord[i-1].first, coord[i-1].second) < std::min(coord[i].first, coord[i].second) ||
            (coord[i-1].second == coord[i].first && coord[i].second > coord[i-1].second))) &&
                                                            (coord[i-1].first != coord[i].first)) ++count;

        // if (!(coord[i-1].second >= coord[i].second) || !((std::max(coord[i-1].first, coord[i-1].second) >= std::min(coord[i].first, coord[i].second)))) ++count;
    }

    if (n == count + 1)
        std::cout << n;
    else
        std::cout << count;
}