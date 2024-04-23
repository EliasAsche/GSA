# GSA
DSA Final Project

How to Run the frontend:
- in main.cpp, change line 12 readTransactionsCaller parameter to the file path to the downloaded data set
- compile the project to produce the executable with this command: "g++ main.cpp transactions.cpp -o out2" in terminal
- should output a out2.exe file in directory
- to open the popup window, run this command in terminal: "python run.py"
- make sure to click restart after age or amount selection if not followed by fraud stats selection

How the backend is set up:
- Transactions class with the nested Node structure, in which each hold the type, amount, age, and flag indicating whether its fraudulent
- File operation methods, such as readTransactions(const string& filename), which reads transaction data from a file and stores them into a vector
- The file operations also parse each line of the data fileand extracts the attributes and converts them into their specific types
  
