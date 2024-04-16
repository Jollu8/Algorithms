///// @Jollu
// Ramer Douglas Peucker Algorithm



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
using line_segment_t = std::pair<point_t<T>, point_t<T>>;

template<typename T>
using points_t = std::vector<point_t<T>>;

template<typename T>
double get_distance_between_point_and_line_segment(const line_segment_t<T> &lineSegment, const point_t<T> &point) {
    const T x = std::get<X_COORDINATE>(point);
    const T y = std::get<Y_COORDINATE>(point);

    const T x1 = std::get<X_COORDINATE>(lineSegment.first);
    const T y1 = std::get<Y_COORDINATE>(lineSegment.first);

    const T x2 = std::get<X_COORDINATE>(lineSegment.second);
    const T y2 = std::get<Y_COORDINATE>(lineSegment.second);

    const double doubleArea = std::abs((y2 - y1) * x - (x2 - x1) * y + x2 * y1 - y2 * x1);
    const double lineSegmentLength = std::sqrt(std::pow((x2 - x1), 2) + std::pow((y2 - y1), 2));
    if (lineSegmentLength != 0.0) return doubleArea / lineSegmentLength;
    else return 0.0;
}

template<typename T>
void simplify_points(const points_t<T> &srcPoints, points_t<T> &destPoints, double tolerance, std::size_t begin,
                     std::size_t end) {
    if (begin + 1 == end) return;

    double maxDistance = -1.0;
    std::size_t maxIndex = 0;

    for (std::size_t i = begin + 1; i < end; ++i) {
        const point_t<T> &curPoint = srcPoints.at(i);
        const point_t<T> &startPoint = srcPoints.at(begin);
        const point_t<T> &endPont = srcPoints.at(end);
        const double distance = get_distance_between_point_and_line_segment({startPoint, endPont}, curPoint);
        if (distance > maxDistance) {
            maxDistance = distance;
            maxIndex = i;
        }
    }
    if (maxDistance > tolerance) {
        simplify_points(srcPoints, destPoints, tolerance, begin, maxIndex);
        destPoints.push_back(srcPoints.at(maxIndex));
        simplify_points(srcPoints, destPoints, tolerance, maxIndex, end);
    }
}

template<typename T, typename = typename std::enable_if_t<std::is_integral_v<T> || std::is_floating_point_v<T>>>
points_t<T> ramer_duglas_peucker(const points_t<T> &srcPoints, double tolerance) {
    if (tolerance <= 0) return srcPoints;

    points_t<T> destPoints{};
    destPoints.push_back(srcPoints.front());
    simplify_points(srcPoints, destPoints, tolerance, 0, srcPoints.size() - 1);
    destPoints.push_back(srcPoints.back());
    return destPoints;
}

int main() {
    points_t<int> source_points{{1,  5},
                                {2,  3},
                                {5,  1},
                                {6,  4},
                                {9,  6},
                                {11, 4},
                                {13, 3},
                                {14, 2},
                                {18, 5}};
    points_t<int> simplify_points = ramer_duglas_peucker(source_points, 0.5);

}