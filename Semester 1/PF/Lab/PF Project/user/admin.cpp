#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

// Constants
const int MAX_USERS = 100;
const int MAX_FLIGHTS = 100;
const int ROWS = 10;
const int COLS = 6;
const string USER_FILE = "users.txt";
const string FLIGHT_FILE = "flights.txt";

// Structures
struct Flight {
    string flightID;
    string flightType;
    string ticketType;
    string origin;
    string destination;
    string departureDate;
    string returnDate;
    string departureTime;
    string returnTime;
    int totalSeats;
    int bookedSeats;
    double ticketPrice;
    double revenue;
    char seatingMap[ROWS][COLS];
};

struct User {
    string username;
    string password;
};

// Function prototypes
void adminMenu(Flight** flightList, int& flightCount);
void userMenu(User* users, int& userCount, Flight** flightList, int& flightCount);

// Shared functions
void loadFlights(Flight** flightList, int& flightCount);
void saveFlights(Flight** flightList, int flightCount);
bool validateDate(const string& date);
bool validateTime(const string& time);

// Admin functions
bool loginAdmin();
void addFlight(Flight** flightList, int& flightCount);
void removeFlight(Flight** flightList, int& flightCount);
void displayFlights(Flight** flightList, int flightCount);
void calculateProfitOrLoss(Flight** flightList, int flightCount);
void displayRegisteredUsers(User* users, int userCount);

// User functions
bool loginUser(User* users, int userCount, string& loggedInUser);
void registerUser(User* users, int& userCount);
void loadUsers(User* users, int& userCount);
void saveUsers(User* users, int userCount);
void displayFilteredFlights(Flight** flightList, int flightCount);
void bookFlight(Flight** flightList, int flightCount, const string& username);
void bookSpecificSeat(Flight* flight, const string& username);

// Helper functions
string getValidInput(const string& prompt);
int getValidNumericInput(const string& prompt);
bool validateFlightID(const string& flightID);
bool isFlightIDUnique(Flight** flightList, int flightCount, const string& flightID);

int main() {
    Flight* flightList[MAX_FLIGHTS] = {nullptr};
    User users[MAX_USERS];
    int flightCount = 0, userCount = 0;

    loadFlights(flightList, flightCount);
    loadUsers(users, userCount);

    int choice;
    do {
        cout << "\nMain Menu:\n";
        cout << "1. Admin Login\n";
        cout << "2. User Login\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Clear input buffer

        switch (choice) {
            case 1:
                if (loginAdmin()) {
                    adminMenu(flightList, flightCount);
                } else {
                    cout << "Invalid admin login." << endl;
                }
                break;
            case 2: {
                string loggedInUser;
                if (loginUser(users, userCount, loggedInUser)) {
                    userMenu(users, userCount, flightList, flightCount);
                } else {
                    cout << "Invalid user login." << endl;
                }
                break;
            }
            case 3:
                cout << "Exiting program. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 3);

    // Clean up dynamically allocated memory
    for (int i = 0; i < flightCount; ++i) {
        delete flightList[i];
    }

    return 0;
}

// Admin functions
bool loginAdmin() {
    const string adminUsername = "admin", adminPassword = "1234";
    string username, password;

    cout << "Enter Admin Username: ";
    cin >> username;
    cout << "Enter Admin Password: ";
    cin >> password;

    return username == adminUsername && password == adminPassword;
}

void addFlight(Flight** flightList, int& flightCount) {
    if (flightCount >= MAX_FLIGHTS) {
        cout << "Cannot add more flights. List is full.\n";
        return;
    }

    Flight* newFlight = new Flight;
    do {
        newFlight->flightID = getValidInput("Enter Flight ID (Format: flightnumber-city): ");
        if (!validateFlightID(newFlight->flightID)) {
            cout << "Invalid Flight ID format. Example: 123-London (City part must not contain digits).\n";
        } else if (!isFlightIDUnique(flightList, flightCount, newFlight->flightID)) {
            cout << "Flight ID already exists. Please enter a unique Flight ID.\n";
        }
    } while (!validateFlightID(newFlight->flightID) || !isFlightIDUnique(flightList, flightCount, newFlight->flightID));

    newFlight->flightType = getValidInput("Enter Flight Type (Domestic/International): ");
    newFlight->ticketType = getValidInput("Enter Ticket Type (One-Way/Two-Way): ");
    newFlight->origin = getValidInput("Enter Origin: ");
    newFlight->destination = getValidInput("Enter Destination: ");

    do {
        newFlight->departureDate = getValidInput("Enter Departure Date (YYYY-MM-DD): ");
        if (!validateDate(newFlight->departureDate)) {
            cout << "Invalid date format. Please use YYYY-MM-DD.\n";
        }
    } while (!validateDate(newFlight->departureDate));

    if (newFlight->ticketType == "Two-Way") {
        do {
            newFlight->returnDate = getValidInput("Enter Return Date (YYYY-MM-DD): ");
            if (!validateDate(newFlight->returnDate)) {
                cout << "Invalid date format. Please use YYYY-MM-DD.\n";
            }
        } while (!validateDate(newFlight->returnDate));
    } else {
        newFlight->returnDate = "N/A";
    }

    do {
        newFlight->departureTime = getValidInput("Enter Departure Time (HH:MM): ");
        if (!validateTime(newFlight->departureTime)) {
            cout << "Invalid time format. Please use HH:MM (24-hour format).\n";
        }
    } while (!validateTime(newFlight->departureTime));

    if (newFlight->ticketType == "Two-Way") {
        do {
            newFlight->returnTime = getValidInput("Enter Return Time (HH:MM): ");
            if (!validateTime(newFlight->returnTime)) {
                cout << "Invalid time format. Please use HH:MM (24-hour format).\n";
            }
        } while (!validateTime(newFlight->returnTime));
    } else {
        newFlight->returnTime = "N/A";
    }

    newFlight->totalSeats = getValidNumericInput("Enter Total Seats: ");
    newFlight->ticketPrice = getValidNumericInput("Enter Ticket Price: ");
    newFlight->bookedSeats = 0;
    newFlight->revenue = 0.0;

    // Initialize seating map
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            newFlight->seatingMap[i][j] = 'A';
        }
    }

    flightList[flightCount++] = newFlight;
    saveFlights(flightList, flightCount);
    cout << "Flight added successfully and data saved!\n";
}

