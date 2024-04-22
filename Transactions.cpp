#include "Transactions.h"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iostream>
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

void Transactions::readTransactions(const string& filename) {
    ifstream file(filename);
    string line;
    getline(file, line);

    while (getline(file, line)) {
        stringstream ss(line);
        vector<string> transactionData;
        string data;

        while (getline(ss, data, ',')) {
            transactionData.push_back(data);
        }

        double amount = stod(transactionData[0]);
        string type = transactionData[1];
        bool isFraudulent = transactionData[2] == "1";
        int age = stoi(transactionData[3]);

        Node* newNode = new Node(type, amount, age, isFraudulent);
        transactionNodes.push_back(newNode);
    }
    file.close();
}

void Transactions::readTransactionsCaller(const std::string &filename) {
    readTransactions(filename);
}

vector<Transactions::Node*> Transactions::getNodes() const{
    return this->transactionNodes;
}

double Transactions::getAvgAccountAge(const std::vector<Node*>& nodes) const {
    double totalAge = 0;
    int count = 0;
    for (const Node* node : nodes) {
        if (node->isFraudulent) {
            totalAge += node->accountAge;
            count++;
        }
    }
    if (count > 0) {
        return totalAge / count;
    } else {
        return 0;
    }
}

double Transactions::getAvgTransactionAmount(const std::vector<Node*>& nodes) const {
    double totalAmount = 0;
    int count = 0;
    for (const Node* node : nodes) {
        if (node->isFraudulent) {
            totalAmount += node->transactionAmount;
            count++;
        }
    }

    if (count > 0) {
        return totalAmount / count;
    } else {
        return 0;
    }
}

void Transactions::getFraudulentRate(const std::vector<Node*>& nodes) const {
    double btCount = 0;
    double creditCount = 0;
    double debitCount = 0;
    double paypalCount = 0;
    double btFraudCount = 0;
    double creditFraudCount = 0;
    double debitFraudCount = 0;
    double paypalFraudCount = 0;
    for (const auto& node : nodes) {
        if (node->transactionType == "bank transfer") {
            btCount++;
            if (node->isFraudulent) {
                btFraudCount++;
            }
        }
        else if (node->transactionType == "credit card") {
            creditCount++;
            if (node->isFraudulent) {
                creditFraudCount++;
            }
        }
        else if (node->transactionType == "debit card") {
            debitCount++;
            if (node->isFraudulent) {
                debitFraudCount++;
            }
        }
        else if (node->transactionType == "PayPal") {
            paypalCount++;
            if (node->isFraudulent) {
                paypalFraudCount++;
            }
        }
    }
    double btPercent = (btFraudCount / btCount) * 100;
    double creditPercent = (creditFraudCount / creditCount) * 100;
    double debitPercent = (debitFraudCount / debitCount) * 100;
    double paypalPercent = (paypalFraudCount / paypalCount) * 100;


    cout << "Bank Transfer: " << btPercent << "%\n" << "Credit Card: " << creditPercent << "%\n"
    << "Debit Card: " << debitPercent << "%\n" << "PayPal: " << paypalPercent<< endl;
}