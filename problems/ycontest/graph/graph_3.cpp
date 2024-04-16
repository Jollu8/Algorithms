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

using namespace std;




// Test Case
int main() {


    long long sum{};
    int n;
    cin >> n;
    int z = n;
    while(n--) {
        int tmp;
        for(int i = 0; i < z; ++i) {
            cin >> tmp;
            sum += tmp;
        }
    }

    cout << sum / 2;


}