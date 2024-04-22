#include "Transactions.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 4) {
        cout << "Usage: " << argv[0] << " <file_path> <sort_field> <sort_method>" << endl;
        cout << "sort_field: age or amount" << endl;
        cout << "sort_method: merge or quick" << endl;
        return 1;
    }

    string filePath = argv[1];
    string sortField = argv[2];
    string sortMethod = argv[3];

    Transactions transactions;
    transactions.readTransactions(filePath);

    vector<Transactions::Node*> sortedNodes;

    if (sortField == "age") {
        if (sortMethod == "merge") {
            sortedNodes = transactions.mergeSortAge(transactions.getNodes());
        } else if (sortMethod == "quick") {
            sortedNodes = transactions.quickSortAge(transactions.getNodes());
        } else {
            cout << "Invalid sort method. Use 'merge' or 'quick'." << endl;
            return 1;
        }
    } else if (sortField == "amount") {
        if (sortMethod == "merge") {
            sortedNodes = transactions.mergeSortAmount(transactions.getNodes());
        } else if (sortMethod == "quick") {
            sortedNodes = transactions.quickSortAmount(transactions.getNodes());
        } else {
            cout << "Invalid sort method. Use 'merge' or 'quick'." << endl;
            return 1;
        }
    } else {
        cout << "Invalid sort field. Use 'age' or 'amount'." << endl;
        return 1;
    }

    for (const auto& node : sortedNodes) {
        cout << "Transaction Type: " << node->transactionType
             << ", Amount: $" << node->transactionAmount
             << ", Account Age: " << node->accountAge
             << ", Is Fraudulent: " << (node->isFraudulent ? "Yes" : "No") << endl;
    }

    return 0;
}