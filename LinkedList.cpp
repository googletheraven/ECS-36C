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
LinkedList<T>::LinkedList(const std::vector<T> &items) : _size(0), _head(nullptr), _tail(nullptr)
{
    for (const T &item : items)
    {
        append(item);
    }
}

template <typename T>
size_t LinkedList<T>::size() const
{
    return _size;
}

template <typename T>
LinkedListNode<T> *LinkedList<T>::head() const
{
    return _head;
}

template <typename T>
LinkedListNode<T> *LinkedList<T>::tail() const
{
    return _tail;
}

template <typename T>
LinkedListNode<T> *LinkedList<T>::find(T value) const
{
    LinkedListNode<T> *current = _head;
    while (current != nullptr)
    {
        if (current->value == value)
        {
            return current;
        }
        current = current->next();
    }
    return nullptr;
}

template <typename T>
LinkedListNode<T> *LinkedList<T>::prepend(T value)
{
    LinkedListNode<T> *newNode = new LinkedListNode<T>(value);
    if (_head == nullptr)
    {
        _head = newNode;
        _tail = newNode;
    }
    else
    {
        newNode->_next = _head;
        _head = newNode;
    }
    _size++;
    return newNode;
}

template <typename T>
LinkedListNode<T> *LinkedList<T>::append(T value)
{
    LinkedListNode<T> *newNode = new LinkedListNode<T>(value);
    if (_head == nullptr)
    {
        _head = newNode;
        _tail = newNode;
    }
    else
    {
        _tail->_next = newNode;
        _tail = newNode;
    }
    _size++;
    return newNode;
}

template <typename T>
LinkedListNode<T> *LinkedList<T>::insertAfter(LinkedListNode<T> *node, T value)
{
    if (node == nullptr)
    {
        return prepend(value);
    }
    LinkedListNode<T> *newNode = new LinkedListNode<T>(value);
    newNode->_next = node->_next;
    node->_next = newNode;
    if (node == _tail)
    {
        _tail = newNode;
    }
    _size++;
    return newNode;
}

template <typename T>
std::optional<T> LinkedList<T>::removeHead()
{
    if (_head == nullptr)
    {
        return std::nullopt;
    }
    T value = _head->value;
    LinkedListNode<T> *oldHead = _head;
    _head = _head->_next;
    if (_head == nullptr)
    {
        _tail = nullptr;
    }
    delete oldHead;
    _size--;
    return value;
}


template <typename T>
bool LinkedList<T>::remove(T value)
{
    LinkedListNode<T> *current = _head;
    LinkedListNode<T> *previous = nullptr;
    while (current != nullptr)
    {
        if (current->value == value)
        {
            if (previous == nullptr)
            {
                return removeHead().has_value();
            }
            else
            {
                previous->_next = current->_next;
                if (current == _tail)
                {
                    _tail = previous;
                }
                delete current;
                _size--;
                return true;
            }
        }
        previous = current;
        current = current->_next;
    }
    return false;
}




template <typename T>
void LinkedList<T>::clear()
{
    while (_head != nullptr)
    {
        LinkedListNode<T> *oldHead = _head;
        _head = _head->_next;
        delete oldHead;
    }
    _tail = nullptr;
    _size = 0;
}

template <typename T>
LinkedList<T>::~LinkedList()
{
    clear();
}
#endif
