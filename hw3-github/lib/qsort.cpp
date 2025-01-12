#ifndef QSORT_CPP
#define QSORT_CPP

#include "qsort.hpp"
#include <cstdlib>  // For std::rand()

template <typename RandomAccessIter, typename Comparator>
void quick_sort(RandomAccessIter first, RandomAccessIter last, Comparator comparator)
{
    // Calculate the size of the range
    auto size = std::distance(first, last);
    
    // Base case: if the range is empty or has one element, it is already sorted.
    if (size <= 1) {
        return;
    }

    // Randomly select a pivot (only if we have elements to sort)
    auto random_index = size > 0 ? std::rand() % size : 0;
    std::iter_swap(first, first + random_index);

    auto pivot = *first;
    RandomAccessIter low = first + 1;
    RandomAccessIter high = last - 1;

    // Partition the range
    while (true) {
        // Move low pointer right while elements are less than pivot
        while (low <= high && comparator(*low, pivot)) {
            ++low;
        }
        // Move high pointer left while elements are greater than pivot
        while (low <= high && !comparator(*high, pivot)) {
            --high;
        }
        // If pointers crossed, we're done partitioning
        if (low > high) {
            break;
        }
        // Swap elements and continue
        std::iter_swap(low, high);
        ++low;
        --high;
    }

    // Place pivot in its final position
    std::iter_swap(first, high);

    // Recursively sort subarrays
    quick_sort(first, high, comparator);
    quick_sort(high + 1, last, comparator);
}

#endif  // QSORT_CPP