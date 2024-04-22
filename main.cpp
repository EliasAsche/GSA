#include "Transactions.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <chrono>
using namespace std;

int main(int argc, char* argv[]) {


    Transactions transactions;
    transactions.readTransactionsCaller(filePath);

    vector<Transactions::Node*> sortedNodesMerge;
    vector<Transactions::Node*> sortedNodesQuick;

    if (sortField == "age") {
        auto beginMerge = chrono::high_resolution_clock::now();
        sortedNodesMerge = transactions.mergeSortAge(transactions.getNodes());
        auto endMerge = chrono::high_resolution_clock::now();
        auto durationMerge = chrono::duration_cast<std::chrono::milliseconds>(endMerge - beginMerge);
        auto beginQuick = chrono::high_resolution_clock::now();
        sortedNodesQuick = transactions.quickSortAge(transactions.getNodes());
        auto endQuick = chrono::high_resolution_clock::now();
        auto durationQuick = chrono::duration_cast<std::chrono::milliseconds>(endQuick - beginQuick);
    }
    else if (sortField == "amount") {
        auto beginMerge = chrono::high_resolution_clock::now();
        sortedNodesMerge = transactions.mergeSortAmount(transactions.getNodes());
        auto endMerge = chrono::high_resolution_clock::now();
        auto durationMerge = chrono::duration_cast<std::chrono::milliseconds>(endMerge - beginMerge);
        sortedNodesQuick = transactions.quickSortAmount(transactions.getNodes());
    }

    for (const auto& node : sortedNodesMerge) {
        cout << "Transaction Type: " << node->transactionType
             << ", Amount: $" << node->transactionAmount
             << ", Account Age: " << node->accountAge
             << ", Is Fraudulent: " << (node->isFraudulent ? "Yes" : "No") << endl;
    }

    for (const auto& node : sortedNodesQuick) {
        cout << "Transaction Type: " << node->transactionType
             << ", Amount: $" << node->transactionAmount
             << ", Account Age: " << node->accountAge
             << ", Is Fraudulent: " << (node->isFraudulent ? "Yes" : "No") << endl;
    }

    return 0;
}