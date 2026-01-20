#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
void displayFlights(const Flight flightList[], int flightCount) {
    if (flightCount == 0) {
        cout << "No flights available.\n";
        return;
    }

    cout << "Flight List:\n";
    for (int i = 0; i < flightCount; ++i) {
        cout << "Flight Number: " << flightList[i].flightNumber
             << ", Origin: " << flightList[i].origin
             << ", Destination: " << flightList[i].destination
             << ", Departure Time: " << flightList[i].departureTime
             << ", Seats: " << flightList[i].bookedSeats << "/" << flightList[i].totalSeats
             << ", Ticket Price: $" << fixed << setprecision(2) << flightList[i].ticketPrice
             << ", Revenue: $" << flightList[i].revenue << "\n";
    }
}
