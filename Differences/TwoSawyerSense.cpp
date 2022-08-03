///// @Jollu
// Two Sawyer Sense

#include <vector>
#include <iostream>
#include <algorithm>

enum class IntervalType {
    START_BOARD = -1,
    END_BOARD = 1
};

template<
        typename T,
        typename = typename std::enable_if<std::is_integral<T>::value>::type>
struct IntervalBoard {
    T coordinate = 0;
    IntervalType type = IntervalType::START_BOARD;

    bool operator<(const IntervalBoard &other) noexcept {
        if (coordinate == other.coordinate)
            return type < other.type;
        else
            return coordinate < other.coordinate;
    }
};

template<typename T>
T find_count_painted_boards(std::vector<IntervalBoard<T>> &painted_intervals) noexcept {
    std::sort(painted_intervals.begin(), painted_intervals.end());

    int type_balance = 0;
    std::size_t left_iterator = 0;
    std::size_t right_iterator = 0;
    T amount_painted_boards = 0;

    for (std::size_t i = 0; i < painted_intervals.size(); i++) {
        type_balance += static_cast<int>(painted_intervals.at(i).type);
        if (type_balance == 0) {
            amount_painted_boards +=
                    painted_intervals.at(right_iterator).coordinate - painted_intervals.at(left_iterator).coordinate +
                    1;
            left_iterator = ++right_iterator;
        } else {
            right_iterator++;
        }
    }

    return amount_painted_boards;
}


#include <atomic>
#include <thread>
#include <chrono>

template<typename Function, typename... Args>
std::atomic_bool &set_interval(const std::chrono::milliseconds &interval, Function function, Args... args) {

    std::atomic_bool is_running = true;
    auto callback = [Func = std::forward<Function>(function)] { return Func(); };
    std::thread thread([=, &is_running] {
        while (is_running) {
            std::this_thread::sleep_for(interval);
            callback();
        }
    });
    thread.detach();
    return is_running;
}

int main(int argc, char **argv) {
    std::atomic_bool &is_running = set_interval(std::chrono::milliseconds(5000), [] {
        std::cout << "Hello world" << std::endl;
    });

    std::this_thread::sleep_for(std::chrono::milliseconds(25000));
    return EXIT_SUCCESS;
}
