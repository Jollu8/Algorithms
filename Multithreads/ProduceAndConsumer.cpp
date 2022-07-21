///// @Jollu
// Producer And Consumer

#include <atomic>
#include <thread>
#include <string>
#include <cstdint>
#include <iostream>
#include <queue>
#include <random>
#include <chrono>
#include <ctime>
#include <condition_variable>
#include <mutex>

std::mutex m;
std::condition_variable conditionVariable;

std::queue<int> buffer;


void produce() {
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::unique_lock<std::mutex> lock(m);
        conditionVariable.wait(lock, [&] { return buffer.size() < 2; });
        int generatedValue = 1 + rand() % 50;
        std::cout << "Was  produced: " << generatedValue << std::endl;
        buffer.push(generatedValue);
        conditionVariable.notify_one();
    }
}

void consume() {
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::unique_lock<std::mutex> lock(m);
        conditionVariable.wait(lock, [&] { return !buffer.empty(); });
        std::cout << "Was consumed: " << buffer.front() << std::endl;
        buffer.pop();
        conditionVariable.notify_one();
    }
}

int main() {
    std::thread t1(consume);
    std::thread t2(produce);
    t1.join();
    t2.join();
}