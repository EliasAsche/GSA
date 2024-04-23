# GSA
DSA Final Project

How to Run the frontend:
- in main.cpp, change line 12 readTransactionsCaller parameter to the file path to the downloaded data set
- compile the project to produce the executable with this command: "g++ main.cpp transactions.cpp -o out2" in terminal
- should output a out2.exe file in directory
- to open the popup window, run this command in terminal: "python run.py"
- make sure to click restart after age or amount selection if not followed by fraud stats selection
- also ensure all neccesary libries (pysimpleGUI) are installed (it is in master branch)

How to run the back end:
- download the transactions files and main.cpp
- download the txt file with all of the data
- create a project in an IDE and add all of the cpp and header files (Should only be three)
- set up the file path in main.cpp to match where you downloaded txt file
- run the file!

Connecting everything:
- After the previous steps were completed (including creating the exe) create a project in vscode with all files from master (python and c++)
- ensure all file paths (pertaining to the txt file) are correct and the exe was properly generated
- upon running run.py the window will open and will be fully interactable



