#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
void setRevenue(Flight flightList[], int flightCount) {
    int flightNumber;
    cout << "Enter Flight Number: ";
    cin >> flightNumber;

    for (int i = 0; i < flightCount; ++i) {
        if (flightList[i].flightNumber == flightNumber) {
            cout << "Enter Revenue for this Flight: ";
            cin >> flightList[i].revenue;
            cout << "Revenue updated successfully!\n";
            return;
        }
    }

    cout << "Flight not found.\n";
}
