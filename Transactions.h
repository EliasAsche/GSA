#pragma once
#include <string>
#include <vector>

class Transactions {
public:
    struct Node {
        std::string transactionType;
        double transactionAmount;
        int accountAge;
        int isFraudulent;
        Node(std::string type, double amount, int age, int isFraud) : transactionType(type), transactionAmount(amount), accountAge(age), isFraudulent(isFraud) {}
    };

private:
    std::vector<Node*> transactionNodes; // Use smart pointers for better memory management

public:
    const std::vector<Node*>& getNodes() const { return transactionNodes; }
    std::vector<Node*> mergeSortAge(const std::vector<Node*>& nodes) const;
    std::vector<Node*> quickSortAge(const std::vector<Node*>& nodes) const;
    std::vector<Node*> mergeSortAmount(const std::vector<Node*>& nodes) const;
    std::vector<Node*> quickSortAmount(const std::vector<Node*>& nodes) const;
    void readTransactions(const std::string& filename);

};