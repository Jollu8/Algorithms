#include <iostream>
#include <vector>
#include <type_traits>


namespace t_m {
    template<typename T>
    T arithmetic_mean(const std::vector<T> &vec) {
        if (vec.empty())
            return T();
        static_assert(sizeof(T) != 1, "The type should not be char or bool");
        static_assert(std::is_arithmetic<T>(), "Type must be arithmetic");

        T num = T();
        T size = static_cast<T>(vec.size());
        for (const auto &v: vec) {
            num += v;
        }
        return num / size;
    }

    template<typename T>
    void enter_data(std::vector<T> &vec) {
        T num = T();
        std::cout << "Enter type " << typeid(T).name() << " for end enter 0:" << std::endl;
        do {
            std::cin >> num;
            if (num != 0)
                vec.push_back(num);
        } while (num != 0);

    }
}


int main() {
    std::vector<float> t;

    t_m::enter_data(t);
    std::cout << t_m::arithmetic_mean(t) << std::endl;


}