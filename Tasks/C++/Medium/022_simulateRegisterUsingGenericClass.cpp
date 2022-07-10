//Задание 3. Реестр данных на шаблонах
//
//
//Что нужно сделать
//        С помощью шаблонов реализуйте простой класс реестра, хранящий произвольные типы значений по ключам произвольного типа. Ключи могут повторяться.
//
//Реестр должен поддерживать следующие операции: добавление элемента с ключом, удаление элемента по ключу, вывод всех значений с ключами в консоль, поиск элемента по ключу.
//
//Данный словарь должен работать на значениях и ключах следующих типов: int, double, std::string.
//
//Для тестирования программы предусмотрите ввод данных и команд из стандартной консоли:
//
//add — добавить элемент с ключом;
//remove — удалить элемент по ключу;
//print — напечатать на экране все элементы с их ключами;
//find — найти элемент по ключу.
//
//
//Советы и рекомендации
//        Для реализации вы можете использовать стандартный шаблон std::vector, который будет хранить ваши шаблонизированные пары ключей и значений.



#include <iostream>
#include <vector>
#include <fstream>

namespace reg {
    template<typename T1, typename T2>
    class Register {
    public:

        template<class K, class V>
        struct Pair {
            K _key;
            V _value;

            Pair() : _key(K()), _value(V()) {}
        };

    private:
        std::vector<Pair<T1, T2>> _reg;

        int binary_get_index(const T1 &key) const {
            if (_reg.empty())
                return -1;

            int low = 0;
            int high = static_cast<int>(_reg.size());
            high -= 1;
            while (low <= high) {
                int midle = (low + high) / 2;
                Pair<T1, T2> el = _reg[static_cast<std::size_t>(midle)];
                if (el._key == key)
                    return midle;
                if (el._key > key) {
                    high = midle - 1;
                } else {
                    low = midle + 1;
                }
            }
            return -1;
        }

    public:
        Register() {}

        Register(const T1 &key, const T2 &value) {
            add(key, value);
        }

        Pair<T1, T2> add(const T1 &key, const T2 &value) {
            Pair<T1, T2> pair;
            pair._key = key;
            pair._value = value;
            _reg.push_back(pair);
            return _reg.back();
        }

        T2 &operator[](const T1 &key) {
            for ([[maybe_unused]] Pair<T1, T2> &pair: _reg) {
                if (pair._key == key)
                    return pair._value;
            }
            add(key, T2());
            return _reg.back()._value;
        }

        void print() const {
            for ([[maybe_unused]] const Pair<T1, T2> &pair: _reg)
                std::cout << pair._key << " " << pair._value << std::endl;
        }

        T2 find(const T1 &key) const {
            int index = binary_get_index(key);
            if (index == -1)
                return T2();
            return _reg[static_cast<std::size_t>(index)]._value;
        }

        void remove(const T1 &key) {
            int index = binary_get_index(key);
            _reg.erase(_reg.begin() + index);
        }

    };

    void testToFile() {
        std::ofstream oFile("test.txt");
        reg::Register<std::string, int> reg("test", 20);
        reg["test2"] = 56;
        reg["test56"] = 156;
        reg["tes"] = 362;
        reg.print();

        oFile << "Find: " << reg.find("test") << std::endl;
        reg.remove("test56");
        reg.print();

        reg::Register<double, double> re(2.0, 1.2);
        re.add(13.321, 23.434);
        re.print();
        oFile << "Find: " << re.find(13.321) << std::endl;
        re.remove(2.0);
        oFile << "Find: " << re.find(0) << std::endl;
        re.print();
        oFile.close();
    }

    void testRead() {

        reg::Register<std::string, int> reg("test", 20);
        reg["test2"] = 56;
        reg["test56"] = 156;
        reg["tes"] = 362;
        reg.print();

        std::cout << "Find: " << reg.find("test") << std::endl;
        reg.remove("test56");
        reg.print();

        reg::Register<double, double> re(2.0, 1.2);
        re.add(13.321, 23.434);
        re.print();
        std::cout << "Find: " << re.find(13.321) << std::endl;
        re.remove(2.0);
        std::cout << "Find: " << re.find(0) << std::endl;
        re.print();
    }

}

int main() {
    reg::testRead();

}