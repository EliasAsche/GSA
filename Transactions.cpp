#include "Transactions.h"
#include <algorithm>
#include <fstream>
#include <sstream>
using namespace std;

vector<Transactions::Node*> mergeByAge(const vector<Transactions::Node*>& left, const vector<Transactions::Node*>& right) {
    vector<Transactions::Node*> result;
    unsigned leftIndex = 0, rightIndex = 0;
    while (leftIndex < left.size() && rightIndex < right.size()) {
        if (left[leftIndex]->accountAge <= right[rightIndex]->accountAge) {
            result.push_back(left[leftIndex]);
            leftIndex++;
        } else {
            result.push_back(right[rightIndex]);
            rightIndex++;
        }
    }
    result.insert(result.end(), left.begin() + leftIndex, left.end());
    result.insert(result.end(), right.begin() + rightIndex, right.end());
    return result;
}

vector<Transactions::Node*> Transactions::mergeSortAge(const vector<Node*>& nodes) const {
    if (nodes.size() <= 1) {
        return nodes;
    }
    int mid = nodes.size() / 2;
    vector<Node*> left(nodes.begin(), nodes.begin() + mid);
    vector<Node*> right(nodes.begin() + mid, nodes.end());
    return mergeByAge(mergeSortAge(left), mergeSortAge(right));
}

vector<Transactions::Node*> Transactions::quickSortAge(const vector<Node*>& nodes) const {
    if (nodes.size() <= 1) {
        return nodes;
    }
    vector<Node*> less, equal, greater;
    Node* pivot = nodes[nodes.size() / 2];
    for (Node* node : nodes) {
        if (node->accountAge < pivot->accountAge) {
            less.push_back(node);
        } else if (node->accountAge > pivot->accountAge) {
            greater.push_back(node);
        } else {
            equal.push_back(node);
        }
    }
    less = quickSortAge(less);
    greater = quickSortAge(greater);
    less.insert(less.end(), equal.begin(), equal.end());
    less.insert(less.end(), greater.begin(), greater.end());
    return less;
}

vector<Transactions::Node*> mergeByAmount(const vector<Transactions::Node*>& left, const vector<Transactions::Node*>& right) {
    vector<Transactions::Node*> result;
    unsigned leftIndex = 0, rightIndex = 0;
    while (leftIndex < left.size() && rightIndex < right.size()) {
        if (left[leftIndex]->transactionAmount <= right[rightIndex]->transactionAmount) {
            result.push_back(left[leftIndex]);
            leftIndex++;
        } else {
            result.push_back(right[rightIndex]);
            rightIndex++;
        }
    }
    result.insert(result.end(), left.begin() + leftIndex, left.end());
    result.insert(result.end(), right.begin() + rightIndex, right.end());
    return result;
}

vector<Transactions::Node*> Transactions::mergeSortAmount(const vector<Node*>& nodes) const {
    if (nodes.size() <= 1) {
        return nodes;
    }
    int mid = nodes.size() / 2;
    vector<Node*> left(nodes.begin(), nodes.begin() + mid);
    vector<Node*> right(nodes.begin() + mid, nodes.end());
    return mergeByAmount(mergeSortAmount(left), mergeSortAmount(right));
}

vector<Transactions::Node*> Transactions::quickSortAmount(const vector<Node*>& nodes) const {
    if (nodes.size() <= 1) {
        return nodes;
    }
    vector<Node*> less, equal, greater;
    Node* pivot = nodes[nodes.size() / 2];
    for (Node* node : nodes) {
        if (node->transactionAmount < pivot->transactionAmount) {
            less.push_back(node);
        } else if (node->transactionAmount > pivot->transactionAmount) {
            greater.push_back(node);
        } else {
            equal.push_back(node);
        }
    }
    less = quickSortAmount(less);
    greater = quickSortAmount(greater);
    less.insert(less.end(), equal.begin(), equal.end());
    less.insert(less.end(), greater.begin(), greater.end());
    return less;
}

void Transactions::readTransactions(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::vector<std::string> transactionData;
        std::string data;

        while (std::getline(ss, data, ',')) {
            transactionData.push_back(data);
        }

        double amount = std::stod(transactionData[0]);
        std::string type = transactionData[1];
        bool isFraudulent = transactionData[2] == "1";
        int age = std::stoi(transactionData[3]);

        Node* newNode = new Node(type, amount, age, isFraudulent);
        transactionNodes.push_back(newNode);// Optionally display the node data
    }
    file.close();
}
