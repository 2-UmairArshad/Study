#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    ofstream sourceFile("source.txt");
    ifstream destinationFile("destination.txt");
    string line;

    if (sourceFile.is_open() && destinationFile.is_open()) {
        while (getline(sourceFile, line)) {
            destinationFile << line << endl; // Copy each line
        }
        sourceFile.close();
        destinationFile.close();
        cout << "Content copied to destination.txt successfully.\n";
    } else {
        cout << "Error: Unable to open source or destination file.\n";
    }
    return 0;
}
