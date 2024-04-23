#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

void printColumn(const std::string& filename, int columnIndex) {
    ifstream file(filename);
    if (!file.is_open()) { //checking if the file is open
        cerr << "Failed to open file: " << filename << endl;
        return;
    }

    string line; //delaring a string to stoe each line read from the file
    getline(file, line); //reads and disregarding the headers

    while (getline(file, line)) {
        stringstream ss(line);
        string cell;
        int currentColumn = 0; //initializing the current column index to zero

        while (getline(ss, cell, ';')) {  
            if (currentColumn == columnIndex) { //checking if the current column is the one we are looking at
                cout << cell << endl; //outputting the value of the cell
                break; 
            }
            currentColumn++; //incremementing the column index
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
