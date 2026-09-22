///// @Jollu
// Shared Pointer


#include <cstdint>
#include <iostream>


template<typename T>
class SharedPtr {
    T *pointer_;
    u_int16_t *referenceCount_;
public:
    explicit SharedPtr(T *p) noexcept: pointer_(p), referenceCount_(new u_int16_t(1)) {}

    explicit SharedPtr(const SharedPtr &other) noexcept;

    SharedPtr &operator=(const SharedPtr &other) noexcept;

    T operator*() const noexcept;

    T *operator->() const noexcept;

    operator bool() const noexcept;

    T *get() const noexcept;

    bool isUnique() const noexcept;

    uint16_t getReferencesCount() const noexcept;

    void reset(T *p = nullptr) noexcept;

    ~SharedPtr();
};

template<typename T>
SharedPtr<T>::SharedPtr(const SharedPtr &other) noexcept {
    pointer_ = other.pointer_;
    referenceCount_ = other.referenceCount_;
    (*referenceCount_)++;
}

template<typename T>
SharedPtr<T> &SharedPtr<T>::operator=(const SharedPtr<T> &other) noexcept {
    if (this != &other) {
        (*referenceCount_)--;
        if (*referenceCount_ == 0) delete pointer_;
        pointer_ = other.pointer_;
        (*referenceCount_)++;
    }
    return *this;
}

template<typename T>
T SharedPtr<T>::operator*() const noexcept {
    return pointer_;
}

template<typename T>
T *SharedPtr<T>::operator->() const noexcept {
    return pointer_;
}

template<typename T>
SharedPtr<T>::operator bool() const noexcept {
    return pointer_ != nullptr;
}

template<typename T>
T *SharedPtr<T>::get() const noexcept {
    return pointer_;
}

template<typename T>
bool SharedPtr<T>::isUnique() const noexcept {
    return *referenceCount_ == 1;
}

template<typename T>
u_int16_t SharedPtr<T>::getReferencesCount() const noexcept {
    return *referenceCount_;
}

template<typename T>
void SharedPtr<T>::reset(T *p) noexcept {
    (*referenceCount_)--;
    if (*referenceCount_ == 0) {
        delete pointer_;
        delete referenceCount_;
    }
    if (pointer_) {
        pointer_ = pointer_;
        referenceCount_ = new u_int16_t(1);
    }
}

template<typename T>
SharedPtr<T>::~SharedPtr() {
    (*referenceCount_)--;
    if (*referenceCount_ == 0) {
        delete pointer_;
        delete referenceCount_;
    }
}

int main() {
    struct Foo {
        double a, b;
    };

    SharedPtr<Foo> f1(new Foo());
    SharedPtr<Foo> f2(f1);
    std::cout << "a: " << f2->a << " b: " << f2->b << std::endl;
}
