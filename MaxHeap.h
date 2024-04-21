#include <iostream>
#include <vector>
#include <string>
#include <algorithm>#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

struct Node {
private:
    std::vector<double> transactionAmounts;
    std::string transactionType;
    double avgAmount = 0.0;

public:
    Node(std::string type,  std::vector<double> tA) : transactionType(type), transactionAmounts(tA){
        calcAvg();
    }
    double calcAvg();
    std::string getTransactionType();
};

class MaxHeap {
    std::vector<Node*> transactionHeap;
    void heapifyDown(int index);

};