#include <iostream>
#include <vector>
#include <tuple>


std::tuple<int, int, long long> find_max_sub_array(std::vector<int> &a) {
    int sum1 = 0, sum2 = 0;
    int left_sum = INT_MIN, right_sum = INT_MIN;
    int max_left, max_right;

    if (a.empty()) return {0, 0, 0};
    else if (a.size() == 1) return {0, 0, a[0]};
    else {
        for (auto i = a.size() / 2, j = a.size() / 2 + 1; i >= 0, j <= a.size(); --i, ++j) {
            sum1 += a[i];
            sum2 += a[j];
            if (sum1 > left_sum) {
                left_sum = sum1;
                max_left = i;
            }
            if (sum2 > right_sum) {
                right_sum = sum2;
                max_right = j;
            }
        }
    }
    return {max_left, max_right, left_sum + right_sum};
}


int main() {
    std::vector<int> a{-3, -1, 4, -2, -1, 5, -3};

    auto [l, r, sum] = find_max_sub_array(a);

    std::cout << "left=" << l << " right=" << r << " sum=" << sum;
}

#if 0
#include <stdio.h>

void findMaxSubArray(int arr[], int size) {
    int max_so_far = arr[0];
    int curr_max = arr[0];

    for (int i = 1; i < size; i++) {
        curr_max = (arr[i] > curr_max + arr[i]) ? arr[i] : curr_max + arr[i];
        max_so_far = (max_so_far > curr_max) ? max_so_far : curr_max;
    }

    printf("Максимальная сумма подмассива равна: %d", max_so_far);
}

int main() {
    int arr[] = {-3, -1, 4, -2, -1, 5, -3};
    int n = sizeof(arr) / sizeof(arr[0]);

    findMaxSubArray(arr, n);

    return 0;
}
#endif
