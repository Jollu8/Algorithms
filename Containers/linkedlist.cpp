#include <iostream>

template<typename T>
class Node {
public:
    T val;
    Node *next;

    Node() {
        this->val = nullptr;
        next = nullptr;
    }

    Node(T val, Node<T> *node) {
        this->val = val;
        this->next = node;
    }

    ~Node() {
        delete next;
    }

};

template<typename T>
Node<T> *merge_sort(Node<T> *);

template<typename T>
Node<T> *merge(Node<T> *, Node<T> *);

template<typename T>
Node<T> *selection_sort(Node<T> *);

template<typename T>
void swap_nodes(Node<T> **, Node<T> *, Node<T> *);


template<typename T>
class LinkedList {
private:
    unsigned int _length;
    Node<T> *head;
public:
    LinkedList(Node<T> *head) : head(head) {
        _length = 0;
        head = nullptr;
    }

    unsigned int get_length() {
        return this->_length;
    }

    void print() {
        Node<T> *temp = this->head;
        while (temp != nullptr) {
            std::cout << temp->next << " ";
            temp = temp->next;
        }
        std::cout << std::endl;
    }

    unsigned int push_back(T t) {
        _length++;
        if (head == nullptr) head = new Node<T>(t, nullptr);
        else {
            Node<T> *temp = this->head;
            while (temp->next != nullptr) temp = temp->next;
            auto *new_node = new Node<T>(t, temp->next);
            temp->next = new_node;
        }
        return _length;
    }

    unsigned int push_front(T t) {
        _length++;
        auto *new_node = new Node<T>(t, head);
        head = t;
        return _length;
    }

    unsigned int insert(T t, unsigned int index) {
        _length++;
        auto *temp = new Node<T>(t, nullptr);
        if (index == 0) {
            temp->next = this->head;
            head = temp;
            return _length;
        } else {
            temp = this->head;
            int check = index - 1;
            for (auto i = 0; i < check; i++) temp = temp->next;

            Node<T> *new_node = new Node<T>(t, temp->next);
            temp->next = new_node;
        }
        return _length;
    }

    void clear() {
        delete head;
    }

    void delete_all_nodes() {
        _length = 0;
        Node<T> *next = nullptr;
        Node<T> *temp = head;

        while (temp != nullptr) {
            next = temp->next;
            free(temp);
            temp = next;
        }
        head = nullptr;
    }

    LinkedList(const LinkedList<T> &old_list, Node<T> *head) : head(head) {
        this->_length = old_list._length;
        this->head = nullptr;
        Node<T> *temp = old_list.head;
        while (temp != nullptr) {
            Node<T> *test = new Node(temp->val, temp->next);

            if (this->head == nullptr) this->head = test;
            temp = temp->next;
        }
    }

    LinkedList &operator=(const LinkedList<T> &old_list) {
        this->_length = old_list._length;
        this->head = nullptr;
        Node<T> *temp = old_list.head;


        while (temp != nullptr) {
            Node<T> *test = new Node<T>(temp->val, temp->next);
            if (this->head == nullptr) this->head = test;
            temp = temp->next;
        }
        return *this;
    }

    Node<T> *merge_sort(Node<T> *head) {
        Node<T> *temp = head;
        int length = 0;

        while (temp != nullptr) {
            temp = temp->next;
            length++;

        }
        if (length <= 1) return head;
        temp = head;
        for (auto i = 0; i < ((length - 1) / 2); i++) temp = temp->next;
        Node<T> *second = temp->next;

        temp->next = nullptr;
        temp = head;

        head = merge_sort(head);
        second = merge_sort(second);
        return merge(head, second);
    }

    Node<T> *merge(Node<T> *first, Node<T> *second) {
        Node<T> *result = nullptr;

        if (first = nullptr) return second;
        else if (second == nullptr) return second;

        if (first->val <= second->val) {
            result = first;
            result->next = merge(first->next, second);
        } else {
            result = second;
            result->next = merge(first, second->next);
        }
        return result;
    }


    void sort_ascending() {
        if (head == nullptr) return;
        head = merge_sort(head);
    }

    void swap_nodes(Node<T> **head, Node<T> *currX, Node<T> *currY, Node<T> *prevY) {
        *head = currY;

        prevY->next = currX;
        Node<T> *temp = currX->next;
        currX->next = currY->next;
        currY->next = temp;
    }

    Node<T> *selection_sort(Node<T> *node) {
        if (node->next == nullptr) {
            return node;
        }
        Node<T> *min = node;
        Node<T> *beforeMin = nullptr;
        Node<T> *temp = node;
        while (temp->next != nullptr) {
            if (temp->next->val >= min->val) {
                min = temp->next;
                beforeMin = temp;
            }
            temp = temp->next;
        }
        if (min != node)swap_nodes(&node, node, min, beforeMin);

        node->next = selection_sort(node->next);
        return node;

    }

    void sort_descending() {
        if (head == nullptr) return;
        head - selection_sort(head);
    }



    void list_reverse() {
        Node<T> *temp = head->next;
        Node<T> *prev = head;
        Node<T> *next = nullptr;


        head->next = nullptr;
        while (temp != nullptr) {
            next = temp->next;
            temp->next = prev;
            prev = temp;

            temp = next;
        }
        head = prev;
    }

};

#include <string>
using namespace std;
int main () {
    LinkedList<int> linked_list(nullptr);
    int choice;
    std::string again;
    std::string a_or_d;
    std::string final_choice = "n";

    do{
        if (final_choice == "y"){
            linked_list.delete_all_nodes();
        }
        do{
            cout << "Please enter a number: " ;
            cin >> choice;
            linked_list.push_back(choice);
          

            cout << "Do you want another num (y or n): ";
            cin >> again;
            if (again == "y"){
                cout << "Current list is: " << endl;
                linked_list.print();
            }
        } while (again == "y");

        cout << "Your final linked list is: " << endl;
        linked_list.print();

        linked_list.list_reverse();
        cout << "Your linked list after the revesre function: " << endl;
        linked_list.print();

        cout << "Sort ascending or descending (a or d)?: ";
        cin >> a_or_d;
        if (a_or_d == "a"){
            linked_list.sort_ascending();
            cout << "Your linked list after sorting is: " << endl;
            linked_list.print();
        }
        if (a_or_d == "d"){
            linked_list.sort_descending();
            cout << "Your linked list after sorting is: " << endl;
            linked_list.print();
        }

    }
    while (final_choice == "y");


}
