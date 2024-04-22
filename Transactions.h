#pragma once
#include <string>
#include <vector>

class Transactions {
public:
    struct Node {
        std::string transactionType;
        double transactionAmount;
        int accountAge;
        bool isFraudulent;
        Node(std::string type, double amount, int age, int isFraud) : transactionType(type), transactionAmount(amount), accountAge(age), isFraudulent(isFraud) {}
    };

    Transactions() = default;
    ~Transactions() = default;
    std::vector<Node*> getNodes() const;
    void readTransactionsCaller(const std::string& filename);
    std::vector<Node*> mergeSortAge(const std::vector<Node*>& nodes) const;
    std::vector<Node*> quickSortAge(const std::vector<Node*>& nodes) const;
    std::vector<Node*> mergeSortAmount(const std::vector<Node*>& nodes) const;
    std::vector<Node*> quickSortAmount(const std::vector<Node*>& nodes) const;
    double getAvgAccountAge(const std::vector<Node*>& nodes) const;
    double getAvgTransactionAmount(const std::vector<Node*>& nodes) const;
    void getFraudulentRate(const std::vector<Node*>& nodes) const;

private:
    std::vector<Node*> transactionNodes;
    void readTransactions(const std::string& filename);
};