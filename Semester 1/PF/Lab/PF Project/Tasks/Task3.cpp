#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    ofstream ofile("data.txt");
    ifstream inFile("data.txt");
    string word;
    int wordCount = 0;
    if(ofile.is_open())
    {
        ofile<<"hi hello hi hi hi hi hi hi hi hi hi";
    }
    ofile.close();
    if (inFile.is_open()) {
        while (inFile >> word) {
            wordCount++;
        }
        inFile.close();
        cout << "Total number of words: " << wordCount << endl;
    } else {
        cout << "Error: Unable to open file for reading.\n";
    }
    return 0;
}
