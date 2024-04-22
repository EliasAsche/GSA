#pragma once
#include <string>
#include <vector>
#include <memory> // For smart pointers

class Transactions {
public:
    struct Node {
    private:
        std::string transactionType;
        double transactionAmount;
        int accountAge;
        int isFradulent;

    public:
        Node(std::string type, double amount, int age, int isFraud) : transactionType(type), transactionAmount(amount), accountAge(age), isFradulent(isFraud) {}
    };

private:
    std::vector<Node*> transactionNodes; // Use smart pointers for better memory management

public:
    std::vector<Node*> mergeSortAge(const std::vector<Node*>& nodes) const;
    std::vector<Node*> quickSortAge(const std::vector<Node*>& nodes) const;
    std::vector<Node*> mergeSortAmount(const std::vector<Node*>& nodes) const;
    std::vector<Node*> quickSortAmount(const std::vector<Node*>& nodes) const;
    void readTransactions(const std::string& filename);
};
