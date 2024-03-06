#ifndef __HEAP__HPP
#define __HEAP_HPP

#include <iostream>
#include <vector>


template <class T>
class Heap {
    std::vector<T> heap;

    int right(int ind) {
        return (2 * ind) + 2;
    }

    int left(int ind) {
        return (2 * ind) + 1;
    }


    int parent(int ind) {
        return (ind - 1) / 2;//Прочетено е от записки по ДАА на доц. М. Марков
    }

    int minChild(int ind) {
        if (size() <= left(ind)) {
            return -1;
        }
        else  if (size() <= right(ind)) {
            return left(ind);
        }
        else if (heap[left(ind)] < heap[right(ind)]) {
            return left(ind);
        }
        else {
            return right(ind);
        }
    }

    void siftUp(int start) {
        for (int i = start; i > 0 && heap[i] < heap[parent(i)]; i = parent(i)) {
            std::swap(heap[i], heap[parent(i)]);
        }
    }

    void siftDown(int start) {
        for (int i = minChild(start); i != -1 && heap[i] < heap[parent(i)]; i = minChild(i)) {
            std::swap(heap[i], heap[parent(i)]);
        }
    }

public:
    T top() const {
        return heap[0];
    }

    int size() {
        return heap.size();
    }

    bool empty() {
        return heap.size() == 0;
    }

    void push(T newElement) {
        heap.push_back(newElement);
        siftUp(size() - 1);
    }

    void print() {
        for (int i = 0; i < heap.size(); ++i) {
            std::cout << heap[i] << " ";
        }
        std::cout << std::endl;
    }

    void pop() {
        std::swap(heap[0], heap[size() - 1]);
        heap.pop_back();
        siftDown(0);
    }

};

#endif
