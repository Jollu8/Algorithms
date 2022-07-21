///// @Jollu
// PING_PONG

#include <atomic>
#include <thread>
#include <string>
#include <cstdint>
#include <iostream>


const bool PING_STATE = true;
const bool PONG_STATE = false;
const size_t COUNT_MESSAGES = 500;

std::atomic<bool> flag{true};

void write_message(const std::string &message, bool current_state) {
    u_int16_t counter = 0;
    while (counter != COUNT_MESSAGES) {
        if (current_state == flag.load()) {
            std::cout << message << std::endl;
            flag.store(!current_state);
            counter++;
        } else std::this_thread::yield();
    }
}


int main() {
    std::thread t1(write_message, "ping", PING_STATE);
    std::thread t2(write_message, "pong", PONG_STATE);
    t1.detach();
    t2.join();
}
