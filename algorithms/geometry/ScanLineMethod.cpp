///// @Jollu
// Scan Line Method



#include <algorithm>
#include <vector>
#include <utility>
#include <cstdint>
#include <iostream>


enum class PointType {
    START_SEGMENT = 0,
    END_SEGMENT
};


template<typename T>
struct Point {
    T x = 0;
    T y = 0;
    PointType type = PointType::START_SEGMENT;

};



template<typename T>
struct Segment {
    T startXPoint = 0;
    T endXPoint = 0;
};

template<typename T, typename = typename std::enable_if_t<std::is_arithmetic_v<T>>>
Segment<T> find_line_segment_covered_largest_number_segments(std::vector<Point<T>> &segmentsPoints) {
    std::sort(segmentsPoints.begin(), segmentsPoints.end(), [](auto a, auto b) {
        return a.x > b.x;
    });

    std::size_t accumulate = 0;
    std::size_t maxCountSegment = 0;
    Segment<T> largestSegment{};
    for (const auto &point: segmentsPoints) {
        if (point.type == PointType::START_SEGMENT) {
            accumulate++;
            if (accumulate > maxCountSegment) {
                maxCountSegment = accumulate;
                largestSegment.startXPoint = point.x;
            }
        } else if (point.type == PointType::END_SEGMENT) {
            accumulate--;
            if (accumulate == (maxCountSegment - 1)) largestSegment.endXPoint = point.x;
        }
    }
    return largestSegment;
}

int main() {
    std::vector<Point<float>> segments_points = {
            {1.0f,  3.0f, PointType::START_SEGMENT},
            {5.0f,  3.0f, PointType::END_SEGMENT},
            {2.0f,  1.0f, PointType::START_SEGMENT},
            {4.0f,  1.0f, PointType::END_SEGMENT},
            {3.0f,  4.0f, PointType::START_SEGMENT},
            {4.0f,  4.0f, PointType::END_SEGMENT},
            {3.0f,  2.5f, PointType::START_SEGMENT},
            {7.0f,  2.5f, PointType::END_SEGMENT},
            {4.5f,  1.0f, PointType::START_SEGMENT},
            {11.0f, 1.0f, PointType::END_SEGMENT},
            {6.0f,  4.0f, PointType::START_SEGMENT},
            {11.0f, 4.0f, PointType::END_SEGMENT}
    };

    Segment<float> segment = find_line_segment_covered_largest_number_segments(segments_points);
    std::cout << "Largest segment: (" << segment.startXPoint << "; " << segment.endXPoint << ")" << std::endl;


}



