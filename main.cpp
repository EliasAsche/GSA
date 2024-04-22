#include <iostream>
#include <vector>
#include <string>
#include "Transactions.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cout << "Usage: " << argv[0] << " sort_field (age/amount) sort_method (merge/quick)" << endl;
        return 1;
    }

    string sort_field(argv[1]);
    string sort_method(argv[2]);
    Transactions transactions;  // Assuming you have a way to initialize this with data

    vector<Transactions::Node*> sorted_nodes;
    if (sort_field == "age") {
        if (sort_method == "merge") {
            sorted_nodes = transactions.mergeSortAge(transactions.getNodes()); // Assume getNodes returns all nodes
        } 
        else if (sort_method == "quick") {
            sorted_nodes = transactions.quickSortAge(transactions.getNodes());
        } 
        else {
            cout << "Invalid sort method" << endl;
            return 1;
        }
    } 
    else if (sort_field == "amount") {
        if (sort_method == "merge") {
            sorted_nodes = transactions.mergeSortAmount(transactions.getNodes());
        } 
        else if (sort_method == "quick") {
            sorted_nodes = transactions.quickSortAmount(transactions.getNodes());
        } 
        else {
            cout << "Invalid sort method" << endl;
            return 1;
        }
    } 
    else {
        cout << "Invalid sort field" << endl;
        return 1;
    }

    for (const auto& node : sorted_nodes) {
        cout << "Account Age: " << node->accountAge << ", Transaction Amount: $" << node->transactionAmount << endl;
    }

    return 0;
}
