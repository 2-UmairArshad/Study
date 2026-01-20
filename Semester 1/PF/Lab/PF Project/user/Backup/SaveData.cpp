#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
void saveData(const Flight flightList[], int flightCount, const Passenger passengerList[], int passengerCount) {
    ofstream flightFile("flights.txt"), passengerFile("passengers.txt");

    for (int i = 0; i < flightCount; ++i) {
        flightFile << flightList[i].flightNumber << ","
                   << flightList[i].origin << ","
                   << flightList[i].destination << ","
                   << flightList[i].departureTime << ","
                   << flightList[i].totalSeats << ","
                   << flightList[i].bookedSeats << ","
                   << flightList[i].ticketPrice << ","
                   << flightList[i].revenue << "\n";
    }

    for (int i = 0; i < passengerCount; ++i) {
        passengerFile << passengerList[i].flightNumber << ","
                      << passengerList[i].name << ","
                      << passengerList[i].seatNumber << "\n";
    }

    flightFile.close();
    passengerFile.close();
}
