#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    ifstream inFile("student.txt");
    string line;

    if (inFile.is_open()) {
        cout << "Content of student.txt:\n";
        while (getline(inFile, line)) {
            cout << line << endl;
        }
        inFile.close();
    }
    return 0;
}
