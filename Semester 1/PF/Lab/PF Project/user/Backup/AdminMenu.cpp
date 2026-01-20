#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
void adminMenu() {
    loadData(flightList, flightCount, passengerList, passengerCount);
    int choice;
        cout << "\nAdmin Menu:\n";
        cout << "1. Add Flight\n";
        cout << "2. Display Flights\n";
        cout << "3. Add Passenger\n";
        cout << "4. Remove Passenger\n";
        cout << "5. Display Passengers\n";
        cout << "6. Set Revenue for a Flight\n";
        cout << "7. Show Profit or Loss\n";
        cout << "8. Show Seat Map\n";
        cout << "9. Save and Exit\n";
        cout << "Enter your choice: ";
}
