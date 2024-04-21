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
    Node(std::string type,  std::vector<double> tA) : transactionType(type), transactionAmounts(tA){
        calcAvg(M);
    }
    double calcAvg(Node*);
public:
    //add more here

};

class MaxHeap {
    std::vector<Node*> transactionHeap;


};