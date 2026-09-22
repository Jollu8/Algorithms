///// @Jollu
// Unique Pointer


#include <iostream>

template<typename T>
class UniquePtr {
    T *pointer_;
public:
    explicit UniquePtr(T *p) noexcept: pointer_(p) {}

    explicit UniquePtr(const UniquePtr &other) = delete;

    UniquePtr &operator=(const UniquePtr &other) = delete;

    explicit UniquePtr(UniquePtr &&other) noexcept;

    UniquePtr &operator=(UniquePtr &&other) noexcept;

    T operator*() const noexcept;

    T *operator->() const noexcept;

    operator bool() const noexcept;

    T *get() const noexcept;

    T *release() noexcept;

    void reset(T *p = nullptr) noexcept;

    ~UniquePtr();

    bool operator<(const UniquePtr &rhs) const;

    bool operator>(const UniquePtr &rhs) const;

    bool operator<=(const UniquePtr &rhs) const;

    bool operator>=(const UniquePtr &rhs) const;
};

template<typename T>
UniquePtr<T>::UniquePtr(UniquePtr &&other) noexcept {
    pointer_ = other.pointer_;
    other.pointer_ = nullptr;
}

template<typename T>
UniquePtr<T> &UniquePtr<T>::operator=(UniquePtr &&other) noexcept {
    if (this != &other) {
        delete pointer_;
        pointer_ = other.pointer_;
        other.pointer_ = nullptr;
    }
    return *this;
}


template<typename T>
T UniquePtr<T>::operator*() const noexcept {
    return *pointer_;
}

template<typename T>
bool UniquePtr<T>::operator<(const UniquePtr &rhs) const {
    return pointer_ < rhs.pointer_;
}

template<typename T>
bool UniquePtr<T>::operator>(const UniquePtr &rhs) const {
    return rhs < *this;
}

template<typename T>
bool UniquePtr<T>::operator<=(const UniquePtr &rhs) const {
    return !(rhs < *this);
}

template<typename T>
bool UniquePtr<T>::operator>=(const UniquePtr &rhs) const {
    return !(*this < rhs);
}

template<typename T>
T *UniquePtr<T>::operator->() const noexcept {
    return pointer_;
}

template<typename T>
UniquePtr<T>::operator bool() const noexcept {
    return pointer_ != nullptr;
}

template<typename T>
T *UniquePtr<T>::get() const noexcept {
    return pointer_;
}

template<typename T>
T *UniquePtr<T>::release() noexcept {
    T *tmp = pointer_;
    pointer_ = nullptr;
    return tmp;
}

template<typename T>
void UniquePtr<T>::reset(T *p) noexcept {
    delete pointer_;
    pointer_ = p;
}

template<typename T>
UniquePtr<T>::~UniquePtr() {
    delete pointer_;
}

int main() {
    struct Vector2d {
        double x, y;
    };

    UniquePtr<Vector2d> ptr1(new Vector2d());
    UniquePtr<Vector2d> ptr2(std::move(ptr1));
    std::cout << "x: " << ptr2->x << " y: " << ptr2->y << std::endl;
}