//
// Created by zholu on 06/11/2021.
//
#include <chrono>
#include <mutex>
#include <iostream>
#include <string>
#include <vector>
#include <thread>

class Train {
    std::string m_name = "unknown";
    int m_time = 0;
    bool m_arrived = false;
public:
    Train(std::string in_name, int in_time);

    [[maybe_unused]] int getTime(int x);

    int arriving();


    bool setArrival();

    bool getArrival();

    std::string getName();

    [[maybe_unused]] std::string setName(std::string foo);
};


void comeToRailwayStation(Train myTrain);

[[maybe_unused]] bool allDepart();


std::vector<bool> railwayStation = {false, false, false};
std::mutex railwayStation_access;


Train::Train(std::string in_name, int in_time) {
    m_time = in_time;
    m_name = in_name;
}

[[maybe_unused]] int Train::getTime(int x) {
    return m_time = x;
}

int Train::arriving() {
    return m_time -= 1;
}

bool Train::getArrival() {
    return m_arrived;
}

bool Train::setArrival() {
    if (m_time == 0) return m_arrived = true;
    else return m_arrived = false;
}


std::string Train::getName() {
    return m_name;
}


// =========================================================================
void comeToRailwayStation(Train myTrain) {
    myTrain.setArrival();
    while (!myTrain.getArrival()) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        myTrain.arriving();
        myTrain.setArrival();
    }
    railwayStation_access.lock();
    std::cout << "Train " << myTrain.getName() << " is arrived " << std::endl;
    std::cout << "Waiting for depart. PLease enter a command depart" << std::endl;
    std::string buffer;
    std::cin >> buffer;
    while (buffer != "depart") {
        std::cout << " Incorrect input command, please try again " << std::endl;
        std::cin >> buffer;
    }
    for (int i = 0; i < railwayStation.size(); i++) {
        if (railwayStation[i] == false) {
            railwayStation[i] = true;
            break;
        }
    }
    railwayStation_access.unlock();
}


int main() {

    std::vector<std::string> name;
    std::string temp;
    int time[3];
    for (int i = 0; i < 3; i++) {
        std::cout << "Please enter name and travel time for " << i + 1 << "train" << std::endl;
        std::cin >> temp >> time[i];
        name.push_back(temp);
    }
    class Train A(name[0], time[0]);
    class Train B(name[1], time[1]);
    class Train C(name[2], time[2]);
    std::thread run1(comeToRailwayStation, A);
    std::thread run2(comeToRailwayStation, B);
    std::thread run3(comeToRailwayStation, C);
    run1.join();
    run2.join();
    run3.join();

}