#include "Transactions.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <chrono>
using namespace std;
// this file basically just iterates performs all sorts and bonus function and couts everything to the screen so that the front end can parse it
int main(int argc, char* argv[]) {
    Transactions transactions;
    transactions.readTransactionsCaller("C:/Users/jazly/alliancebranch/GSA/transactions.txt"); //change this and enter the filepath here


    vector<Transactions::Node*> sortedNodesMergeAge;
    vector<Transactions::Node*> sortedNodesMergeAmount; // create all necessary vectors to store sorted vectors
    vector<Transactions::Node*> sortedNodesQuickAge;
    vector<Transactions::Node*> sortedNodesQuickAmount;

        auto beginMergeAge = chrono::high_resolution_clock::now(); // timer start to keep track of how long a sort takes
        sortedNodesMergeAge = transactions.mergeSortAge(transactions.getNodes());
        auto endMergeAge = chrono::high_resolution_clock::now(); // end to keep track
        auto durationMergeAge = chrono::duration_cast<std::chrono::milliseconds>(endMergeAge - beginMergeAge); // this finds the total duration
        auto beginQuickAge = chrono::high_resolution_clock::now();
        sortedNodesQuickAge = transactions.quickSortAge(transactions.getNodes());
        auto endQuickAge = chrono::high_resolution_clock::now();
        auto durationQuickAge = chrono::duration_cast<std::chrono::milliseconds>(endQuickAge - beginQuickAge);
        // all sorts have their own timing clock logic
        auto beginMergeAmount = chrono::high_resolution_clock::now();
        sortedNodesMergeAmount = transactions.mergeSortAmount(transactions.getNodes());
        auto endMergeAmount = chrono::high_resolution_clock::now();
        auto durationMergeAmount = chrono::duration_cast<std::chrono::milliseconds>(endMergeAmount - beginMergeAmount);
        auto beginQuickAmount = chrono::high_resolution_clock::now();
        sortedNodesQuickAmount = transactions.quickSortAmount(transactions.getNodes());
        auto endQuickAmount = chrono::high_resolution_clock::now();
        auto durationQuickAmount = chrono::duration_cast<std::chrono::milliseconds>(endQuickAmount - beginQuickAmount);

        double tAmount = transactions.getAvgTransactionAmount(transactions.getNodes()); // storing result for cout
        double tAge = transactions.getAvgAccountAge(transactions.getNodes()); // storing result for cout

    cout << "Merge Sorted by Account Age (only first 100 elements) \n" << "Time to merge sort by account age: " << durationMergeAge.count() << " milliseconds" << endl;
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
    cout <<"Quick Sorted by Account Age (only first 100 elements) \n" << "Time to quick sort by account age: " << durationQuickAge.count() << " milliseconds" << endl;
    count = 0;
    for (const auto& node : sortedNodesQuickAge) { // these for loops iterate throgh the sorted vectors and output all attriibutes of the first 100 since 1,000,000 is too long to cout
        if (count >= 100) break;
        cout << "Transaction Type: " << node->transactionType
             << ", Amount: $" << node->transactionAmount
             << ", Account Age: " << node->accountAge
             << ", Is Fraudulent: " << (node->isFraudulent ? "Yes" : "No") << endl;
        count++;
    }
    cout << endl;
    cout << "Merge Sorted by Transaction Amount (only first 100 elements) \n" <<"Time to merge sort by transaction amount: " << durationMergeAmount.count() << " milliseconds" << endl;
    count = 0;
    for (const auto& node : sortedNodesMergeAmount) {
        if (count >= 100) break;
        cout << "Transaction Type: " << node->transactionType
             << ", Amount: $" << node->transactionAmount
             << ", Account Age: " << node->accountAge
             << ", Is Fraudulent: " << (node->isFraudulent ? "Yes" : "No") << endl;
        count++;
    }
    cout << endl;
    cout <<"Quick Sorted by Transaction Amount (only first 100 elements) \n" << "Time to quick sort by transaction amount: " << durationQuickAmount.count() << " milliseconds" << endl;
    count = 0;
    for (const auto& node : sortedNodesQuickAmount) {
        if (count >= 100) break;
        cout << "Transaction Type: " << node->transactionType
             << ", Amount: $" << node->transactionAmount
             << ", Account Age: " << node->accountAge
             << ", Is Fraudulent: " << (node->isFraudulent ? "Yes" : "No") << endl;
        count++;
    }
    cout << endl;
    cout << "Statistics of Fraudulent Transactions:\n" << "Average Fraudulent Transaction Amount: " << tAmount << "\n"
    << "Average Fraudulent Account Age: " << tAge << "\n" << "Fraud Rate of Transaction Types: \n";

    transactions.getFraudulentRate(transactions.getNodes()); // ccall this function which couts fraud rates of each transacion type

    return 0;
}
