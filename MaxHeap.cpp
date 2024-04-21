#include "MaxHeap.h"
using namespace std;

double Node::calcAvg(Node*) {
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
