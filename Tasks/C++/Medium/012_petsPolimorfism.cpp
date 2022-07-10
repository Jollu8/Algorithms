//
// Created by zholu on 07/11/2021.
//



#include <iostream>

class Animal {
public:
    std::string _voice_type;

    virtual void voice() = 0;
};

class Dog : virtual public Animal {
public:
    Dog() {
        _voice_type = "Bark";
    }

    void voice() override {
        std::cout << "Bark";
    }
};

class Cat : virtual public Animal {
public:
    Cat() {
        _voice_type = "Meow";
    }

    void voice() override {
        std::cout << "Meow";
    }
};

void meeting(Animal *one, Animal *two) {
    std::string sound = one->_voice_type + " " + two->_voice_type;
    if (sound == "Meow Meow") {
        std::cout << "Purr Purr" << std::endl;
    } else if (sound == "Bark Bark") {
        std::cout << "Woof Woof" << std::endl;
    } else {
        std::cout << sound << std::endl;
    }
}

int main() {
    __attribute__((unused)) Animal *a = new Cat();
    Animal *c = new Dog();
    Animal *b = new Dog();
    meeting(b, c);
    return 0;
}