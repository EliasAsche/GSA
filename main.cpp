#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

//splitting up the token data created in python
vector<string> split(const string &s, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

//reading and printing the CSV data
void readAndPrintCSV(const string &filePath) {
    ifstream file(filePath);
    string line;

    if (!file.is_open()) {
        cerr << "Failed to open file\n";
        return;
    }

    while (getline(file, line)) {
        vector<string> tokens = split(line, ',');
        for (const string& token : tokens) {
            cout << token << " ";
        }
        cout << endl;
    }

    file.close();
}

int main() {
    string filePath = R"(C:\Users\myakh\PycharmProjects\DSA Project 3\new commerce data.txt)";
    readAndPrintCSV(filePath);
    return 0;
}
