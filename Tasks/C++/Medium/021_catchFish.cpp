//
//Задание 2. Симуляция ловли рыбы
//
//
//        Что нужно сделать
//Реализуйте простую игру-симуляцию ловли рыбы. Игровое поле представляет собой девять секторов условного пруда. В начале игры в одном из этих секторов с помощью генератора случайных чисел оказывается рыба. Точно так же, случайным образом, распределяются и три сапога. Сапог и рыба при этом не могут находиться в одном и том же секторе одновременно, как и несколько сапог сразу.
//
//Игрок закидывает удочку с приманкой в один из секторов, номер которого вводится стандартным способом через консоль. Задача игрока — угадать сектор, в котором находится рыба и, таким образом, поймать её. Если игрок попал на пустой сектор, то удочку надо забросить повторно. Если игрок поймал сапог, то игра завершается с отрицательным результатом.
//
//Реализовать задачу нужно с помощью исключений: когда успешный заброс удочки генерирует специальное пользовательское исключение, после чего программа должна завершиться и оповестить пользователя об успешной рыбалке и количестве попыток, которое ему для этого потребовалось. Если же был пойман сапог, то должно выводиться сообщение о неудачной ловле.
//
//
//
//Что оценивается
//Корректность работы игровой логики. Точность использования исключений.

#include <stdexcept>
#include <random>
#include<iostream>
#include <array>
#include <exception>
#include <string>

class exception_fish : std::exception {
    std::string _message;

public:
    exception_fish(const std::string &message) : _message(message) {}

    const char *what() const noexcept override {

        return _message.c_str();
    }
};

class exception_boot : std::exception {
    std::string _message;

public:
    exception_boot(const std::string &message) : _message(message) {}

    const char *what() const noexcept override {

        return _message.c_str();
    }
};


class Fish {
    enum class Items {
        FISH,
        BOOT,
        EMPTY
    };
    int _size_boot = 3;
    mutable int _col_fishing = 1;
    Items _pond[9];

    int random(int a, int b);

public:
    Fish();

    void catchFish(std::size_t pond) const;

    int attempts() const { return _col_fishing; }
};


int Fish::random(int a, int b) {
    std::random_device rd;
    std::mt19937 ran(rd());
    std::uniform_int_distribution<> gen_mt(a, b);
    return gen_mt(ran);
}

Fish::Fish() {
    constexpr auto size_pond = sizeof(_pond) / sizeof(_pond[0]);

    for (std::size_t i = 0; i < size_pond; ++i) {
        _pond[i] = Items::EMPTY;
    }

    _pond[random(0, size_pond - 1)] = Items::FISH;

    int count_pond = 0;

    while (count_pond != _size_boot) {
        const auto rand = random(0, size_pond - 1);
        if (Items::EMPTY == _pond[rand]) {
            _pond[rand] = Items::BOOT;
            ++count_pond;
        }
    }

}

void Fish::catchFish(std::size_t pond) const {
    constexpr auto size_pond = sizeof(_pond) / sizeof(_pond[0]);
    if (pond >= size_pond)
        throw std::out_of_range("Error: fishing sector must be 0 to 8");

    if (_pond[pond] == Items::FISH)
        throw exception_fish("Good job, you caught a fish");

    if (_pond[pond] == Items::BOOT)
        throw exception_boot("Ha ha, you caught the boot");

    if (_pond[pond] == Items::EMPTY) {
        ++_col_fishing;
        throw std::runtime_error("There are no fish here, try again");
    }


}


int main() {
    Fish Simulator;
    bool fish = true;

    while (fish) {
        std::cout << "Enter number pond to fishing: ";
        std::size_t pond;
        std::cin >> pond;
        try {
            Simulator.catchFish(pond);
        }
        catch (const exception_fish &e) {
            std::cout << e.what() << " in " << Simulator.attempts() << " attempts\n";
            fish = false;
        }
        catch (const exception_boot &e) {
            std::cout << e.what() << '\n';
            fish = false;
        }
        catch (const std::runtime_error &e) {
            std::cout << e.what() << '\n';
        }
        catch (const std::exception &e) {
            std::cerr << e.what() << '\n';
        }
    }

    return 0;
}