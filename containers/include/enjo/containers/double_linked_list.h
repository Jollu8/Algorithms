#pragma once

#include <cstddef>


template<typename T>
class LinkedList {
    using Size = std::size_t;
    using Type = T;
    using Bool = bool;
private:
    struct ListNode {
        T data;
        ListNode<Type> *next;
    };

protected:
    Size m_size;
    ListNode<Type> *m_root;
    ListNode<Type> *m_last;

    ListNode<Type> *m_last_list_node;
    Size m_last_index_size;
    Bool is_

};
