#include <iostream>
#include <vector>
#include <iomanip>  // for std::setprecision

class HeapSort {
private:
    static void heapify(std::vector<double>& arr, int n, int i) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && arr[left] > arr[largest])
            largest = left;

        if (right < n && arr[right] > arr[largest])
            largest = right;

        if (largest != i) {
            std::swap(arr[i], arr[largest]);
            heapify(arr, n, largest);
        }
    }

public:
    static void sort(std::vector<double>& arr) {
        int n = arr.size();

        for (int i = n / 2 - 1; i >= 0; i--)
            heapify(arr, n, i);

        for (int i = n - 1; i > 0; i--) {
            std::swap(arr[0], arr[i]);
            heapify(arr, i, 0);
        }
    }

    static void printArray(const std::vector<double>& arr) {
        // Set precision to 3 decimal places
        std::cout << std::fixed << std::setprecision(3);
        for (int i = 0; i < arr.size(); i++) {
            std::cout << arr[i] << " ";
        }
        std::cout << std::endl;
    }
};

int main() {
    // Test with floating point numbers
    double arr1_data[] = {3.14, 1.414, 2.718, 0.577, 1.732, 2.236};
    std::vector<double> arr1(arr1_data, arr1_data + sizeof(arr1_data)/sizeof(arr1_data[0]));
    
    std::cout << "Original array: ";
    HeapSort::printArray(arr1);
    
    HeapSort::sort(arr1);
    
    std::cout << "Sorted array: ";
    HeapSort::printArray(arr1);

    // Test with negative and mixed floating point numbers
    double arr2_data[] = {-3.14, 2.5, -1.5, 0.0, 1.5, -2.5};
    std::vector<double> arr2(arr2_data, arr2_data + sizeof(arr2_data)/sizeof(arr2_data[0]));
    
    std::cout << "\nOriginal array: ";
    HeapSort::printArray(arr2);
    
    HeapSort::sort(arr2);
    
    std::cout << "Sorted array: ";
    HeapSort::printArray(arr2);

    return 0;
}

// Other implementation
#include <iostream>
#include <vector>

class HeapSort {
private:
    static void heapify(std::vector<int>& arr, int n, int i) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && arr[left] > arr[largest])
            largest = left;

        if (right < n && arr[right] > arr[largest])
            largest = right;

        if (largest != i) {
            std::swap(arr[i], arr[largest]);
            heapify(arr, n, largest);
        }
    }

public:
    static void sort(std::vector<int>& arr) {
        int n = arr.size();

        for (int i = n / 2 - 1; i >= 0; i--)
            heapify(arr, n, i);

        for (int i = n - 1; i > 0; i--) {
            std::swap(arr[0], arr[i]);
            heapify(arr, i, 0);
        }
    }

    static void printArray(const std::vector<int>& arr) {
        for (int i = 0; i < arr.size(); i++) {
            std::cout << arr[i] << " ";
        }
        std::cout << std::endl;
    }
};

int main() {
    // Initialize vectors the old way
    int arr1_data[] = {12, 11, 13, 5, 6, 7};
    std::vector<int> arr1(arr1_data, arr1_data + sizeof(arr1_data)/sizeof(arr1_data[0]));
    
    std::cout << "Original array: ";
    HeapSort::printArray(arr1);
    
    HeapSort::sort(arr1);
    
    std::cout << "Sorted array: ";
    HeapSort::printArray(arr1);

    int arr2_data[] = {4, 4, 2, 2, 3, 3, 1, 1};
    std::vector<int> arr2(arr2_data, arr2_data + sizeof(arr2_data)/sizeof(arr2_data[0]));
    
    std::cout << "\nOriginal array: ";
    HeapSort::printArray(arr2);
    
    HeapSort::sort(arr2);
    
    std::cout << "Sorted array: ";
    HeapSort::printArray(arr2);

    return 0;
}