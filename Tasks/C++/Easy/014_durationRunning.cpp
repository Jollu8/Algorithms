//
// Created by jollu on 12/17/21.
//

//Easy: Задание №1
//Напишите программу, вычисляющую скорость, с которой бегун пробежал дистанцию.
//
//Пример результата выполнения программы:
//
//Введите длину дистанции (м): 1000
//Введите время (минут.секунд): 3.25
//Вы бежали со скоростью 17.56 км/час

#include <stdio.h>
#include <iostream>
#include <cmath>

using namespace std;


double res(double dist, int temp_buff, double run_time) {
    temp_buff = run_time;
    return dist / ((temp_buff * 60 + (run_time - temp_buff) * 100) / 3.6);
}

int main() {
    double dist = 0;
    double result = 0;
    cout << "Distance, metr: ";
    cin >> dist;
    double run_time = 0;
    int temp_buff = 0;
    cout << "Time, min.sec: ";
    cin >> run_time;
    result = res(dist, temp_buff, run_time);
    cout << "You speed run: " << round(result * 100) / 100 << " km/h" << endl;
}
