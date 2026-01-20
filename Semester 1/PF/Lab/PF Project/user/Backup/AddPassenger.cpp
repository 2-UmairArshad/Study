#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
void addPassenger(Passenger passengerList[], int& passengerCount, int maxPassengers, const Flight flightList[], int flightCount) {
    if (passengerCount >= maxPassengers) {
        cout << "Cannot add more passengers. Maximum capacity reached.\n";
        return;
    }

    Passenger newPassenger;
    cout << "Enter Flight Number: ";
    cin >> newPassenger.flightNumber;

    // Check if the flight exists and has free seats
    bool flightFound = false;
    for (int i = 0; i < flightCount; ++i) {
        if (flightList[i].flightNumber == newPassenger.flightNumber) {
            if (flightList[i].bookedSeats < flightList[i].totalSeats) {
                flightFound = true;
                cout << "Enter Passenger Name: ";
                cin.ignore();
                getline(cin, newPassenger.name);
                cout << "Enter Seat Number (1-" << flightList[i].totalSeats << "): ";
                cin >> newPassenger.seatNumber;

                if (newPassenger.seatNumber < 1 || newPassenger.seatNumber > flightList[i].totalSeats) {
                    cout << "Invalid seat number. Try again.\n";
                    return;
                }

                // Update flight details
                flightList[i].bookedSeats++;
                passengerList[passengerCount++] = newPassenger;
                cout << "Passenger added successfully!\n";
                return;
            } else {
                cout << "No available seats on this flight.\n";
                return;
            }
        }
    }

    if (!flightFound) {
        cout << "Flight not found.\n";
    }
}
