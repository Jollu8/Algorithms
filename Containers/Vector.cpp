#include <iostream>


template<typename T>
class MyVector {
private:
    T *arr_;
    long long capacity; // all reserve memory
    long long length_; //

public:

    explicit MyVector(long long = 100);

    long long push_back(T);

    T pop_back();

    long long size() const;

    T &operator[](long long);

    class Iterator {
        T *ptr_;
    public:
        explicit Iterator() : ptr_(nullptr) {}
        explicit Iterator(T*p) : ptr_(p) {}

        bool operator==(const Iterator &rhs) const {
            return ptr_ == rhs.ptr_;
        }

        bool operator!=(const Iterator &rhs) const {
            return !(*this == rhs);
        }

        T operator*() const {
            return *ptr_;
        }

        Iterator &operator++() {
            ++ptr_;
            return *this;
        }

        Iterator operator++(int) {
            Iterator temp(*this);
            ++*this;
            return temp;
        }
    };

    Iterator begin() const;

    Iterator end() const;
};


template<typename T>
MyVector<T>::MyVector(long long n) : capacity(n), arr_(new T[n]), length_(0) {}

template<typename T>
long long MyVector<T>::push_back(T data) {
    if (length_ == capacity) {
        T *old = arr_;
        arr_ = new T[capacity = capacity * 2];
        std::copy(old, old + length_, arr_);
        delete[]old;
    }
    arr_[length_++] = data;
    return length_;
}

template<typename T>
T MyVector<T>::pop_back() {
    return arr_[length_ - 1];
}

template<typename T>
long long MyVector<T>::size() const {
    return length_;
}

template<typename T>
T& MyVector<T>::operator[](long long index) {
    if(index >= length_) {
        std::cout << "Error: Array index out of  bound";
        exit(0);
    }
    return *(arr_ + index);
}

template<typename T>
typename MyVector<T>::Iterator MyVector<T>::end() const {
    return Iterator(arr_ + length_);
}

template<typename T>
typename MyVector<T>::Iterator MyVector<T>::begin() const {
    return Iterator(arr_);
}

template<typename T>
void display_vector(T&v) {
    typename T::Iterator it;
    for(it = v.begin(); it != v.end(); it++) {
        std::cout << *it << ' ';
    }
    std::cout << std::endl;
}

int main() {
    MyVector<int> vec;
    for(auto i = 0; i < 10; i++) {
        vec.push_back(i);
    }

    display_vector(vec);
}
