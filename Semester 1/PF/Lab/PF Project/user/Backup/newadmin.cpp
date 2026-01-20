#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

// Struct to store flight details
struct Flight {
    int flightNumber;
    string origin;
    string destination;
    string departureTime;
    int totalSeats;
    int bookedSeats;
    double ticketPrice;
    double revenue;
};

// Struct to store passenger details
struct Passenger {
    int flightNumber;
    string name;
    int seatNumber;
};
const int maxFlights = 100;
const int maxPassengers = 1000;
Flight flightList[maxFlights];
Passenger passengerList[maxPassengers];
int flightCount = 0;
int passengerCount = 0;

// Function declarations
void adminMenu();
bool loginAdmin();
void addFlight(Flight flightList[], int& flightCount, int maxFlights);
void displayFlights(const Flight flightList[], int flightCount);
void addPassenger(Passenger passengerList[], int& passengerCount, int maxPassengers, const Flight flightList[], int flightCount);
void removePassenger(Passenger passengerList[], int& passengerCount);
void displayPassengers(const Passenger passengerList[], int passengerCount);
void setRevenue(Flight flightList[], int flightCount);
void showProfitOrLoss(const Flight flightList[], int flightCount);
void saveData(const Flight flightList[], int flightCount, const Passenger passengerList[], int passengerCount);
void loadData(Flight flightList[], int& flightCount, Passenger passengerList[], int& passengerCount);
void showSeatMap(const Flight flightList[], int flightCount);

int main() 
{
    int choice;
    if (loginAdmin()) 
    {
        adminMenu();
       do
        { 
            cin >> choice;
            switch (choice)
            {
            case 1:
                addFlight(flightList, flightCount, maxFlights);
                break;
            case 2:
                displayFlights(flightList, flightCount);
                break;
            case 3:
                addPassenger(passengerList, passengerCount, maxPassengers, flightList, flightCount);
                break;
            case 4:
                removePassenger(passengerList, passengerCount);
                break;
            case 5:
                displayPassengers(passengerList, passengerCount);
                break;
            case 6:
                setRevenue(flightList, flightCount);
                break;
            case 7:
                showProfitOrLoss(flightList, flightCount);
                break;
            case 8:
                showSeatMap(flightList, flightCount);
                break;
            case 9:
                saveData(flightList, flightCount, passengerList, passengerCount);
                cout << "Data saved. Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
            } while (choice != 9);
    }
    else 
    {
        cout << "Invalid login. Exiting...\n";
    }
    return 0;
    }
}