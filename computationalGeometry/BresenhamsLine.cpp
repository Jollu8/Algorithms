///// @Jollu
// Bresenham`s Line algorithm


#include <algorithm>
#include <vector>
#include <utility>
#include <cstdint>
#include <iostream>
#include <cmath>


static const std::int8_t X_COORDINATE = 0;
static const std::int8_t Y_COORDINATE = 1;


template<typename T>
using point_t = std::pair<T, T>;


template<typename T>
using line_t = std::vector<point_t<T>>;

template<typename T, typename =
typename std::enable_if_t<std::is_arithmetic_v<T>>>
line_t<T> create_line(const point_t<T> &from_point, const point_t<T> &to_point) noexcept {
    line_t<T> des_line{};
    const int dx = (std::get<X_COORDINATE>(to_point) - std::get<X_COORDINATE>(from_point) >= 0 ? 1 : -1);
    const int dy = (std::get<Y_COORDINATE>(to_point) - std::get<Y_COORDINATE>(from_point) >= 0 ? 1 : -1);
    const std::size_t length_x = std::abs(std::get<X_COORDINATE>(to_point) - std::get<X_COORDINATE>(from_point));
    const std::size_t length_y = std::abs(std::get<Y_COORDINATE>(to_point) - std::get<Y_COORDINATE>(from_point));

    std::size_t max_length = std::max(length_x, length_y);
    if (max_length == 0) des_line.push_back(from_point);
    else if (length_x, length_y) {
        max_length++;
        T x = std::get<X_COORDINATE>(from_point);
        float y = std::get<Y_COORDINATE>(from_point);
        float d = dy * static_cast<float >(length_y) / length_x;
        while (max_length--) {
            des_line.template emplace_back(x, std::roundf(y));
            y += d;
            x += dx;
        }
    } else {
        max_length++;
        float x = std::get<X_COORDINATE>(from_point);
        T y = std::get<Y_COORDINATE>(from_point);
        T d = dx * static_cast<float >(length_x) / length_y;

        while (max_length--) {
            des_line.template emplace_back(std::roundf(x), y);
            x += d;
            y += dy;
        }
    }
    return des_line;
};

int main()
{
    const point_t<int> start_point{ 2, 6 };
    const point_t<int> end_point{ 12, 2 };
    const line_t<int> dest_line = create_line(start_point, end_point);
    for (const auto& point : dest_line)
        std::cout << "{ " << std::get<X_COORDINATE>(point) << "; " << std::get<Y_COORDINATE>(point) << " }\n";

}