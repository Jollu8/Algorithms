//
// Created by jollu on 1/23/22.
//

#ifndef CPLUSPLUS_INFINITI2_H
#define CPLUSPLUS_INFINITI2_H
#include <iostream>
static const int N = 10000;

void infinti2() {
    int i, p, q, id[N];
    for (i = 0; i < N; i++)id[i] = i;
    while (std::cin >> p >> q) {
        int t = id[p];
        if (t == id[q])continue;
        for (i = 0; i < N; i++)
            if (id[i] == t) id[i] = id[q];
        std::cout << " " << p << " " << q << std::endl;
    }
}
#endif //CPLUSPLUS_INFINITI2_H
