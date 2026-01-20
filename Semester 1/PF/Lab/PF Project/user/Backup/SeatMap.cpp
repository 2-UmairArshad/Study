#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
void showSeatMap(const Flight flightList[], int flightCount) {
    int flightNumber;
    cout << "Enter Flight Number: ";
    cin >> flightNumber;

    for (int i = 0; i < flightCount; ++i) {
        if (flightList[i].flightNumber == flightNumber) {
            cout << "Seat Map for Flight " << flightList[i].flightNumber << ":\n";
            for (int j = 1; j <= flightList[i].totalSeats; ++j) {
                if (j <= flightList[i].bookedSeats) {
                    cout << "* ";
                } else {
                    cout << "# ";
                }
                if (j % 10 == 0) cout << "\n";
            }
            cout << "\n";
            return;
        }
    }

    cout << "Flight not found.\n";
}