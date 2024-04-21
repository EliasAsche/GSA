#include "MaxHeap.h"
using namespace std;

double Node::calcAvg() {
    if (!this->transactionAmounts.empty()) {
        double sum = 0.0;
        for (double amount : transactionAmounts) {
            sum += amount
        }
        avgAmount = sum / this->transactionAmounts.size();
    } else {
        this->avgAmount = 0.0;
    }
    return avgAmount;
}

void MaxHeap::heapifyDown(int index) {
    int largest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < this->transactionHeap.size() && this->transactionHeap[left]->calcAvg() > this->transactionHeap[largest]->calcAvg()) {
        largest = left;
    }
    if (right < this->transactionHeap.size() && this->transactionHeap[right]->calcAvg() > this->transactionHeap[largest]->calcAvg()) {
        largest = right;
    }

    if (largest != index) {
        swap(this->transactionHeap[index], this->transactionHeap[largest]);
        heapifyDown(largest);
    }
}