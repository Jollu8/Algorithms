

//
// Created by zholu on 06/11/2021.
//

#include <iostream>
#include <vector>
#include <mutex>
#include <thread>


enum {
    CHICKEN,
    SOUP,
    STAKE,
    SALAD,
    SUSHI
};

std::mutex order_access;
std::mutex kitchen_access;


void print_order(int order) {
    if (order == CHICKEN) {
        std::cout << "Waiter: Order on CHICKEN received" << std::endl;
    } else if (order == SOUP) {
        std::cout << "Waiter: Order on SOUP received" << std::endl;
    } else if (order == STAKE) {
        std::cout << "Waiter: Order on STAKE received" << std::endl;
    } else if (order == SALAD) {
        std::cout << "Waiter: Order on SALAD received" << std::endl;
    } else if (order == SUSHI) {
        std::cout << "Waiter: Order on SUSHI received" << std::endl;
    }
}

void print_cooked(int order) {
    if (order == CHICKEN) {
        std::cout << "Cook: CHICKEN cooked" << std::endl;
    } else if (order == SOUP) {
        std::cout << "Cook: SOUP cooked" << std::endl;
    } else if (order == STAKE) {
        std::cout << "Cook: STAKE cooked" << std::endl;
    } else if (order == SALAD) {
        std::cout << "Cook: SALAD cooked" << std::endl;
    } else if (order == SUSHI) {
        std::cout << "Cook: SUSHI cooked" << std::endl;
    }
}

void print_delivery(int order) {
    if (order == CHICKEN) {
        std::cout << "Delivery boy: CHICKEN taken in delivery" << std::endl;
    } else if (order == SOUP) {
        std::cout << "Delivery boy: SOUP taken in delivery" << std::endl;
    } else if (order == STAKE) {
        std::cout << "Delivery boy: STAKE taken in delivery" << std::endl;
    } else if (order == SALAD) {
        std::cout << "Delivery boy: SALAD taken in delivery" << std::endl;
    } else if (order == SUSHI) {
        std::cout << "Delivery boy: SUSHI taken in delivery" << std::endl;
    }
}

void order(std::vector<int> *online_orders) {
    int order;
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(std::rand() % 6 + 5));
        order = std::rand() % 5;
        order_access.lock();
        online_orders->emplace(online_orders->begin(), order);
        order_access.unlock();
        print_order(order);
    }
}

void kitchen(std::vector<int> *online_orders, std::vector<int> *cooked_orders) {
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(std::rand() % 11 + 5));
        kitchen_access.lock();
        cooked_orders->emplace(cooked_orders->begin(), online_orders->back());
        kitchen_access.unlock();
        print_cooked(online_orders->back());
        order_access.lock();
        online_orders->pop_back();
        order_access.unlock();
    }
}

void delivery(std::vector<int> *cooked_orders) {
    int delivery_count = 0;
    while (delivery_count < 10) {
        std::this_thread::sleep_for(std::chrono::seconds(30));
        for (int i = 0; i < cooked_orders->size(); ++i) {
            print_delivery(cooked_orders->back());
            kitchen_access.lock();
            cooked_orders->pop_back();
            kitchen_access.unlock();
            delivery_count++;
        }
    }
}


int main() {
    std::srand(std::time(nullptr));
    std::vector<int> online_orders;
    std::vector<int> cooked_orders;
    std::thread thOrders(order, &online_orders);
    thOrders.detach();
    std::thread thKitchen(kitchen, &online_orders, &cooked_orders);
    thKitchen.detach();
    std::thread thDelivery(delivery, &cooked_orders);
    thDelivery.join();
    std::cout << "Work is done";
}