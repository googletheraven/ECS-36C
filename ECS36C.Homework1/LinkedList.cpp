#ifndef LINKED_LIST_CPP
#define LINKED_LIST_CPP

#include "LinkedList.hpp"

template <typename T>
LinkedList<T>::LinkedList() : _size(0), _head(nullptr), _tail(nullptr) {}

template <typename T>
LinkedList<T>::LinkedList(LinkedList<T> &&other) : _size(other._size),
                                                   _head(other._head),
                                                   _tail(other._tail)
{
    other._size = 0;
    other._head = nullptr;
    other._tail = nullptr;
}

template <typename T>
void LinkedList<T>::addFront(T value) {
    Node* newNode = new Node(value);
    newNode->next = head;
    head = newNode;
    size++;
}

#include "LinkedList.hpp"

template <typename T>
LinkedList<T>::LinkedList() : _size(0), _head(nullptr), _tail(nullptr) {}

template <typename T>
LinkedList<T>::LinkedList(LinkedList<T> &&other) : _size(other._size),
                                                   _head(other._head),
                                                   _tail(other._tail) {
    other._size = 0;
    other._head = nullptr;
    other._tail = nullptr;
}

template <typename T>
LinkedList<T>::LinkedList(const std::vector<T> &items) : _size(0), _head(nullptr), _tail(nullptr) {
    for (const auto &item : items) {
        append(item);
    }
}

template <typename T>
size_t LinkedList<T>::size() const {
    return _size;
}

template <typename T>
LinkedListNode<T> *LinkedList<T>::head() const {
    return _head;
}

template <typename T>
LinkedListNode<T> *LinkedList<T>::tail() const {
    return _tail;
}

template <typename T>
LinkedListNode<T> *LinkedList<T>::find(T value) const {
    LinkedListNode<T> *temp = _head;
    while (temp != nullptr) {
        if (temp->value == value) {
            return temp;
        }
        temp = temp->next();
    }
    return nullptr;
}

template <typename T>
LinkedListNode<T> *LinkedList<T>::prepend(T value) {
    LinkedListNode<T> *node = new LinkedListNode<T>(value, _head);
    _head = node;
    if (_tail == nullptr) {
        _tail = node; // If the list was empty, set tail to the new node
    }
    _size++;
    return node;
}

template <typename T>
LinkedListNode<T> *LinkedList<T>::append(T value) {
    LinkedListNode<T> *node = new LinkedListNode<T>(value);
    if (_head == nullptr) {
        _head = node; // If the list is empty, set head to the new node
        _tail = node; // Set tail to the new node
    } else {
        _tail->_next = node; // Link the current tail to the new node
        _tail = node; // Update tail to the new node
    }
    _size++;
    return node;
}

template <typename T>
LinkedListNode<T> *LinkedList<T>::insertAfter(LinkedListNode<T> *node, T value) {
    if (node == nullptr) {
        return prepend(value); // If node is nullptr, prepend
    }
    LinkedListNode<T> *newNode = new LinkedListNode<T>(value, node->next());
    node->_next = newNode; // Link the current node to the new node
    if (newNode->next() == nullptr) {
        _tail = newNode; // Update tail if new node is now the last node
    }
    _size++;
    return newNode;
}

template <typename T>
std::optional<T> LinkedList<T>::removeHead() {
    if (_head == nullptr) {
        return std::nullopt; // List is empty
    }
    T value = _head->value;
    LinkedListNode<T> *temp = _head;
    _head = _head->next(); // Move head to the next node
    if (_head == nullptr) {
        _tail = nullptr; // If the list is now empty, set tail to nullptr
    }
    delete temp; // Free the old head
    _size--;
}
// TODO: Implement all other methods defined in LinkedList.hpp here

#endif