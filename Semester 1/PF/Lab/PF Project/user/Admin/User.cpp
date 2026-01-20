#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

const int MAX_USERS = 100;
const int MAX_FLIGHTS = 100;
const int ROWS = 10; // Rows should align with admin module
const int COLS = 6; // Columns should align with admin module
const string USER_FILE = "users.txt";
const string FLIGHT_FILE = "flights.txt";

struct Flight {
    string flightID;
    string flightType;
    string ticketType;
    string origin;
    string destination;
    string departureTime;
    string returnTime;
    int totalSeats;
    int bookedSeats;
    double ticketPrice;
    char seatingMap[ROWS][COLS];
};

struct User {
    string username;
    string password;
};

// Function prototypes
bool loginUser(User* users, int userCount, string& loggedInUser);
void registerUser(User* users, int& userCount);
void loadUsers(User* users, int& userCount);
void saveUsers(User* users, int userCount);
void loadFlights(Flight* flights, int& flightCount);
void saveFlights(Flight* flights, int flightCount);
void displayFilteredFlights(const Flight* flights, int flightCount);
void bookFlight(Flight* flights, int flightCount, const string& username);
void userAuthentication(User* users, int& userCount, string& loggedInUser, bool& isLoggedIn);
void displaySeatingMap(const Flight* flights, int flightCount);
void bookSpecificSeat(Flight* flight, const string& username);

int main() {
    User* users = new User[MAX_USERS];
    Flight* flights = new Flight[MAX_FLIGHTS];
    int userCount = 0, flightCount = 0;
    string loggedInUser;
    bool isLoggedIn = false;

    loadUsers(users, userCount);
    loadFlights(flights, flightCount);

    userAuthentication(users, userCount, loggedInUser, isLoggedIn);

    int choice;
    do {
        cout << "\nUser Menu:\n";
        cout << "1. View Flights by Cities\n2. Book a Flight\n3. View Seating Map\n4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                displayFilteredFlights(flights, flightCount);
                break;
            case 2:
                bookFlight(flights, flightCount, loggedInUser);
                break;
            case 3:
                displaySeatingMap(flights, flightCount);
                break;
            case 4:
                cout << "Exiting program. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 4);

    delete[] users;
    delete[] flights;

    return 0;
}

void loadUsers(User* users, int& userCount) {
    ifstream userFile(USER_FILE);
    if (!userFile) {
        cout << "No user data found. Starting fresh." << endl;
        return;
    }

    while (userFile >> users[userCount].username >> users[userCount].password) {
        userCount++;
        if (userCount >= MAX_USERS) break;
    }

    userFile.close();
    cout << "User data loaded successfully." << endl;
}

void saveUsers(User* users, int userCount) {
    ofstream userFile(USER_FILE);
    if (!userFile) {
        cout << "Error saving user data." << endl;
        return;
    }

    for (int i = 0; i < userCount; i++) {
        userFile << users[i].username << " " << users[i].password << endl;
    }

    userFile.close();
    cout << "User data saved successfully." << endl;
}

void loadFlights(Flight* flights, int& flightCount) {
    ifstream flightFile(FLIGHT_FILE);
    if (!flightFile) {
        cout << "No flights data found. Please contact admin." << endl;
        return;
    }

    string headerLine;
    getline(flightFile, headerLine); // Skip the header line

    while (flightFile >> flights[flightCount].flightID >> flights[flightCount].flightType >> flights[flightCount].ticketType >> flights[flightCount].origin >> flights[flightCount].destination >> flights[flightCount].departureTime >> flights[flightCount].returnTime >> flights[flightCount].totalSeats >> flights[flightCount].bookedSeats >> flights[flightCount].ticketPrice) {
        for (int r = 0; r < ROWS; r++) {
            for (int c = 0; c < COLS; c++) {
                flights[flightCount].seatingMap[r][c] = 'A';
            }
        }
        flightCount++;
        if (flightCount >= MAX_FLIGHTS) break;
    }

    flightFile.close();
    cout << "Flight data loaded successfully." << endl;
}

void saveFlights(Flight* flights, int flightCount) {
    ofstream flightFile(FLIGHT_FILE);
    if (!flightFile) {
        cout << "Error saving flight data." << endl;
        return;
    }

    for (int i = 0; i < flightCount; i++) {
        flightFile << flights[i].flightID << " " << flights[i].flightType << " " << flights[i].ticketType << " " << flights[i].origin << " " << flights[i].destination << " " << flights[i].departureTime << " " << flights[i].returnTime << " " << flights[i].totalSeats << " " << flights[i].bookedSeats << " " << flights[i].ticketPrice << endl;
    }

    flightFile.close();
    cout << "Flight data saved successfully." << endl;
}

void displayFilteredFlights(const Flight* flights, int flightCount) {
    string departure, destination;
    cout << "Enter departure city: ";
    cin >> departure;
    cout << "Enter destination city: ";
    cin >> destination;

    bool found = false;
    for (int i = 0; i < flightCount; i++) {
        if (flights[i].origin == departure && flights[i].destination == destination) {
            found = true;
            cout << left << setw(10) << flights[i].flightID << setw(15) << flights[i].origin << setw(15) << flights[i].destination << setw(10) << flights[i].departureTime << setw(10) << flights[i].ticketPrice << endl;
        }
    }

    if (!found) {
        cout << "No flights found for the specified route." << endl;
    }
}

void bookFlight(Flight* flights, int flightCount, const string& username) {
    string flightID;
    cout << "Enter Flight ID to book: ";
    cin >> flightID;

    for (int i = 0; i < flightCount; i++) {
        if (flights[i].flightID == flightID) {
            if (flights[i].bookedSeats >= flights[i].totalSeats) {
                cout << "Sorry, this flight is fully booked." << endl;
                return;
            }

            bookSpecificSeat(&flights[i], username);
            saveFlights(flights, flightCount);
            return;
        }
    }

    cout << "Flight ID not found." << endl;
}

void displaySeatingMap(const Flight* flights, int flightCount) {
    string flightID;
    cout << "Enter Flight ID to view seating map: ";
    cin >> flightID;

    for (int i = 0; i < flightCount; i++) {
        if (flights[i].flightID == flightID) {
            cout << "Seating Map for Flight " << flightID << ":\n";
            cout << "  A B C D E F\n";
            for (int r = 0; r < ROWS; r++) {
                cout << r + 1 << " ";
                for (int c = 0; c < COLS; c++) {
                    if (flights[i].seatingMap[r][c] == 'A') {
                        cout << "# ";
                    } else {
                        cout << "* ";
                    }
                }
                cout << endl;
            }
            return;
        }
    }

    cout << "Flight ID not found." << endl;
}

void bookSpecificSeat(Flight* flight, const string& username) {
    string seat;
    cout << "Enter seat (e.g., 1A): ";
    cin >> seat;

    int row = seat[0] - '1'; // Convert row (1-indexed) to 0-indexed
    int col = seat[1] - 'A'; // Convert column ('A'-'F') to 0-indexed

    if (row >= 0 && row < ROWS && col >= 0 && col < COLS && flight->seatingMap[row][col] == 'A') {
        flight->seatingMap[row][col] = 'B'; // Mark as booked
        flight->bookedSeats++;
        cout << "Seat " << seat << " booked successfully!" << endl;
    } else {
        cout << "Invalid or already booked seat. Try again." << endl;
    }
}
