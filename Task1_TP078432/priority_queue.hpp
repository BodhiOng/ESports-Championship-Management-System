#ifndef PRIORITY_QUEUE_HPP
#define PRIORITY_QUEUE_HPP
//handles ranking based priority
#include "player.hpp"

class PriorityQueue {
private:
    Player heap[100];
    int size;

    void heapifyUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (heap[index].ranking > heap[parent].ranking) {
                swap(heap[index], heap[parent]);
                index = parent;
            } else {
                break;
            }
        }
    }

    void heapifyDown(int index) {
        int left, right, largest;
        while (true) {
            left = 2 * index + 1;
            right = 2 * index + 2;
            largest = index;

            if (left < size && heap[left].ranking > heap[largest].ranking)
                largest = left;
            if (right < size && heap[right].ranking > heap[largest].ranking)
                largest = right;

            if (largest != index) {
                swap(heap[index], heap[largest]);
                index = largest;
            } else {
                break;
            }
        }
    }

public:
    PriorityQueue() {
        size = 0;
    }

    void insert(Player p) {
        heap[size] = p;
        heapifyUp(size);
        size++;
    }

    Player extractMax() {
        Player top = heap[0];
        heap[0] = heap[size - 1];
        size--;
        heapifyDown(0);
        return top;
    }

    bool isEmpty() {
        return size == 0;
    }

    int getSize() {
        return size;
    }
};

#endif
