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
    transactions.readTransactionsCaller("C:/Users/elias/Downloads/new commerce data.txt"); //change this and enter the filepath here

    vector<Transactions::Node*> sortedNodesMergeAge;
    vector<Transactions::Node*> sortedNodesMergeAmount;
    vector<Transactions::Node*> sortedNodesQuickAge;
    vector<Transactions::Node*> sortedNodesQuickAmount;

        auto beginMergeAge = chrono::high_resolution_clock::now();
        sortedNodesMergeAge = transactions.mergeSortAge(transactions.getNodes());
        auto endMergeAge = chrono::high_resolution_clock::now();
        auto durationMergeAge = chrono::duration_cast<std::chrono::milliseconds>(endMergeAge - beginMergeAge);
        auto beginQuickAge = chrono::high_resolution_clock::now();
        sortedNodesQuickAge = transactions.quickSortAge(transactions.getNodes());
        auto endQuickAge = chrono::high_resolution_clock::now();
        auto durationQuickAge = chrono::duration_cast<std::chrono::milliseconds>(endQuickAge - beginQuickAge);

        auto beginMergeAmount = chrono::high_resolution_clock::now();
        sortedNodesMergeAmount = transactions.mergeSortAmount(transactions.getNodes());
        auto endMergeAmount = chrono::high_resolution_clock::now();
        auto durationMergeAmount = chrono::duration_cast<std::chrono::milliseconds>(endMergeAmount - beginMergeAmount);
        auto beginQuickAmount = chrono::high_resolution_clock::now();
        sortedNodesQuickAmount = transactions.quickSortAmount(transactions.getNodes());
        auto endQuickAmount = chrono::high_resolution_clock::now();
        auto durationQuickAmount = chrono::duration_cast<std::chrono::milliseconds>(endQuickAmount - beginQuickAmount);

        double tAmount = transactions.getAvgTransactionAmount(transactions.getNodes());
        double tAge = transactions.getAvgAccountAge(transactions.getNodes());

    cout << durationMergeAge.count() << endl;
    int count = 0;
    for (const auto& node : sortedNodesMergeAge) {
        if (count >= 100) break;
        cout << "Transaction Type: " << node->transactionType
             << ", Amount: $" << node->transactionAmount
             << ", Account Age: " << node->accountAge
             << ", Is Fraudulent: " << (node->isFraudulent ? "Yes" : "No") << endl;
        count++;
    }
    cout << endl;
    cout << durationMergeAmount.count() << endl;
    count = 0;
    for (const auto& node : sortedNodesMergeAmount) {
        if (count >= 100) break;
        cout << "Transaction Type: " << node->transactionType
             << ", Amount: $" << node->transactionAmount
             << ", Account Age: " << node->accountAge
             << ", Is Fraudulent: " << (node->isFraudulent ? "Yes" : "No") << endl;
        count++;
    }

    cout << durationQuickAge.count();
    count = 0;
    for (const auto& node : sortedNodesQuickAge) {
        if (count >= 100) break;
        cout << "Transaction Type: " << node->transactionType
             << ", Amount: $" << node->transactionAmount
             << ", Account Age: " << node->accountAge
             << ", Is Fraudulent: " << (node->isFraudulent ? "Yes" : "No") << endl;
        count++;
    }

    cout << durationQuickAmount.count();
    count = 0;
    for (const auto& node : sortedNodesQuickAmount) {
        if (count >= 100) break;
        cout << "Transaction Type: " << node->transactionType
             << ", Amount: $" << node->transactionAmount
             << ", Account Age: " << node->accountAge
             << ", Is Fraudulent: " << (node->isFraudulent ? "Yes" : "No") << endl;
        count++;
    }

    cout << "Statistics of Fraudulent Transactions:\n" << "Average Fraudulent Transaction Amount: " << tAmount << "\n"
    << "Average Fraudulent Account Age: " << tAge << "\n" << "Fraud Rate of Transaction Types: \n";

    transactions.getFraudulentRate(transactions.getNodes());

    return 0;
}