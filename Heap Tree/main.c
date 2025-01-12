#include <iostream>
#include <vector>

class MaxHeap {
private:
    std::vector<int> heap;

    int getParent(int i) {
        return (i - 1) / 2;
    }

    int getLeftChild(int i) {
        return 2 * i + 1;
    }

    int getRightChild(int i) {
        return 2 * i + 2;
    }

    void heapifyUp(int i) {
        while (i > 0 && heap[getParent(i)] < heap[i]) {
            int temp = heap[i];
            heap[i] = heap[getParent(i)];
            heap[getParent(i)] = temp;
            i = getParent(i);
        }
    }

    void heapifyDown(int i) {
        int largest = i;
        int left = getLeftChild(i);
        int right = getRightChild(i);

        if (left < (int)heap.size() && heap[left] > heap[largest]) {
            largest = left;
        }

        if (right < (int)heap.size() && heap[right] > heap[largest]) {
            largest = right;
        }

        if (largest != i) {
            int temp = heap[i];
            heap[i] = heap[largest];
            heap[largest] = temp;
            heapifyDown(largest);
        }
    }

public:
    void insert(int value) {
        heap.push_back(value);
        heapifyUp(heap.size() - 1);
    }

    void removeMax() {
        if (heap.empty()) {
            std::cout << "Heap is empty\n";
            return;
        }

        heap[0] = heap[heap.size() - 1];
        heap.pop_back();

        if (!heap.empty()) {
            heapifyDown(0);
        }
    }

    int getMax() {
        if (heap.empty()) {
            std::cout << "Heap is empty\n";
            return -1;
        }
        return heap[0];
    }

    void display() {
        if (heap.empty()) {
            std::cout << "Heap is empty\n";
            return;
        }
        
        std::cout << "Heap contents: ";
        for (size_t i = 0; i < heap.size(); i++) {
            std::cout << heap[i] << " ";
        }
        std::cout << "\n";
    }
};

int main() {
    MaxHeap heap;
    int choice = 0;
    int value;

    do {
        std::cout << "\n1. Insert\n";
        std::cout << "2. Remove max\n";
        std::cout << "3. Get max\n";
        std::cout << "4. Display\n";
        std::cout << "5. Exit\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Enter value: ";
                std::cin >> value;
                heap.insert(value);
                break;
            case 2:
                heap.removeMax();
                break;
            case 3:
                value = heap.getMax();
                if (value != -1) {
                    std::cout << "Maximum value: " << value << "\n";
                }
                break;
            case 4:
                heap.display();
                break;
            case 5:
                std::cout << "Exiting...\n";
                break;
            default:
                std::cout << "Invalid choice\n";
        }
    } while (choice != 5);

    return 0;
}