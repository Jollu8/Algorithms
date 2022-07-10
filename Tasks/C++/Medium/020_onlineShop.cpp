//Задание 1. Работа корзины с покупками
//
//
//Что нужно сделать
//        Реализуйте простую и безопасную модель работы корзины онлайн-магазина.
//
//В начале программы вы заполняете базу данных самого магазина через стандартную консоль. Каждый элемент этой базы данных состоит из двух компонентов — артикула и количества штук.
//Корзина должна поддерживать следующие операции: добавление товара с указанным его количеством — add, удаление товара с указанным количеством — remove. Обе операции принимают артикул товара в виде строки и количество в виде целого числа.
//При вводе аргументов к операциям должна осуществляться их валидация. Артикул должен быть в базе данных магазина, количество не должно превышать количество доступного продукта на складе (при удалении — в корзине).
//
//
//Советы и рекомендации
//        В качестве контейнера для базы данных и самой корзины можете использовать std::map

#include <string>
#include <map>
#include <exception>
#include <iostream>
#include <iomanip>

class exception_shop : std::exception {
    std::string _message;

public:
    exception_shop(const std::string &message) : _message(message) {}

    const char *what() const noexcept override {

        return _message.c_str();
    }
};

class Shop {

    std::map<std::string, std::size_t> _shop;
    std::size_t _setw = 0;

public:
    Shop() = default;

    ~Shop() = default;

    Shop(const Shop &other) = default;

    Shop &operator=(Shop &other) = default;

    void insert(const std::string &article, std::size_t count) {
        if (count == SIZE_MAX)
            throw exception_shop("Error count");

        auto it_find = _shop.find(article);

        if (it_find != _shop.end()) {
            throw exception_shop("Such an article [" + article + "] already exists, use \"ADD\" to add the product");
        } else {
            _shop.insert(std::make_pair(article, count));
            _setw = std::max(_setw, article.size());
        }
    }

    void add(const std::string &article, std::size_t count) {
        if (count == SIZE_MAX)
            throw exception_shop("Error count");

        auto it_find = _shop.find(article);

        if (it_find != _shop.end()) {
            it_find->second += count;
        } else {
            throw exception_shop("Article " + article + " not found");
        }
    }

    void remove(const std::string &article, std::size_t count) {
        if (count == SIZE_MAX)
            throw exception_shop("Error count");

        auto it_find = _shop.find(article);

        if (it_find != _shop.end()) {
            if (count > it_find->second) {
                throw exception_shop("Error: The quantity being deleted is larger than the existing one");
            } else {
                it_find->second -= count;
            }

        } else {
            throw exception_shop("Article " + article + " not found");
        }
    }

    std::size_t count_article(const std::string &article) const {
        auto it_find = _shop.find(article);

        if (it_find != _shop.end()) {
            return it_find->second;
        } else {
            throw exception_shop("Article [" + article + "] not found");
        }
    }

    //Return size article
    std::size_t count_product() const {
        return _shop.size();
    }


    //Show database
    void show() const {

        for (auto it = _shop.begin(); it != _shop.end(); ++it) {
            std::cout << std::setw(static_cast<int>(_setw)) << std::left
                      << it->first << " : " << it->second << std::endl;
        }
    }
};

int main() {
    Shop shop;

    std::cout << "Enter database shop: " << std::endl;
    std::string article;
    std::size_t count;
    do {
        std::cout << "Insert [Article] and [count]:" << std::endl;
        std::cin >> article;
        if (article != "end") {
            std::cin >> count;
            try {
                shop.insert(article, count);
            }
            catch (const exception_shop &e) {
                std::cerr << e.what() << '\n';
            }

            std::cout << "Enter [end] to complete:" << std::endl;
        }

    } while (article != "end");

    if (shop.count_product() == 0) {
        std::cout << "The database has been empty, exit to program..." << std::endl;
        return 0;
    }

    std::cout << "The database has been created, use [add], [remove], [exit] to work" << std::endl;
    shop.show();

    do {
        std::cout << ">> ";
        std::cin >> article;
        if (article == "add") {
            std::cout << "Enter name article for add count: ";
            std::cin >> article;
            std::cout << "Enter count: ";
            std::cin >> count;
            try {
                shop.add(article, count);
                shop.show();
            }
            catch (const exception_shop &e) {
                std::cerr << e.what() << '\n';
            }
            catch (const std::exception &e) {
                std::cerr << e.what();
                return 100;
            }

        } else if (article == "remove") {
            std::cout << "Enter name article for remove count: ";
            std::cin >> article;
            std::cout << "Enter count: ";
            std::cin >> count;
            try {
                shop.remove(article, count);
                shop.show();
            }
            catch (const exception_shop &e) {
                std::cerr << e.what() << '\n';
            }
            catch (const std::exception &e) {
                std::cerr << e.what();
                return 100;
            }
        }

    } while (article != "end");
    std::cout << "The database close" << std::endl;
}
