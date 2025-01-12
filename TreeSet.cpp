
#include "TreeSet.hpp"
#include <algorithm>

// Constructor
template <typename T>
TreeSet<T>::TreeSet() : _root(nullptr), _size(0), _comparator([](T a, T b) { return (a < b) ? -1 : (a > b) ? 1 : 0; }) {}

template <typename T>
TreeSet<T>::TreeSet(const std::vector<T> &items) : TreeSet() {
    for (const auto &item : items) {
        add(item);
    }
}

template <typename T>
TreeSet<T>::TreeSet(std::function<int(T, T)> comparator) : _root(nullptr), _size(0), _comparator(comparator) {}

template <typename T>
TreeSet<T>::TreeSet(const std::vector<T> &items, std::function<int(T, T)> comparator) : TreeSet(comparator) {
    for (const auto &item : items) {
        add(item);
    }
}

// Returns the number of elements in the tree
template <typename T>
size_t TreeSet<T>::size() const {
    return _size;
}

// Adds a value to the set
template <typename T>
void TreeSet<T>::add(T value) {
    BinaryTreeNode<T> *z = new BinaryTreeNode<T>(value);
    //auto newNode = new BinaryTreeNode<T>(value);

    // If the tree is empty, set the root to the new node
    if (!_root) {
        _root = z;
        _size++;
        return;
    }

    BinaryTreeNode<T> *y = nullptr;
    BinaryTreeNode<T> *x = _root;
//finding the correct position for the new value
    while (x) {
        y = x;
        int cmp = _comparator(value, x->value);
        if (cmp==0) {
            //key already exists, update the value
            x->value = value;
            delete z;
            return;
        }
        else if (cmp < 0) {
            x = x->_left;
        } else {
            x = x->_right;
        }
    }

  
    //z->_parent = y;  //Set parent
    if (!y) {
        _root = z; // Tree was empty
    } else if (_comparator(value, y->value) < 0) {
        y->_left = z;
    } else {
        y->_right = z;
    }

    _size++;
    fix_violation(z); //Red-Black tree balancing placeholder
}

// Check if an element is in the set
template <typename T>
bool TreeSet<T>::contains(T value) const {
    BinaryTreeNode<T> *x = _root;
    while (x) {
        int cmp = _comparator(value, x->value);
        if (cmp == 0) {
            return true;  //found
        } else if (cmp < 0) {
            x = x->_left;
        } else {
            x = x->_right;
        }
    }
    return false;  //not found
}

// Check if the set is empty
template <typename T>
bool TreeSet<T>::is_empty() const {
    return _size == 0;
}

// Search for the smallest value in the set
template <typename T>
std::optional<T> TreeSet<T>::min() const {
    if (!_root) return std::nullopt;
    BinaryTreeNode<T> *current = _root;
    while (current->_left) {
        current = current->_left;
    }
    return current->value;
}

// Search for the largest value in the set
template <typename T>
std::optional<T> TreeSet<T>::max() const {
    if (!_root) return std::nullopt;
    BinaryTreeNode<T> *current = _root;
    while (current->_right) {
        current = current->_right;
    }
    return current->value;
}

// Traverse the set in order and return the values as a vector
template <typename T>
std::vector<T> TreeSet<T>::to_vector() const {
    std::vector<T> result;
    std::function<void(BinaryTreeNode<T> *)> in_order = [&](BinaryTreeNode<T>* node) {
        if (node) {
            in_order(node->_left);
            result.push_back(node->value);
            in_order(node->_right);
        }
    };
    in_order(_root);
    return result;
}

// Finds a value and returns it
template <typename T>
std::optional<T> TreeSet<T>::get(T value) const {
    BinaryTreeNode<T> *x = _root;
    while (x) {
        int cmp = _comparator(value, x->value);
        if (cmp == 0) {
            return x->value;
        } else if (cmp < 0) {
            x = x->_left;
        } else {
            x = x->_right;
        }
    }
    return std::nullopt;
}

