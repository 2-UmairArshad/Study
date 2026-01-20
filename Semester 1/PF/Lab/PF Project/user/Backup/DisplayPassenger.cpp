#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
void displayPassengers(const Passenger passengerList[], int passengerCount) {
    if (passengerCount == 0) {
        cout << "No passengers available.\n";
        return;
    }

    cout << "Passenger List:\n";
    for (int i = 0; i < passengerCount; ++i) {
        cout << "Passenger Name: " << passengerList[i].name
             << ", Flight Number: " << passengerList[i].flightNumber
             << ", Seat Number: " << passengerList[i].seatNumber << "\n";
    }
}