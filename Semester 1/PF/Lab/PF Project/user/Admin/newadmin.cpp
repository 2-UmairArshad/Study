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
void userMenu(User* users, int& userCount, Flight* flights, int& flightCount);

// Shared functions
void loadFlights(Flight** flightList, int& flightCount);
void saveFlights(Flight** flightList, int flightCount);
void loadUsers(User* users, int& userCount);
void saveUsers(User* users, int userCount);
bool validateDate(const string& date);
bool validateTime(const string& time);
string getValidInput(const string& prompt);
int getValidNumericInput(const string& prompt);

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
void displayFilteredFlights(Flight** flightList, int flightCount);
void bookFlight(Flight** flightList, int flightCount, const string& username);
void displaySeatingMap(const Flight& flight);
void bookSpecificSeat(Flight* flight, const string& username);

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

        switch (choice) {
            case 1:
                if (loginAdmin()) {
                    adminMenu(flightList, flightCount);
                } else {
                    cout << "Invalid admin login." << endl;
                }
                break;
            case 2:
                userMenu(users, userCount, reinterpret_cast<Flight*>(flightList), flightCount);
                break;
            case 3:
                cout << "Exiting program. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 3);

    return 0;
}

// Shared functions implementation
void loadFlights(Flight** flightList, int& flightCount) {
    ifstream flightFile(FLIGHT_FILE);
    if (!flightFile) {
        cout << "No flights data found. Starting fresh." << endl;
        return;
    }

    flightCount = 0;
    while (flightCount < MAX_FLIGHTS && !flightFile.eof()) {
        Flight* flight = new Flight;
        flightFile >> flight->flightID >> flight->flightType >> flight->ticketType
                   >> flight->origin >> flight->destination >> flight->departureDate
                   >> flight->returnDate >> flight->departureTime >> flight->returnTime
                   >> flight->totalSeats >> flight->bookedSeats >> flight->ticketPrice
                   >> flight->revenue;

        for (int r = 0; r < ROWS; r++) {
            for (int c = 0; c < COLS; c++) {
                flight->seatingMap[r][c] = 'A';
            }
        }

        flightList[flightCount++] = flight;
    }

    flightFile.close();
    cout << "Flight data loaded successfully." << endl;
}

void saveFlights(Flight** flightList, int flightCount) {
    ofstream flightFile(FLIGHT_FILE);
    if (!flightFile) {
        cout << "Error saving flight data." << endl;
        return;
    }

    for (int i = 0; i < flightCount; i++) {
        flightFile << flightList[i]->flightID << " " << flightList[i]->flightType << " "
                   << flightList[i]->ticketType << " " << flightList[i]->origin << " "
                   << flightList[i]->destination << " " << flightList[i]->departureDate << " "
                   << flightList[i]->returnDate << " " << flightList[i]->departureTime << " "
                   << flightList[i]->returnTime << " " << flightList[i]->totalSeats << " "
                   << flightList[i]->bookedSeats << " " << flightList[i]->ticketPrice << " "
                   << flightList[i]->revenue << endl;
    }

    flightFile.close();
    cout << "Flight data saved successfully." << endl;
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

bool validateDate(const string& date) {
    if (date.length() != 10 || date[4] != '-' || date[7] != '-') {
        return false;
    }

    string year = date.substr(0, 4);
    string month = date.substr(5, 2);
    string day = date.substr(8, 2);

    for (char c : year + month + day) {
        if (!isdigit(c)) {
            return false;
        }
    }

    int y = stoi(year), m = stoi(month), d = stoi(day);
    if (m < 1 || m > 12 || d < 1 || d > 31) {
        return false;
    }

    return true;
}

bool validateTime(const string& time) {
    if (time.length() != 5 || time[2] != ':') {
        return false;
    }

    string hourPart = time.substr(0, 2);
    string minutePart = time.substr(3, 2);

    for (char c : hourPart + minutePart) {
        if (!isdigit(c)) return false;
    }

    int hours = stoi(hourPart);
    int minutes = stoi(minutePart);

    return hours >= 0 && hours <= 23 && minutes >= 0 && minutes <= 59;
}

string getValidInput(const string& prompt) {
    string input;
    cout << prompt;
    cin.ignore();
    getline(cin, input);
    return input;
}

int getValidNumericInput(const string& prompt) {
    int value;
    cout << prompt;
    while (!(cin >> value) || value < 0) {
        cout << "Invalid input. Enter a positive number: ";
        cin.clear();
        cin.ignore();
    }
    return value;
}
