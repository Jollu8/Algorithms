#pragma once

#include <cassert>
#include <cstddef>
#include <initializer_list>
#include <iterator>
#include <utility>
#include <algorithm>

template<typename Type>
class SingleLinkedList {
    struct Node {
        Node() = default;

        Node(const Type &val, Node *next)
            : value(val), next_node(next) {
        }

        Type value;
        Node *next_node = nullptr;
    };

    template<typename ValueType>
    class BasicIterator {
        friend class SingleLinkedList;

        explicit BasicIterator(Node *node)
            : node_(node) {
        }

    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = Type;
        using difference_type = std::ptrdiff_t;
        using pointer = ValueType *;
        using reference = ValueType &;

        BasicIterator() = default;

        BasicIterator(const BasicIterator<Type> &other) noexcept
            : BasicIterator(other.node_) {
        }

        BasicIterator &operator=(const BasicIterator &rhs) = default;

        [[nodiscard]] bool operator==(const BasicIterator<const Type> &rhs) const noexcept {
            bool result = (node_ == rhs.node_ ? 1 : 0);
            return result;
        }

        [[nodiscard]] bool operator!=(const BasicIterator<const Type> &rhs) const noexcept {
            bool result = (node_ == rhs.node_ ? 0 : 1);
            return result;
        }

        [[nodiscard]] bool operator==(const BasicIterator<Type> &rhs) const noexcept {
            bool result = (node_ == rhs.node_ ? 1 : 0);
            return result;
        }

        [[nodiscard]] bool operator!=(const BasicIterator<Type> &rhs) const noexcept {
            bool result = (node_ == rhs.node_ ? 0 : 1);
            return result;
        }

        BasicIterator &operator++() noexcept {
            // Node var = *node_;
            node_ = node_->next_node;
            return *this;
        }

        BasicIterator operator++(int) noexcept {
            BasicIterator var(node_);
            node_ = node_->next_node;
            return var;
        }

        [[nodiscard]] reference operator*() const noexcept {
            reference var = node_->value;
            return var;
        }

        [[nodiscard]] pointer operator->() const noexcept {
            pointer var = &(node_->value);
            return var;
        }

    private:
        Node *node_ = nullptr;
    };

public:
    SingleLinkedList() {
    }

    SingleLinkedList(const SingleLinkedList &other)
        : SingleLinkedList(other.begin(), other.end()) {
    }

    SingleLinkedList(std::initializer_list<Type> values)
        : SingleLinkedList(values.begin(), values.end()) {
    }

    template<typename iter>
    SingleLinkedList(iter beginIter, iter endIter) {
        SingleLinkedList copy;
        for (auto i = beginIter; i != endIter; i++) {
            copy.push_front(*i);
        }
        SingleLinkedList copy_copy;
        for (auto i = copy.begin(); i != copy.end(); i++) {
            copy_copy.push_front(*i);
        }
        swap(copy_copy);
    }

    SingleLinkedList &operator=(const SingleLinkedList &rhs) {
        SingleLinkedList copy(rhs);
        swap(copy);
        return *this;
    }

    using value_type = Type;
    using reference = value_type &;
    using const_reference = const value_type &;
    using Iterator = BasicIterator<Type>;
    using ConstIterator = BasicIterator<const Type>;

    void push_front(const Type &value) {
        head_.next_node = new Node(value, head_.next_node);
        ++size_;
    }

    void clear() noexcept {
        do {
            Node *must_be_del_node = head_.next_node;
            head_.next_node = must_be_del_node->next_node;
            delete must_be_del_node;
        } while (head_.next_node != nullptr);
        size_ = 0u;
    }

    [[nodiscard]] size_t get_size() const noexcept {
        return size_;
    }

    [[nodiscard]] bool is_empty() const noexcept {
        bool result = (get_size() == 0u ? 1 : 0);
        return result;
    }

    ~SingleLinkedList() {
        if (size_ != 0u) {
            clear();
        }
    }

    [[nodiscard]] Iterator begin() noexcept {
        if (size_ == 0u) {
            return end();
        }
        return Iterator(head_.next_node);
    }

    [[nodiscard]] Iterator end() noexcept {
        return Iterator(NULL);
    }

    [[nodiscard]] ConstIterator begin() const noexcept {
        return cbegin();
    }

    [[nodiscard]] ConstIterator end() const noexcept {
        return cend();
    }

    [[nodiscard]] ConstIterator cbegin() const noexcept {
        if (size_ == 0u) {
            return cend();
        }
        return ConstIterator(head_.next_node);
    }

    [[nodiscard]] ConstIterator cend() const noexcept {
        return ConstIterator(NULL);
    }

    void swap(SingleLinkedList &other) noexcept {
        auto head_var = head_.next_node;
        auto var_size = size_;

        head_.next_node = other.head_.next_node;
        size_ = other.size_;

        other.head_.next_node = head_var;
        other.size_ = var_size;
    }

    [[nodiscard]] Iterator before_begin() noexcept {
        return Iterator(&head_);
    }

    [[nodiscard]] ConstIterator cbefore_begin() const noexcept {
        return ConstIterator(const_cast<SingleLinkedList<Type>::Node *>(&head_));
    }

    [[nodiscard]] ConstIterator before_begin() const noexcept {
        return cbefore_begin();
    }

    Iterator insert_after(ConstIterator pos, const Type &value) {
        //assert(pos.node_ != nullptr);
        Node *node_to_insert_after = pos.node_;
        Node *new_node = new Node(value, node_to_insert_after->next_node);
        node_to_insert_after->next_node = new_node;
        ++size_;
        return Iterator(new_node);
    }

    void pop_front() noexcept {
        Node *must_be_del_node = head_.next_node;
        head_.next_node = must_be_del_node->next_node;
        delete must_be_del_node;
        size_--;
    }

    Iterator erase_after(ConstIterator pos) noexcept {
        Node *node_to_erase_after = pos.node_;
        Node *var = node_to_erase_after->next_node;
        node_to_erase_after->next_node = node_to_erase_after->next_node->next_node;
        delete var;
        size_--;
        return Iterator(node_to_erase_after->next_node);
    }

private:
    Node head_;
    size_t size_ = 0u;
};

template<typename Type>
void swap(SingleLinkedList<Type> &lhs, SingleLinkedList<Type> &rhs) noexcept {
    lhs.swap(rhs);
}

template<typename Type>
bool operator==(const SingleLinkedList<Type> &lhs, const SingleLinkedList<Type> &rhs) {
    bool result = std::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()) ? 1 : 0;
    return result;
}

template<typename Type>
bool operator!=(const SingleLinkedList<Type> &lhs, const SingleLinkedList<Type> &rhs) {
    bool result = lhs == rhs ? 0 : 1;
    return result;
}

template<typename Type>
bool operator<(const SingleLinkedList<Type> &lhs, const SingleLinkedList<Type> &rhs) {
    bool result = std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()) ? 1 : 0;
    return result;
}

template<typename Type>
bool operator<=(const SingleLinkedList<Type> &lhs, const SingleLinkedList<Type> &rhs) {
    return lhs < rhs || lhs == rhs;
}

template<typename Type>
bool operator>(const SingleLinkedList<Type> &lhs, const SingleLinkedList<Type> &rhs) {
    return !(lhs < rhs);
}

template<typename Type>
bool operator>=(const SingleLinkedList<Type> &lhs, const SingleLinkedList<Type> &rhs) {
    return !(lhs < rhs);
}
