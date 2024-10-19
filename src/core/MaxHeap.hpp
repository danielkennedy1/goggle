#include "ArrayList.h"
#include <cmath>

template <typename T>
struct HeapNode {
    T value;
    int priority;
    HeapNode(T value, int priority) : value(value), priority(priority) {};
};

template <typename T>
class MaxHeap {
public:
    MaxHeap() { array = new ArrayList<HeapNode<T>*>(); }

    // TODO: There's a faster way to do it by shifting the replaced value down
    // instead of this percolation
    void insert(T newValue, int priority) {
        array->append(new HeapNode<T>(newValue, priority));
        int childIndex = array->length - 1;
        int parentIndex = (childIndex - 1) / 2;

        while (childIndex > 0 && array->get(parentIndex)->priority < array->get(childIndex)->priority) {
            swap(parentIndex, childIndex);
            childIndex = parentIndex;
            parentIndex = (childIndex - 1) / 2;
        }
    }

    ArrayList<HeapNode<T>*>* array;

    void swap(int indexA, int indexB) {
        HeapNode<T>* t = array->get(indexA);
        array->get(indexA) = array->get(indexB);
        array->get(indexB) = t;
    }

    void printArray() {
        for (int i = 0; i < array->length; i++) {
            std::cout << i << ", ";
        }
        std::cout << std::endl;

        for (int i = 0; i < array->length; i++) {
            std::cout << array->get(i)->priority << ", ";
        }
        std::cout << std::endl;
    }

    T max() {
        T result = array->get(0)->value;

        if (array->length == 1) {
            array->remove(0);
            return result;
        }

        swap(0, array->length - 1);
        array->remove(array->length - 1);

        heapify(0);

        return result;
    }

    // Helper function to maintain the heap property
    void heapify(int index) {
        int min = index;
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;

        if (leftChild < array->length && array->get(leftChild)->priority > array->get(min)->priority) {
            min = leftChild;
        }

        if (rightChild < array->length && array->get(rightChild)->priority > array->get(min)->priority) {
            min = rightChild;
        }

        if (min != index) {
            swap(index, min);
            heapify(min);
        }
    }
};
