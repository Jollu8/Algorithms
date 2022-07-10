//
// Created by jollu on 12/17/21.
//

//Easy: Задание №1
//Напишите программу вычисления стоимости поездки на автомобиле на дачу (туда и обратно). Исходными данными являются:
//
//расстояние до дачи (в км);
//
//литраж бензина, который потребляет автомобиль на 100 км пробега;
//
//цена одного литра бензина.
//
//Пример результата выполнения программы:
//
//Расстояние до дачи (км): 67
//Расход бензина (литров на 100 км пробега): 8.5
//Цена литра бензина (руб.): 50
//Поездка на дачу и обратно обойдется в 284.75 руб.

#include <iostream>


double count(double d, double g, double p) {
    return g * (d / 100) * p * 2;
}

int main() {
    double distance;
    double gasoline;
    double priceGas;

    std::cout << "Distance to the cottage (km): \n>";
    std::cin >> distance;
    std::cout << "Gasoline consumption (liters per 100 km of run):\n>";
    std::cin >> gasoline;
    std::cout << "Price per liter of gasoline (rub.): \n>";
    std::cin >> priceGas;
    while (distance <= 0 && gasoline <= 0 && priceGas <= 0) {
        std::cout << "Error  less than zero!\n";
        std::cout << "Distance to the cottage (km): \n>";
        std::cin >> distance;
        std::cout << "Gasoline consumption (liters per 100 km of run):\n>";
        std::cin >> gasoline;
        std::cout << "Price per liter of gasoline (rub.): \n>";
        std::cin >> priceGas;
    }
    double totalPrice = count(distance, gasoline, priceGas);
    std::cout << "A trip to the country house and back will cost " << totalPrice << std::endl;
}
