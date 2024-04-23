#pragma once
#include <string>
#include <vector>

class Transactions {
public:
    struct Node { // Nested Node structure to contain all transaction data in one piece of data for ease of passing and connection
        std::string transactionType;
        double transactionAmount;
        int accountAge;
        bool isFraudulent;
        Node(std::string type, double amount, int age, int isFraud) : transactionType(type), transactionAmount(amount), accountAge(age), isFraudulent(isFraud) {}
    };

    Transactions() = default; // Default constructor and destructor
    ~Transactions() = default;
    std::vector<Node*> getNodes() const; // All functions are const as they enssure the user is unable to manipulate any important data with public functions
    void readTransactionsCaller(const std::string& filename);
    std::vector<Node*> mergeSortAge(const std::vector<Node*>& nodes) const; // these functions don't need callers as they cannot manipulate the data directly
    std::vector<Node*> quickSortAge(const std::vector<Node*>& nodes) const;
    std::vector<Node*> mergeSortAmount(const std::vector<Node*>& nodes) const;
    std::vector<Node*> quickSortAmount(const std::vector<Node*>& nodes) const;
    double getAvgAccountAge(const std::vector<Node*>& nodes) const;
    double getAvgTransactionAmount(const std::vector<Node*>& nodes) const;
    void getFraudulentRate(const std::vector<Node*>& nodes) const;

private:
    std::vector<Node*> transactionNodes; // vector which holds all the nodes of transactions so it is easy to iterate through all the transaciotns
    void readTransactions(const std::string& filename);
};
