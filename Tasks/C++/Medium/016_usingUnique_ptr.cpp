

#include<iostream>
#include<string>
#include<cassert>
#include <utility>

class Toy
{
public:
    explicit Toy(std::string name) : _name(std::move(name)) {};
    Toy() : _name("SomeToy") {};
    [[nodiscard]] std::string name() const {
        return _name;
    }
private:
    std::string _name;
};


class shared_ptr_toy
{
private:
    Toy* obj = nullptr;
    int* counter = nullptr;

    void init() {
        assert(counter == nullptr);
        counter = new int(1);
    }

    void decrease() {
        if(--*counter == 0) {
            std::cerr << "Delete toy with name " << (obj == nullptr ? "Empty" : obj->name())<<std::endl;
            delete obj;
            delete counter;
        }
    }

public:
    shared_ptr_toy(): obj(new Toy("SomeName"))
    {
        init();
    }

    explicit shared_ptr_toy(std::string name): obj(new Toy(std::move(name)))
    {
        init();
    }

    explicit shared_ptr_toy(Toy* ptr): obj(ptr)
    {
        init();
    }

    shared_ptr_toy(const shared_ptr_toy& oth): obj(oth.obj), counter(oth.counter)
    {
        ++*counter;
    }

    shared_ptr_toy& operator=(const shared_ptr_toy& oth)
    {
        if (counter != oth.counter) {
            decrease();

            obj = oth.obj;
            counter = oth.counter;
            ++*counter;
        }

        return *this;
    }

    Toy* operator->() const
    {
        return obj;
    }

    ~shared_ptr_toy()
    {
        decrease();
    }
};

template<typename ... Args>
shared_ptr_toy make_shared_toy(Args&&... args)
{
    return shared_ptr_toy(std::forward<Args>(args)...);
}

int main() {

    shared_ptr_toy null1(nullptr);
    shared_ptr_toy null5(nullptr);
    auto null2 = null1;

    auto p = make_shared_toy("Ball");
    null2 = null1 = p;

    std::cout<<null2->name()<<std::endl;
}