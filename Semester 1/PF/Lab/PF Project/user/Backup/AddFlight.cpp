#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
void addFlight(Flight flightList[], int& flightCount, int maxFlights) {
    if (flightCount >= maxFlights) {
        cout << "Cannot add more flights. Maximum capacity reached.\n";
        return;
    }

    Flight newFlight;
    cout << "Enter Flight Number: ";
    cin >> newFlight.flightNumber;
    cin.ignore();
    cout << "Enter Origin: ";
    getline(cin, newFlight.origin);
    cout << "Enter Destination: ";
    getline(cin, newFlight.destination);
    cout << "Enter Departure Time (e.g., 14:30): ";
    getline(cin, newFlight.departureTime);
    cout << "Enter Total Seats: ";
    cin >> newFlight.totalSeats;
    newFlight.bookedSeats = 0;
    cout << "Enter Ticket Price: ";
    cin >> newFlight.ticketPrice;
    newFlight.revenue = 0.0;

    flightList[flightCount++] = newFlight;
    cout << "Flight added successfully!\n";
}