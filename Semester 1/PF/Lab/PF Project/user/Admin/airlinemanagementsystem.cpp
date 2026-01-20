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
void loadFlights(Flight* flights, int& flightCount);
void saveFlights(Flight* flights, int flightCount);
void displaySeatingMap(const Flight* flights, int flightCount);
bool validateDate(const string& date);
bool validateTime(const string& time);

// Admin functions
bool loginAdmin();
void addFlight(Flight** flightList, int& flightCount, int maxFlights);
void removeFlight(Flight** flightList, int& flightCount);
void displayFlights(const Flight* flights, int flightCount);
void calculateProfitOrLoss(const Flight* flights, int flightCount);
void displayRegisteredUsers();

// User functions
bool loginUser(User* users, int userCount, string& loggedInUser);
void registerUser(User* users, int& userCount);
void loadUsers(User* users, int& userCount);
void saveUsers(User* users, int userCount);
void displayFilteredFlights(const Flight* flights, int flightCount);
void bookFlight(Flight* flights, int flightCount, const string& username);
void bookSpecificSeat(Flight* flight, const string& username);

int main() {
    Flight* flightList[MAX_FLIGHTS] = {nullptr};
    User users[MAX_USERS];
    int flightCount = 0, userCount = 0;

    loadFlights(reinterpret_cast<Flight*>(flightList), flightCount);
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
bool loginAdmin() {
    const string adminUsername = "admin", adminPassword = "1234";
    string username, password;

    username = getValidInput("Enter Admin Username: ");
    password = getValidInput("Enter Admin Password: ");

    if (username == adminUsername && password == adminPassword) {
        cout << "Login successful!\n";
        return true;
    }
    return false;
}

void addFlight(Flight** flightList, int& flightCount, int maxFlights) {
    if (flightCount >= maxFlights) {
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

    flightList[flightCount++] = newFlight;
    saveData(flightList, flightCount);
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

    if (index == -1) {
        cout << "Flight ID not found.\n";
        return;
    }

    delete flightList[index];
    for (int i = index; i < flightCount - 1; i++) {
        flightList[i] = flightList[i + 1];
    }
    flightList[--flightCount] = nullptr;
    saveData(flightList, flightCount);
    cout << "Flight removed successfully and data saved!\n";
}

void displayFlights(Flight* flightList[], int flightCount) {
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


void calculateProfitOrLoss(Flight* flightList[], int flightCount) {
    double expectedRevenue = getValidNumericInput("Enter the expected revenue for the month: $");
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

void displayRegisteredUsers() {
    ifstream userFile("users.txt");
    if (!userFile) {
        cout << "No registered users found.\n";
        return;
    }

    cout << left << setw(15) << "Username" << setw(15) << "Password" << endl;
    string username, password;
    while (userFile >> username >> password) {
        cout << left << setw(15) << username << setw(15) << password << endl;
    }
    userFile.close();
}

string getValidInput(const string& prompt) {
    string input;
    do {
        cout << prompt;
        getline(cin, input);
        if (input.empty()) {
            cout << "Input cannot be empty. Please try again.\n";
        }
    } while (input.empty());
    return input;
}

int getValidNumericInput(const string& prompt) {
    string input;
    int value = 0;
    bool valid = false;

    do {
        cout << prompt;
        getline(cin, input);

        valid = true;
        for (char c : input) {
            if (!isdigit(c)) {
                valid = false;
                break;
            }
        }

        if (valid) {
            value = 0;
            for (char c : input) value = value * 10 + (c - '0');
        } else {
            cout << "Invalid input. Please enter a numeric value.\n";
        }

    } while (!valid);

    return value;
}



bool validateFlightID(const string& flightID) {
    int hyphenPos = -1;

    for (int i = 0; i < flightID.length(); i++) {
        if (flightID[i] == '-') {
            hyphenPos = i;
            break;
        }
    }

    if (hyphenPos == -1 || hyphenPos == 0 || hyphenPos == flightID.length() - 1) {
        return false;
    }

    string flightNumber = flightID.substr(0, hyphenPos);
    string city = flightID.substr(hyphenPos + 1);

    for (char c : flightNumber) {
        if (!isdigit(c)) {
            return false;
        }
    }

    for (char c : city) {
        if (isdigit(c)) {
            return false; 
        }
    }

    return true;
}

// Check if Flight ID is Unique
bool isFlightIDUnique(Flight* flightList[], int flightCount, const string& flightID) {
    for (int i = 0; i < flightCount; i++) {
        if (flightList[i]->flightID == flightID) {
            return false;
        }
    }
    return true;
}
//Combined functions
bool validateTime(const string& time) {
    if (time.length() != 5 || time[2] != ':') {
        return false;
    }

    string hourPart = time.substr(0, 2);
    string minutePart = time.substr(3, 2);

    for (char c : hourPart) {
        if (!isdigit(c)) return false;
    }
    for (char c : minutePart) {
        if (!isdigit(c)) return false;
    }

    int hours = 0, minutes = 0;

    for (char c : hourPart) hours = hours * 10 + (c - '0');
    for (char c : minutePart) minutes = minutes * 10 + (c - '0');

    return hours >= 0 && hours <= 23 && minutes >= 0 && minutes <= 59;
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
void displaySeatingMap(const Flight& flight) {
    cout << "Seating Map for Flight ID: " << flight.flightID << endl;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < SEATS_PER_ROW; j++) {
            int seatNumber = i * SEATS_PER_ROW + j + 1;
            if (seatNumber <= flight.bookedSeats) {
                cout << "* ";
            } else {
                cout << "# ";
            }
        }
        cout << endl;
    }
}
void loadData(Flight** flightList, int& flightCount) {
    ifstream flightFile("flights.txt");
    if (!flightFile) {
        cout << "No data file found. Starting fresh.\n";
        flightCount = 0;
        return;
    }

    string headerLine;
    getline(flightFile, headerLine);

    flightCount = 0;
    while (flightCount < MAX_FLIGHTS) {
        Flight* flight = new Flight;

        flightFile >> flight->flightID >> flight->flightType >> flight->ticketType
                   >> flight->origin >> flight->destination >> flight->departureDate
                   >> flight->returnDate >> flight->departureTime >> flight->returnTime
                   >> flight->totalSeats >> flight->bookedSeats >> flight->ticketPrice
                   >> flight->revenue;

        if (flightFile.eof()) {
            delete flight;
            break;
        }

        if (flightFile.fail()) {
            cout << "Error: Malformed line in flight data. Skipping...\n";
            flightFile.clear();
            flightFile.ignore();
            delete flight;
            continue;
        }

        flightList[flightCount++] = flight;
    }

    flightFile.close();
    cout << "Data loaded successfully. Total flights: " << flightCount << endl;
}
void saveData(Flight* flightList[], int flightCount) {
    ofstream flightFile("flights.txt");
    flightFile << left << setw(10) << "Flight ID" << setw(15) << "Type" << setw(15) << "Ticket"
               << setw(15) << "Origin" << setw(15) << "Destination" << setw(15) << "Dep Date"
               << setw(15) << "Ret Date" << setw(10) << "Seats" << setw(10) << "Booked"
               << setw(10) << "Price" << setw(10) << "Revenue" << endl;

    for (int i = 0; i < flightCount; i++) {
        flightFile << left << setw(10) << flightList[i]->flightID
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
    flightFile.close();
    cout << "Data saved successfully!\n";
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
