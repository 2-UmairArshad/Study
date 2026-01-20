#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

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
};

const int MAX_FLIGHTS = 100;
const int ROWS = 10;
const int SEATS_PER_ROW = 6;

bool loginAdmin();
void addFlight(Flight** flightList, int& flightCount, int maxFlights);
void removeFlight(Flight** flightList, int& flightCount);
void displayFlights(Flight* flightList[], int flightCount);
bool validateFlightID(const string& flightID);
bool isFlightIDUnique(Flight* flightList[], int flightCount, const string& flightID);
void saveData(Flight* flightList[], int flightCount);
void loadData(Flight** flightList, int& flightCount);
void calculateProfitOrLoss(Flight* flightList[], int flightCount);
void displaySeatingMap(const Flight& flight);
void displayRegisteredUsers();
bool validateTime(const string& time);
string getValidInput(const string& prompt);
int getValidNumericInput(const string& prompt);
bool validateDate(const string& date);

int main() {
    if (!loginAdmin()) {
        cout << "Invalid login. Exiting...\n";
        return 0;
    }

    Flight* flightList[MAX_FLIGHTS] = {nullptr};
    int flightCount = 0;

    loadData(flightList, flightCount);

    int choice;
    do {
        cout << "\nAdmin Menu:\n";
        cout << "1. Add or Remove Flight\n";
        cout << "2. Display Flights\n";
        cout << "3. Display Seating Map\n";
        cout << "4. Display Registered Users\n";
        cout << "5. Calculate Profit or Loss\n";
        cout << "6. Exit\n";
        choice = getValidNumericInput("Enter your choice: ");

        switch (choice) {
            case 1:
                addFlight(flightList, flightCount, MAX_FLIGHTS);
                break;
            case 2:
                displayFlights(flightList, flightCount);
                break;
            case 3: {
                string flightID = getValidInput("Enter Flight ID to view seating map: ");
                bool found = false;
                for (int i = 0; i < flightCount; i++) {
                    if (flightList[i]->flightID == flightID) {
                        displaySeatingMap(*flightList[i]);
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    cout << "Flight ID not found.\n";
                }
                break;
            }
            case 4:
                displayRegisteredUsers();
                break;
            case 5:
                calculateProfitOrLoss(flightList, flightCount);
                break;
            case 6:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 6);

    for (int i = 0; i < flightCount; i++) {
        delete flightList[i];
    }

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