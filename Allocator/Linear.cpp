///// @Jollu
// Liner Allocator

#include <iostream>
#include <stdexcept>

class LineAllocator {
    size_t memorySize_ = 0;
    size_t memoryOffset_ = 0;
    void *base_pointer = nullptr;

public:
    explicit LineAllocator(size_t memorySize);

    explicit LineAllocator(LineAllocator &&other) noexcept;

    LineAllocator &operator=(LineAllocator &&other) noexcept;

    explicit LineAllocator(const LineAllocator &other) = delete;

    void *allocate(size_t allocateSize) noexcept;

    void deallocate() noexcept;

    ~LineAllocator();

};

LineAllocator::LineAllocator(size_t memorySize) : memorySize_(memorySize) {
    if (memorySize_ == 0) throw std::runtime_error("Could not allocate 0 byte of the memory!");

    base_pointer = malloc(memorySize);
    if (!base_pointer) throw std::runtime_error("Memory was not allocated for allocator!");
}


LineAllocator::LineAllocator(LineAllocator &&other) noexcept {
    memorySize_ = other.memorySize_;
    memoryOffset_ = other.memoryOffset_;
    base_pointer = other.base_pointer;
    other.base_pointer = nullptr;
    other.deallocate();
}

LineAllocator &LineAllocator::operator=(LineAllocator &&other) noexcept {
    if (this != &other) {
        memorySize_ = other.memorySize_;
        memoryOffset_ = other.memoryOffset_;
        base_pointer = other.base_pointer;
        other.base_pointer = nullptr;
        other.deallocate();
    }
    return *this;
}


void *LineAllocator::allocate(size_t allocateSize) noexcept {
    if (memoryOffset_ + allocateSize > memorySize_) return nullptr;

    const size_t allocatedAddress = reinterpret_cast<size_t>(base_pointer) + memoryOffset_;
    memoryOffset_ += allocateSize;
    return reinterpret_cast<void *>(allocatedAddress);
}

void LineAllocator::deallocate() noexcept {
    memorySize_ = memoryOffset_ = 0;
}

LineAllocator::~LineAllocator() {
    free(base_pointer);
}

int main() {
    class Foo {
    public:
        double a, b, c;
    };

    try {
        LineAllocator allocator(sizeof(Foo) *2);
        Foo *vec1 = static_cast<Foo *>(allocator.allocate(sizeof(Foo)));
        Foo *vec2 = static_cast<Foo *>(allocator.allocate(sizeof(Foo)));
        Foo *vec3 = static_cast<Foo *>(allocator.allocate(sizeof(Foo)));
        allocator.deallocate();
    } catch (const std::exception &e) {
        std::cerr << "Error! Cause: " << e.what() << std::endl;
    }

}

