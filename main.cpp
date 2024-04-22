#include "Transactions.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm> // For std::sort
using namespace std;

int main(int argc, char* argv[]) {
    /*if (argc != 2) {
        cout << "Usage: " << argv[0] << " <sort_method>" << endl;
        return 1;
    }*/

    string sortMethod;
    //string sortMethod = argv[1];
    Transactions transactions;
    string filePath = "transactions.txt";
    transactions.readTransactions(filePath);

    cin >> sortMethod;

    vector<Transactions::Node*> sortedNodes = (sortMethod == "merge") ?
        transactions.mergeSortAge(transactions.getNodes()) :
        transactions.quickSortAge(transactions.getNodes());

    // Assuming Node* list is now sorted, display only the top 10 or fewer if there aren't 10
    size_t count = min(sortedNodes.size(), size_t(10));
    cout << "Top Transactions:\n";
    for (size_t i = 0; i < count; i++) {
        cout << "Amount: $" << sortedNodes[i]->transactionAmount
                  << ", Fraudulent: " << (sortedNodes[i]->isFraudulent ? "Yes" : "No") << endl;
    }

    return 0;
}

