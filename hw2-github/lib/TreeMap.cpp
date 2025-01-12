

#ifndef TREE_MAP_CPP
#define TREE_MAP_CPP


#include "TreeMap.hpp"
#include "TreeSet.cpp"


// Constructor
template <typename TKey, typename TValue>
TreeMap<TKey, TValue>::TreeMap() 
    : _tree([] (const std::pair<TKey, TValue>& a, const std::pair<TKey, TValue>& b) 
    {
        if (a.first < b.first) return -1;
        if (a.first > b.first) return 1;
        return 0;
        }) {}

// Constructor - initial items
template <typename TKey, typename TValue>
TreeMap<TKey, TValue>::TreeMap(const std::vector<std::pair<TKey, TValue>>& items) 
    : TreeMap() {
    for (const auto& item : items) {
        insert(item.first, item.second);
    }
}

// returns map elements
template <typename TKey, typename TValue>
size_t TreeMap<TKey, TValue>::size() const {
    return _tree.size();
}

// Insert a key-value pair into the map
template <typename TKey, typename TValue>
void TreeMap<TKey, TValue>::insert(TKey key, TValue value) {
    //_tree.add(std::make_pair(key, value));
    std::pair<TKey, TValue> new_pair = std::make_pair(key, value);
    auto existing = _tree.get(new_pair);
    if (existing) {
       // _tree.remove(new_pair);
    }
      _tree.add(new_pair);
    
    
}

// Get key value
template <typename TKey, typename TValue>
std::optional<TValue> TreeMap<TKey, TValue>::get(TKey key) const {

    //std::pair<TKey, TValue> searchPair = {key, TValue()};  //search pair creation
    auto result = _tree.get(std::make_pair(key, TValue{}));
    //searchPair);  //using get() from TreeSet
    return result ? std::optional<TValue>(result->second) : std::nullopt;
}

// Check if a key is in the map
template <typename TKey, typename TValue>
bool TreeMap<TKey, TValue>::contains(TKey key) const {
    return _tree.contains(std::make_pair(key, TValue{})); // Use a dummy value for checking
}

// Traverse the map in order and return the key-value pairs as a vector
template <typename TKey, typename TValue>
std::vector<std::pair<TKey, TValue>> TreeMap<TKey, TValue>::to_vector() const {
    //std::vector<std::pair<TKey, TValue>> result;
    //for (const auto &item : _tree.to_vector()) {
      //  result.push_back(item);
    //}
    return _tree.to_vector();
}

// Check if the map is empty
template <typename TKey, typename TValue>
bool TreeMap<TKey, TValue>::is_empty() const {
    return _tree.is_empty();
}

// Clear the map
template <typename TKey, typename TValue>
void TreeMap<TKey, TValue>::clear() {
    _tree.clear();
}

// Destructor
template <typename TKey, typename TValue>
TreeMap<TKey, TValue>::~TreeMap() = default;
#endif
