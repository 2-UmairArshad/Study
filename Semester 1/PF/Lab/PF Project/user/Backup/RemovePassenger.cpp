#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
void removePassenger(Passenger passengerList[], int& passengerCount) {
    if (passengerCount == 0) {
        cout << "No passengers to remove.\n";
        return;
    }

    string nameToRemove;
    cout << "Enter Passenger Name to Remove: ";
    cin.ignore();
    getline(cin, nameToRemove);

    for (int i = 0; i < passengerCount; ++i) {
        if (passengerList[i].name == nameToRemove) {
            for (int j = i; j < passengerCount - 1; ++j) {
                passengerList[j] = passengerList[j + 1];
            }
            passengerCount--;
            cout << "Passenger removed successfully.\n";
            return;
        }
    }

    cout << "Passenger not found.\n";
}
