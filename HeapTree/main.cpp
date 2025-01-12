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

    bool isEmpty() {
        return heap.empty();
    }
};

int main() {
    MaxHeap heap;
    int choice;
    int value;

    while (true) {
        std::cout << "\nMax Heap Operations:\n";
        std::cout << "1. Insert\n";
        std::cout << "2. Remove max\n";
        std::cout << "3. Get max\n";
        std::cout << "4. Display\n";
        std::cout << "5. Exit\n";
        std::cout << "Enter choice: ";
        
        if (!(std::cin >> choice)) {
            std::cout << "Invalid input. Exiting...\n";
            break;
        }

        if (choice == 5) {
            std::cout << "Exiting program...\n";
            break;
        }

        switch (choice) {
            case 1:
                std::cout << "Enter value to insert: ";
                if (std::cin >> value) {
                    heap.insert(value);
                    std::cout << "Inserted " << value << "\n";
                } else {
                    std::cout << "Invalid input\n";
                }
                break;
            case 2:
                heap.removeMax();
                std::cout << "Removed maximum element\n";
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
            default:
                std::cout << "Invalid choice\n";
        }
    }

    return 0;
}