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

    public:
        Node(std::string type, double amount, int age) : transactionType(type), transactionAmount(amount), accountAge(age) {}
    };

private:
    std::vector<Node*> transactionNodes; // Use smart pointers for better memory management

public:
    std::vector<Node*> mergeSortAge(const std::vector<Node*>& nodes) const;
    std::vector<Node*> quickSortAge(const std::vector<Node*>& nodes) const;
    std::vector<Node*> mergeSortAmount(const std::vector<Node*>& nodes) const;
    std::vector<Node*> quickSortAmount(const std::vector<Node*>& nodes) const;
};
