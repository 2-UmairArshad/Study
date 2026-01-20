#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
void showProfitOrLoss(const Flight flightList[], int flightCount) {
    if (flightCount == 0) {
        cout << "No flights available.\n";
        return;
    }

    for (int i = 0; i < flightCount; ++i) {
        double profitOrLoss = flightList[i].revenue - (flightList[i].bookedSeats * flightList[i].ticketPrice);
        cout << "Flight Number: " << flightList[i].flightNumber
             << ", Profit/Loss: $" << fixed << setprecision(2) << profitOrLoss << "\n";
    }
}