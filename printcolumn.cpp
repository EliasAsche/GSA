#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

void printColumn(const std::string& filename, int columnIndex) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Failed to open file: " << filename << endl;
        return;
    }

    string line;
    getline(file, line); 

    while (getline(file, line)) {
        stringstream ss(line);
        string cell;
        int currentColumn = 0; 

        while (getline(ss, cell, ';')) {  
            if (currentColumn == columnIndex) {
                cout << "check 2" << endl;
                break; 
            }
            currentColumn++;
        }
    }

    file.close();
}

int main() {
    string filename = "C://Users//myakh//CLionProjects//project_3//Fraudulent_E-Commerce_Transaction_Data.csv";
    int columnIndex = 2; 
    printColumn(filename, columnIndex);
    return 0;
}
