#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <vector>

std::vector<std::string> results;
std::mutex results_mtx;

void swim(const std::string& name, double speed)
{
    std::cout << name << " started to swim...";
    double distance = 0;
    while (distance <= 100)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << name << " swam: " << distance << std::endl;
        distance += speed;
    }
    std::cout << name << " finished." << std::endl;
    results_mtx.lock();
    results.push_back(name);
    results_mtx.unlock();
}

int main()
{
    constexpr int n = 6;
    std::vector<std::thread> swimmers;
    std::vector<std::string> names(n);
    std::vector<double> speeds(n);

    std::cout << "Names:";
    for (int i = 0; i < n; ++i) {
        std::cin>>names[i];
    }
    std::cout << "Speeds:";
    for (int i = 0; i < n; ++i) {
        std::cin>>speeds[i];
    }

    for (int i = 0; i < n; ++i) {
        swimmers.emplace_back(swim, names[i], speeds[i]);
    }
    for (int i = 0; i < n; ++i) {
        swimmers[i].join();
    }

    for (int i = 0; i < n; ++i) {
        std::cout << i << ". " << results[i] << std::endl;
    }
}