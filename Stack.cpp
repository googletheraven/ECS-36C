#ifndef STACK_CPP
#define STACK_CPP

#include "Stack.hpp"

template <typename T>
Stack<T>::Stack() : _llist() {}

template <typename T>
Stack<T>::Stack(const std::vector<T> &items) : _llist(items) {}

template <typename T>
size_t Stack<T>::size() const
{
    return _llist.size();
}

template <typename T>
std::optional<T> Stack<T>::top() const
{
    if (_llist.head() == nullptr)
    {
        return std::nullopt;
    }
    LinkedListNode<T> *node = _llist.head();
    while (node->next() != nullptr)
    {
        node = node->next();
    }
    return node->value;
}

template <typename T>
void Stack<T>::push(T value)
{
    _llist.append(value);
}
/*
template <typename T>
std::optional<T> Stack<T>::pop()
{
    
    if (_llist.head() == nullptr)
    {
        return std::nullopt;
    }
    LinkedListNode<T> *node = _llist.head();
    LinkedListNode<T> *prev = nullptr;

    //_llist.removeHead();
    
    while (node->next() != nullptr)
    {
        prev = node;
        node = node->next();
    }
    std::optional<T> value = node->value;
    if (prev != nullptr)
    {
        
        prev->next() = nullptr;

        //node = nullptr;
    }
    else
    {
        //_llist.removeHead();
       _llist.removeHead();
    }
    //std::optional<T> value = node->value;
    delete node;
    
    return value; 
}*/




template <typename T>
std::optional<T> Stack<T>::pop()
{
    if (_llist.head() == nullptr)
    {
        return std::nullopt; // Stack is empty
    }
    
    LinkedListNode<T> *node = _llist.head();
    LinkedListNode<T> *prev = nullptr;
/*  
    if (_llist.size() == 1) // Only one element
    {
        std::optional<T> value = _llist.head()->value;
        _llist.removeHead(); // Remove the head
        return value;
    }

    LinkedListNode<T> *node = _llist.head();
    LinkedListNode<T> *prev = nullptr;
*/

    // Traverse to the last node
    while (node->next() != nullptr)
    {
        prev = node;
        node = node->next();
    }

    std::optional<T> value = node->value;
  /*  _llist.remove(node) // Update the tail to point to the second-to-last node
    delete node; // Free memory
    */

    

    // Remove the last node from the linked list using its value
    if (prev != nullptr) // More than one node
    {
        // Use the value of the node to remove it
        if (!_llist.remove(value.value())) // Check if removal was successful
        {
            // Handle the case where removal failed (should not happen in a well-formed stack)
            // You might want to log an error or throw an exception
        }
    }
    else // Only one node in the stack
    {
        // Remove the head, which is the only node
        if (!_llist.remove(value.value())) // Check if removal was successful
        {
            // Handle the case where removal failed
        }
    }

    return value; // Return the value of the popped node

}



#endif