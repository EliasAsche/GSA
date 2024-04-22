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
    transactions.readTransactionsCaller(filePath); //change this and enter the filepath here

    vector<Transactions::Node*> sortedNodesMerge;
    vector<Transactions::Node*> sortedNodesQuick;

        auto beginMergeAge = chrono::high_resolution_clock::now();
        sortedNodesMerge = transactions.mergeSortAge(transactions.getNodes());
        auto endMergeAge = chrono::high_resolution_clock::now();
        auto durationMergeAge = chrono::duration_cast<std::chrono::milliseconds>(endMergeAge - beginMergeAge);
        auto beginQuickAge = chrono::high_resolution_clock::now();
        auto sortedNodesQuickAge = transactions.quickSortAge(transactions.getNodes());
        auto endQuickAge = chrono::high_resolution_clock::now();
        auto durationQuickAge = chrono::duration_cast<std::chrono::milliseconds>(endQuickAge - beginQuickAge);

        auto beginMergeAmount = chrono::high_resolution_clock::now();
        auto sortedNodesMergeAmount = transactions.mergeSortAmount(transactions.getNodes());
        auto endMergeAmount = chrono::high_resolution_clock::now();
        auto durationMergeAmount = chrono::duration_cast<std::chrono::milliseconds>(endMergeAmount - beginMergeAmount);
        auto beginQuickAmount = chrono::high_resolution_clock::now();
        auto sortedNodesQuickAmount = transactions.quickSortAmount(transactions.getNodes());
        auto endQuickAmount = chrono::high_resolution_clock::now();
        auto durationQuickAmount = chrono::duration_cast<std::chrono::milliseconds>(endQuickAmount - beginQuickAmount);

        double tAmount = transactions.getAvgTransactionAmount(transactions.getNodes());
        double tAge = transactions.getAvgAccountAge(transactions.getNodes());

    for (const auto& node : sortedNodesMerge) {
        cout << "Transaction Type: " << node->transactionType
             << ", Amount: $" << node->transactionAmount
             << ", Account Age: " << node->accountAge
             << ", Is Fraudulent: " << (node->isFraudulent ? "Yes" : "No") << endl;
    }
    cout << durationMergeAge.count();
    cout << durationMergeAmount.count();
    for (const auto& node : sortedNodesQuick) {
        cout << "Transaction Type: " << node->transactionType
             << ", Amount: $" << node->transactionAmount
             << ", Account Age: " << node->accountAge
             << ", Is Fraudulent: " << (node->isFraudulent ? "Yes" : "No") << endl;
    }
    cout << durationQuickAge.count();
    cout << durationQuickAmount.count();

    cout << "Statistics of Fraudulent Transactions:\n" << "Average Fraudulent Transaction Amount: " << tAmount << "\n"
    << "Average Fraudulent Account Age: " << tAge << "\n" << "Fraud Rate of Transaction Types: \n";

    transactions.getFraudulentRate(transactions.getNodes());

    return 0;
}