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
    getline(file, line);  // Optionally skip the header if not needed

    while (getline(file, line)) {
        stringstream ss(line);
        string cell;
        int currentColumn = 0;  // Initialize to 0 for each new line

        // Ensure you are using the correct delimiter. If unsure, check the actual CSV file.
        while (getline(ss, cell, ';')) {  // Change ';' to ',' if your file uses commas
            if (currentColumn == columnIndex) {
                cout << "check 2" << endl;
                break;  // Stop processing this line once the required column is found
            }
            currentColumn++;
        }
    }

    file.close();
}

int main() {
    string filename = "C://Users//myakh//CLionProjects//project_3//Fraudulent_E-Commerce_Transaction_Data.csv";
    int columnIndex = 2;  // Specify the column index to print (0-based)
    printColumn(filename, columnIndex);
    return 0;
}
