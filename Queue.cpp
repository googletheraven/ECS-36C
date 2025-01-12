#ifndef QUEUE_CPP
#define QUEUE_CPP

#include "Queue.hpp"

template <typename T>
Queue<T>::Queue(LinkedList<T> &&llist) : _llist(std::move(llist)) {}

template <typename T>
Queue<T>::Queue() : Queue(LinkedList<T>()) {}

template <typename T>
Queue<T>::Queue(const std::vector<T> &items) : _llist(items) {}

// TODO: Implement all other methods defined in Queue.hpp here

template <typename T>
size_t Queue<T>::size() const
{
    return _llist.size();
}

template <typename T>
void Queue<T>::enqueue(T value)
{
    _llist.append(value);
}

template <typename T>
std::optional<T> Queue<T>::dequeue()
{
    if (_llist.head() == nullptr)
    {
        return std::nullopt;
    }
    LinkedListNode<T> *node = _llist.head();
    std::optional<T> value = node->value;
    _llist.removeHead();
    //delete node;
    return value;
}
/*
template <typename T>
std::optional<T> Queue<T>::dequeue()
{
    if (_llist.head() == nullptr)
    {
        return std::nullopt;
    }
    // LinkedListNode<T> *node = _llist.head();
    // std::optional<T> value = node->value;
    // int *head = _llist.head();
    //*head = node->next(); // Update the head of the linked list, call the next function
    _llist.remove(_llist.head(_llist.size() - 1)); // Remove from the front of the queue (end of LinkedList)
    // delete node;
    // return value;
}*/

#endif
// For test cases, just call functioins (add and deque) usinng the functionns you coded and objects presented
