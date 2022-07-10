// <h1>Find the missing term in an Arithmetic Progression</h1>
// <h3>An Arithmetic Progression is defined as one in which there is a constant difference between the consecutive terms of a given series of numbers. You are provided with consecutive elements of an Arithmetic Progression. There is however one hitch: exactly one term from the original series is missing from the set of numbers which have been given to you. The rest of the given series is the same as the original AP. Find the missing term.

//     You have to write a function that receives a list, list size will always be at least 3 numbers. The missing term will never be the first or last one.

//     Example
//     findMissing([1, 3, 5, 9, 11]) == 7
//     PS: This is a sample question of the facebook engineer challenge on interviewstreet. I found it quite fun to solve on paper using math, derive the algo that way. Have fun!"</h3>




#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <numeric>

static long findMissing(std::vector<long> &list) {
    std::reverse(list.begin(), list.end());
    long n = list[0];
    long x = list[0] - list[1];
    for (size_t i = 1; i < list.size(); i++) {
        if ((n - list[i]) == x) {
            n = list[i];
        } else return list[i] + x;
    }
}

int main() {
    std::vector<long> vec {1, 3, 5, 9, 11};
//    std::cout  << vec[-3] <<std::endl;
    std::cout << findMissing(vec);

}