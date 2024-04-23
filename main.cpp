#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

//splitting up the token data created in python
vector<string> split(const string &s, char delimiter) {
    vector<string> tokens; //new vector that stores and splits up the string
    string token; //a temporary string that holds each split part
    istringstream tokenStream(s); //creating a string stream from the input string
    while (getline(tokenStream, token, delimiter)) { //extracting strings split by the delimiter
        tokens.push_back(token);
    }
    return tokens;
}

//reading and printing the CSV data
void readAndPrintCSV(const string &filePath) {
    ifstream file(filePath); //opens the file stream with given file path
    string line;

    if (!file.is_open()) {
        cerr << "Failed to open file\n";
        return;
    }

    while (getline(file, line)) {
        vector<string> tokens = split(line, ','); //splitting each line by the comma
        for (const string& token : tokens) {
            cout << token << " "; //printing each token followed by a space to ensure its saved correctly
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
