#include <vector>

template <typename T>
concept Range = requires(T range) {
    std::begin(range);
    std::end(range);
};

template<Range R>
void counting(R& vec, int exp) {
    vector<int> buff(10, 0);
    vector<int> out(vec.size(), 0);
    for (int i : vec) buff[(i / exp) % 10]++;

    for (int i = 1; i < 10; ++i) buff[i] += buff[i - 1];

    for(int  i = vec.size() - 1; i >= 0; --i) {
        out[buff[(vec[i] / exp) % 10] - 1] = vec[i];
        buff[(vec[i] / exp) % 10]--;
    }

    for(int i = 0; i < vec.size(); ++i) vec[i] = out[i];
}


void radix(vector<int> &vec) {
    const int m = *max_element(vec.begin(), vec.end());
    for(int exp = 1; m / exp > 0; exp *= 10) counting(vec, exp);
}