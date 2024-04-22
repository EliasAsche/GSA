<<<<<<< HEAD
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
=======
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// Function to split a string based on a delimiter and return a vector of strings
vector<string> split(const string &s, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

// Function to read and print CSV data
void readAndPrintCSV(const string &filePath) {
    ifstream file(filePath);
    string line;

    if (!file.is_open()) {
        cerr << "Failed to open file\n";
        return;
    }

    while (getline(file, line)) {
        vector<string> tokens = split(line, ',');
        for (const string& token : tokens) {
            cout << token << " ";
        }
        cout << endl;
    }

    file.close();
}

int main() {
    string filePath = R"(C:\Users\myakh\PycharmProjects\DSA Project 3\new commerce data.txt)";
    readAndPrintCSV(filePath);
    return 0;
}
>>>>>>> 86c2e62f225a764a17ff305b3cab4c288c49dded
