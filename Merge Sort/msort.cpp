#include <iostream>
#include <vector>

template <typename T>
void merge(std::vector<T>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    std::vector<T> L(n1);
    std::vector<T> R(n2);
    
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];
        
    int i = 0, j = 0, k = left;
    
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

template <typename T>
void mergeSort(std::vector<T>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

void runTestCase(const std::vector<int>& input, const std::string& testName) {
    std::vector<int> arr = input;
    
    std::cout << "\nTest Case: " << testName << std::endl;
    std::cout << "Original array: ";
    for (size_t i = 0; i < arr.size(); i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
    
    mergeSort(arr, 0, arr.size() - 1);
    
    std::cout << "Sorted array:   ";
    for (size_t i = 0; i < arr.size(); i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

int main() {
    // Original test case
    std::vector<int> test1;
    test1.push_back(12);
    test1.push_back(11);
    test1.push_back(13);
    test1.push_back(5);
    test1.push_back(6);
    test1.push_back(7);
    runTestCase(test1, "Original");

    // Test case with negative numbers
    std::vector<int> test2;
    test2.push_back(-5);
    test2.push_back(10);
    test2.push_back(-3);
    test2.push_back(8);
    test2.push_back(-9);
    test2.push_back(3);
    runTestCase(test2, "Negative Numbers");

    // Test case with duplicates
    std::vector<int> test3;
    test3.push_back(4);
    test3.push_back(2);
    test3.push_back(4);
    test3.push_back(1);
    test3.push_back(2);
    test3.push_back(4);
    runTestCase(test3, "Duplicates");

    // Test case with already sorted array
    std::vector<int> test4;
    test4.push_back(1);
    test4.push_back(2);
    test4.push_back(3);
    test4.push_back(4);
    test4.push_back(5);
    runTestCase(test4, "Already Sorted");

    // Test case with reverse sorted array
    std::vector<int> test5;
    test5.push_back(9);
    test5.push_back(8);
    test5.push_back(7);
    test5.push_back(6);
    test5.push_back(5);
    runTestCase(test5, "Reverse Sorted");

    // Test case with large numbers
    std::vector<int> test6;
    test6.push_back(1000);
    test6.push_back(1);
    test6.push_back(10000);
    test6.push_back(100);
    test6.push_back(100000);
    runTestCase(test6, "Large Numbers");

    return 0;
}