void removeFlight(Flight** flightList, int& flightCount) {
    if (flightCount == 0) {
        cout << "No flights available to remove.\n";
        return;
    }

    string flightID = getValidInput("Enter the Flight ID to remove: ");
    int index = -1;
    for (int i = 0; i < flightCount; i++) {
        if (flightList[i]->flightID == flightID) {
            index = i;
            break;
        }
    }

    if (index != -1) {
        delete flightList[index];
        for (int i = index; i < flightCount - 1; i++) {
            flightList[i] = flightList[i + 1];
        }
        flightList[--flightCount] = nullptr;
        saveFlights(flightList, flightCount);
        cout << "Flight removed successfully and data saved!\n";
    } else {
        cout << "Flight ID not found.\n";
    }
}

void displayFlights(Flight** flightList, int flightCount) {
    cout << left << setw(10) << "Flight ID" << setw(15) << "Type" << setw(15) << "Ticket"
         << setw(15) << "Origin" << setw(15) << "Destination" << setw(15) << "Dep Date"
         << setw(15) << "Ret Date" << setw(10) << "Seats" << setw(10) << "Booked"
         << setw(10) << "Price" << setw(10) << "Revenue" << endl;

    for (int i = 0; i < flightCount; i++) {
        cout << left << setw(10) << flightList[i]->flightID
             << setw(15) << flightList[i]->flightType
             << setw(15) << flightList[i]->ticketType
             << setw(15) << flightList[i]->origin
             << setw(15) << flightList[i]->destination
             << setw(15) << flightList[i]->departureDate
             << setw(15) << flightList[i]->returnDate
             << setw(10) << flightList[i]->totalSeats
             << setw(10) << flightList[i]->bookedSeats
             << setw(10) << fixed << setprecision(2) << flightList[i]->ticketPrice
             << setw(10) << fixed << setprecision(2) << flightList[i]->revenue << endl;
    }
}

void calculateProfitOrLoss(Flight** flightList, int flightCount) {
    double expectedRevenue;
    cout << "Enter the expected revenue for the month: $";
    cin >> expectedRevenue;

    double totalActualRevenue = 0.0;
    for (int i = 0; i < flightCount; i++) {
        totalActualRevenue += flightList[i]->revenue;
    }

    cout << fixed << setprecision(2);
    cout << "Actual Revenue: $" << totalActualRevenue << endl;

    if (totalActualRevenue > expectedRevenue) {
        cout << "Profit: $" << (totalActualRevenue - expectedRevenue) << endl;
    } else if (totalActualRevenue < expectedRevenue) {
        cout << "Loss: $" << (expectedRevenue - totalActualRevenue) << endl;
    } else {
        cout << "Break-even with no profit or loss.\n";
    }
}