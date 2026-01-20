#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
void loadData(Flight flightList[], int& flightCount, Passenger passengerList[], int& passengerCount) {
    ifstream flightFile("flights.txt"), passengerFile("passengers.txt");

    flightCount = 0;
    passengerCount = 0;

    if (flightFile.is_open()) {
        while (!flightFile.eof()) {
            Flight flight;
            flightFile >> flight.flightNumber;
            if (flightFile.eof()) break;
            flightFile.ignore();
            getline(flightFile, flight.origin, ',');
            getline(flightFile, flight.destination, ',');
            getline(flightFile, flight.departureTime, ',');
            flightFile >> flight.totalSeats >> flight.bookedSeats >> flight.ticketPrice >> flight.revenue;
            flightFile.ignore();
            flightList[flightCount++] = flight;
        }
        flightFile.close();
    }

    if (passengerFile.is_open()) {
        while (!passengerFile.eof()) {
            Passenger passenger;
            passengerFile >> passenger.flightNumber;
            if (passengerFile.eof()) break;
            passengerFile.ignore();
            getline(passengerFile, passenger.name, ',');
            passengerFile >> passenger.seatNumber;
            passengerFile.ignore();
            passengerList[passengerCount++] = passenger;
        }
        passengerFile.close();
    }
}
