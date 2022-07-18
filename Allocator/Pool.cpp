///// @Jollu
// Pool Allocator

#include <iostream>
#include <stdexcept>

class PoolAllocator {
    size_t totalSize_ = 0;
    size_t chunkSize_ = 0;
    size_t memoryUsed_ = 0;
    void *basePointer_ = nullptr;
    struct Chunk {
        Chunk *next_;
    } *pChunk = nullptr;
public:
    explicit PoolAllocator(size_t memorySize, size_t chunkSize);

    explicit PoolAllocator(PoolAllocator &&other) noexcept;

    PoolAllocator &operator=(PoolAllocator &&other) noexcept;

    explicit PoolAllocator(const PoolAllocator &other) = delete;

    PoolAllocator operator=(const PoolAllocator &other) = delete;

    void *allocate(size_t chunkSize);

    void deallocate(void *pVoid) noexcept;

    ~PoolAllocator();
};

PoolAllocator::PoolAllocator(size_t memorySize, size_t chunkSize)
        :
        totalSize_(memorySize), chunkSize_(chunkSize) {
    if (totalSize_ == 0 || chunkSize_ == 0) throw std::runtime_error("Could not allocate 0 byte of the memory!");

    basePointer_ = malloc(totalSize_);
    if (!basePointer_) throw std::runtime_error("Memory was not allocated for allocator!");

    for (auto i = 0; i < memorySize / chunkSize; ++i) {
        auto chunkAddress = reinterpret_cast<size_t>(basePointer_) + i * chunkSize_;
        auto *newFreeChunk = reinterpret_cast<Chunk *>(chunkAddress);
        newFreeChunk->next_ = pChunk;
        pChunk = newFreeChunk;
    }
}

PoolAllocator::PoolAllocator(PoolAllocator &&other) noexcept {
    totalSize_ = other.totalSize_;
    chunkSize_ = other.chunkSize_;
    memoryUsed_ = other.memoryUsed_;
    basePointer_ = other.basePointer_;
    other.basePointer_ = nullptr;
    other.memoryUsed_ = other.chunkSize_ = other.totalSize_ = 0;
}

PoolAllocator &PoolAllocator::operator=(PoolAllocator &&other) noexcept {
    if (this != &other) {
        totalSize_ = other.totalSize_;
        chunkSize_ = other.chunkSize_;
        memoryUsed_ = other.memoryUsed_;
        basePointer_ = other.basePointer_;
        other.basePointer_ = nullptr;
        other.memoryUsed_ = other.chunkSize_ = other.totalSize_ = 0;
    }
    return *this;
}

void *PoolAllocator::allocate(size_t chunkSize) {
    if (chunkSize_ != chunkSize) {
        throw std::invalid_argument("Incorrect chunk size for allocator!");
    }

    if (memoryUsed_ + chunkSize_ > totalSize_) return nullptr;

    memoryUsed_ += chunkSize_;
    auto *freeChunk = pChunk;
    pChunk = pChunk->next_;
    return reinterpret_cast<void *>(freeChunk);
}

void PoolAllocator::deallocate(void *pVoid) noexcept {
    if (memoryUsed_ == 0) return;

    memoryUsed_ -= chunkSize_;
    auto newFreeChunk = reinterpret_cast<Chunk *>(pVoid);
    newFreeChunk->next_ = pChunk;
    pChunk = newFreeChunk;
}

PoolAllocator::~PoolAllocator() {
    free(basePointer_);
}

int main() {
    struct Foo {
        double a, b, c, d;
    };
    try {
        PoolAllocator allocator(sizeof(Foo) * 3, sizeof(Foo));
        Foo *f1 = static_cast<Foo *>(allocator.allocate(sizeof(Foo)));
        Foo *f2 = static_cast<Foo *>(allocator.allocate(sizeof(Foo)));
        Foo *f3 = static_cast<Foo *>(allocator.allocate(sizeof(Foo)));

        allocator.deallocate(f3);
        allocator.deallocate(f2);
        allocator.deallocate(f1);
    } catch (const std::exception &e) {
        std::cerr << "Error! Cause: " << e.what() << std::endl;
    }
};