#include <iostream>
#include <vector>
#include <string>
#include <algorithm>#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

struct Node {
private:
    std::vector<int> ratings;
    std::string title;
    std::string genre;
    float avgRating = 0.0;
    Node(std::string t, std::string g, std::vector<int> r,) : title(t), ratings(r){
        calcAvg();
    }
    float calcAvg();

};

class MaxHeap {
    Node* CurNode;

};