#include <iostream>
#include <fstream>
using namespace std;

int main() {
    ofstream outFile("student.txt");
    if (outFile.is_open()) {
        outFile << "Name: John Doe\n";
        outFile << "Age: 20\n";
        outFile << "Course: Computer Science\n";
        outFile.close();
        cout << "Data written to student.txt successfully.\n";
    } else {
        cout << "Error: Unable to open file for writing.\n";
    }
    return 0;
}
