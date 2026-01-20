#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    // Append new data
    ofstream outFile("student.txt", ios::app); // Open file in append mode
    if (outFile.is_open()) {
        outFile << "Hobbies: Reading, Coding\n";
        outFile.close();
        cout << "Data appended to student.txt successfully.\n";
    } else {
        cout << "Error: Unable to open file for appending.\n";
    }

    // Display updated content
    ifstream inFile("student.txt");
    string line;
    if (inFile.is_open()) {
        cout << "Updated content of student.txt:\n";
        while (getline(inFile, line)) {
            cout << line << endl;
        }
        inFile.close();
    } else {
        cout << "Error: Unable to open file for reading.\n";
    }
    return 0;
}