// Set union
template <typename T>
TreeSet<T> TreeSet<T>::operator+(const TreeSet &other) {
   // TreeSet<T> result(*this);
   TreeSet<T> result(_comparator);  //create a new TreeSet with the same comparator
    //for (const T &item : other.to_vector()) {

// add all elements from the set
    for (const auto &value : to_vector()) {
        result.add(value);
    }

    // Add all elements from the other set and COMMENT THIS
    for (const auto &value : other.to_vector()) {
        result.add(value);
    }

    return result;
}

// In-place set union
template <typename T>
TreeSet<T>& TreeSet<T>::operator+=(const TreeSet &other) {
    for (const T &item : other.to_vector()) {
        add(item);
    }
}

// Set intersection
template <typename T>
TreeSet<T> TreeSet<T>::operator&(const TreeSet &other) {
    TreeSet<T> result;
    for (const T &item : to_vector()) {
        if (other.contains(item)) {
            result.add(item);
        }
    }
    return result;
}

// Set equal
template <typename T>
bool TreeSet<T>::operator==(const TreeSet &other) const {
    if (_size != other._size) return false;
    return to_vector() == other.to_vector();
}

// Set not equal
template <typename T>
bool TreeSet<T>::operator!=(const TreeSet &other) const {
    return !(*this == other);
}

// Clear the set
template <typename T>
void TreeSet<T>::clear() {
    // Implement a clear function to delete all nodes
    std::function<void(BinaryTreeNode<T>*)> clear_helper = [&](BinaryTreeNode<T>* node) {
        if (node != nullptr) {
            clear_helper(node->_left);
            clear_helper(node->_right);
            delete node;
        }
    };
    clear_helper(_root);
    _root = nullptr;
    _size = 0;
}

// Destructor
template <typename T>
TreeSet<T>::~TreeSet() {
    clear();
}

// Rotate left
template <typename T>
void TreeSet<T>::rotate_left(BinaryTreeNode<T> *x) {
    BinaryTreeNode<T> *y = x->_right;
    x->_right = y->_left;
    if (y->_left != nullptr) {
        y->_left->_parent = x;
    }
    y->_parent = x->_parent;
    if (x->_parent == nullptr) {
        _root = y;
    } else if (x == x->_parent->_left) {
        x->_parent->_left = y;
    } else {
        x->_parent->_right = y;
    }
    y->_left = x;
    x->_parent = y;
}

// Rotate right
template <typename T>
void TreeSet<T>::rotate_right(BinaryTreeNode<T> *y) {
    BinaryTreeNode<T> *x = y->_left;
    y->_left = x->_right;
    if (x->_right != nullptr) {
        x->_right->_parent = y;
    }
    x->_parent = y->_parent;
    if (y->_parent == nullptr) {
        _root = x;
    } else if (y == y->_parent->_left) {
        y->_parent->_left = x;
    } else {
        y->_parent->_right = x;
    }
    x->_right = y;
    y->_parent = x;
}

// Fix violation of Red-Black Tree properties
template <typename T>
void TreeSet<T>::fix_violation(BinaryTreeNode<T> *z) {
    // Implementation of the violation fixing logic
    while (z->_parent && z->_parent->_color == Red) {
        BinaryTreeNode<T> *y = (z->_parent == z->_parent->_parent->_left) ? z->_parent->_parent->_right : z->_parent->_parent->_left;

        if (y && y->_color == Red) {
            z->_parent->_color = Black;
            y->_color = Black;
            z->_parent->_parent->_color = Red;
            z = z->_parent->_parent;
        } else {
            if (z == z->_parent->_right) {
                z = z->_parent;
                rotate_left(z);
            }
            z->_parent->_color = Black;
            z->_parent->_parent->_color = Red;
            rotate_right(z->_parent->_parent);
        }
    }
    _root->_color = Black;
}

