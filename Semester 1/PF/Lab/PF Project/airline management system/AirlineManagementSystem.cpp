#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;

const int MAX_USERS = 100;
const int MAX_FLIGHTS = 100;
const int MAX_SEATS = 50;

struct User {
    string username;
    string password;
    string* history;
    int historyCount;
};

struct Flight {
    string flightID;
    string departureCity;
    string destinationCity; 
    string departureTime;
    string returnTime;
    double seatFee;
    string* seats;
    double revenue;
    bool isRoundTrip;  
};

User** users = new User*[MAX_USERS];
int userCount = 0;

Flight** flights = new Flight*[MAX_FLIGHTS];
int flightCount = 0;

// File paths
const string usersFile = "users.txt";
const string flightsFile = "flights.txt";

// Function prototypes
void adminModule();
void userModule();
void adminLogin();
void userLogin();
void userRegister();
void addRemoveFlight();
void viewSeatingMap();
void viewFlights();
void viewRevenue();
void seeRegisteredUsers();
void bookFlight(int userIndex);
void viewUserHistory(int userIndex);
void loadFiles();
void saveFiles();
bool isNumeric(const string& str);
bool isAlpha(const string& str);
void displaySeatingMap(int flightIndex);
void updateSeatingMap(int flightIndex, int seatNumber);
bool isEmptyInput(const string& input);
void displayTableHeader();
void displayFlightTable();

int main() {
    loadFiles();

    int choice;

    cout << "Welcome to the Airline Management System!" << endl;
    cout << "1. Login as Admin" << endl;
    cout << "2. Login as User" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
        case 1:
            adminLogin();
            break;
        case 2:
            userModule();
            break;
        default:
            cout << "Invalid choice. Exiting..." << endl;
            return 0;
    }

    saveFiles();
    return 0;
}

void adminLogin() {
    string username, password;

    cout << "\n--- Admin Login ---\n";
    cout << "Enter Username: ";
    cin >> username;
    cout << "Enter Password: ";
    cin >> password;

    if (username == "admin" && password == "1234") {
        cout << "Login successful!\n";
        adminModule();
    } else {
        cout << "Invalid credentials.\n";
    }
}

void adminModule() {
    int choice;

    do {
        cout << "\n--- Admin Panel ---\n";
        cout << "1. See Registered Users\n";
        cout << "2. Add or Remove Flights\n";
        cout << "3. See Seating Map\n";
        cout << "4. See Flights\n";
        cout << "5. See Revenue of This Month\n";
        cout << "6. Logout\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                seeRegisteredUsers();
                break;
            case 2:
                addRemoveFlight();
                break;
            case 3:
                viewSeatingMap();
                break;
            case 4:
                viewFlights();
                break;
            case 5:
                viewRevenue();
                break;
            case 6:
                cout << "Logging out...\n";
                return;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (true);
}

void addRemoveFlight() {
    string flightID, departureCity, destinationCity, departureTime, returnTime;
    double seatFee;
    int choice;
    bool isRoundTrip;

    cout << "\n--- Add or Remove Flights ---\n";
    cout << "1. Add Flight\n";
    cout << "2. Remove Flight\n";
    cout << "Enter your choice: ";
    cin >> choice;

    if (choice == 1) {
        cout << "Enter Flight ID (e.g., FLIGHTID-CITY): ";
        cin >> flightID;

        for (int i = 0; i < flightCount; i++) {
            if (flights[i]->flightID == flightID) {
                cout << "Flight ID already exists.\n";
                return;
            }
        }

        Flight* newFlight = new Flight;
        newFlight->flightID = flightID;

        cout << "Enter Departure City: ";
        cin >> departureCity;
        newFlight->departureCity = departureCity;

        cout << "Enter Destination City: ";
        cin >> destinationCity;
        newFlight->destinationCity = destinationCity;

        cout << "Enter Departure Time: ";
        cin >> departureTime;
        newFlight->departureTime = departureTime;

        cout << "Is this a one-way flight? (1 for Yes, 0 for No): ";
        cin >> isRoundTrip;

        newFlight->isRoundTrip = (isRoundTrip == 0) ? false : true;

        if (newFlight->isRoundTrip) {
            cout << "Enter Return Time: ";
            cin >> returnTime;
            newFlight->returnTime = returnTime;
        }

        cout << "Enter Seat Fee: ";
        cin >> seatFee;
        newFlight->seatFee = seatFee;

        newFlight->seats = new string[MAX_SEATS];
        for (int i = 0; i < MAX_SEATS; i++) {
            newFlight->seats[i] = "#";
        }

        newFlight->revenue = 0.0;

        flights[flightCount++] = newFlight;

        cout << "Flight added successfully!\n";
    } else if (choice == 2) {
        cout << "Enter Flight ID to remove: ";
        cin >> flightID;

        for (int i = 0; i < flightCount; i++) {
            if (flights[i]->flightID == flightID) {
                delete[] flights[i]->seats;
                delete flights[i];

                for (int j = i; j < flightCount - 1; j++) {
                    flights[j] = flights[j + 1];
                }
                flightCount--;
                cout << "Flight removed successfully!\n";
                return;
            }
        }
        cout << "Flight ID does not exist.\n";
    } else {
        cout << "Invalid choice.\n";
    }
}

void userModule() {
    int choice;
    do {
        cout << "\n--- User Panel ---\n";
        cout << "1. Login\n";
        cout << "2. Register\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                userLogin();
                break;
            case 2:
                userRegister();
                break;
            case 3:
                cout << "Exiting...\n";
                return;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (true);
}

void userLogin() {
    string username, password;

    cout << "\n--- User Login ---\n";
    cout << "Enter Username: ";
    cin >> username;
    cout << "Enter Password: ";
    cin >> password;

    for (int i = 0; i < userCount; i++) {
        if (users[i]->username == username && users[i]->password == password) {
            cout << "Login successful!\n";

            int choice;
            do {
                cout << "\n--- User Panel ---\n";
                cout << "1. Book Flights\n";
                cout << "2. History\n";
                cout << "3. Exit\n";
                cout << "Enter your choice: ";
                cin >> choice;

                switch (choice) {
                    case 1:
                        bookFlight(i);
                        break;
                    case 2:
                        viewUserHistory(i);
                        break;
                    case 3:
                        cout << "Logging out...\n";
                        return;
                    default:
                        cout << "Invalid choice. Try again.\n";
                }
            } while (true);
        }
    }
    cout << "Invalid credentials.\n";
}

void userRegister() {
    string username, password;

    cout << "\n--- User Registration ---\n";
    cout << "Enter Username: ";
    cin >> username;

    for (int i = 0; i < userCount; i++) {
        if (users[i]->username == username) {
            cout << "Username already exists.\n";
            return;
        }
    }

    cout << "Enter Password: ";
    cin >> password;

    User* newUser = new User;
    newUser->username = username;
    newUser->password = password;
    newUser->history = new string[MAX_FLIGHTS];
    newUser->historyCount = 0;
    users[userCount++] = newUser;

    cout << "Registration successful!\n";
}

void loadFiles() {
    ifstream userFile(usersFile);
    ifstream flightFile(flightsFile);

    if (userFile.is_open()) {
        userFile >> userCount;
        for (int i = 0; i < userCount; i++) {
            User* newUser = new User;
            userFile >> newUser->username >> newUser->password >> newUser->historyCount;
            newUser->history = new string[MAX_FLIGHTS];
            for (int j = 0; j < newUser->historyCount; j++) {
                userFile >> newUser->history[j];
            }
            users[i] = newUser;
        }
        userFile.close();
    }

    if (flightFile.is_open()) {
        flightFile >> flightCount;
        for (int i = 0; i < flightCount; i++) {
            Flight* newFlight = new Flight;
            flightFile >> newFlight->flightID >> newFlight->departureCity >> newFlight->destinationCity
                       >> newFlight->departureTime >> newFlight->returnTime >> newFlight->seatFee
                       >> newFlight->isRoundTrip >> newFlight->revenue;

            newFlight->seats = new string[MAX_SEATS];
            for (int j = 0; j < MAX_SEATS; j++) {
                flightFile >> newFlight->seats[j];
            }

            flights[i] = newFlight;
        }
        flightFile.close();
    }
}

void saveFiles() {
    ofstream userFile(usersFile);
    ofstream flightFile(flightsFile);

    if (userFile.is_open()) {
        userFile << userCount << endl;
        for (int i = 0; i < userCount; i++) {
            userFile << users[i]->username << " " << users[i]->password << " " << users[i]->historyCount << endl;
            for (int j = 0; j < users[i]->historyCount; j++) {
                userFile << users[i]->history[j] << " ";
            }
            userFile << endl;
        }
        userFile.close();
    }

    if (flightFile.is_open()) {
        flightFile << flightCount << endl;
        for (int i = 0; i < flightCount; i++) {
            flightFile << flights[i]->flightID << " " << flights[i]->departureCity << " " << flights[i]->destinationCity
                       << " " << flights[i]->departureTime << " " << flights[i]->returnTime << " "
                       << flights[i]->seatFee << " " << flights[i]->isRoundTrip << " " << flights[i]->revenue << endl;

            for (int j = 0; j < MAX_SEATS; j++) {
                flightFile << flights[i]->seats[j] << " ";
            }
            flightFile << endl;
        }
        flightFile.close();
    }
}

bool isEmptyInput(const string& input) {
    return input.empty() || input == " ";
}

void displayTableHeader() {
    cout << setw(15) << "Flight ID" << setw(20) << "Departure City" << setw(20) << "Destination City"
         << setw(20) << "Departure Time" << setw(20) << "Return Time" << setw(10) << "Seat Fee"
         << setw(10) << "Available Seats" << endl;
}

void displayFlightTable() {
    for (int i = 0; i < flightCount; i++) {
        cout << setw(15) << flights[i]->flightID
             << setw(20) << flights[i]->departureCity
             << setw(20) << flights[i]->destinationCity
             << setw(20) << flights[i]->departureTime
             << setw(20) << flights[i]->returnTime
             << setw(10) << flights[i]->seatFee
             << setw(10) << MAX_SEATS << endl;
    }
}
bool isNumeric(const string& str) {
    for (char c : str) {
        if (!isdigit(c)) return false;
    }
    return true;
}

bool isAlpha(const string& str) {
    for (char c : str) {
        if (!isalpha(c)) return false;
    }
    return true;
}

void displaySeatingMap(int flightIndex) {
    cout << "\n--- Seating Map for Flight " << flights[flightIndex]->flightID << " ---\n";
    for (int i = 0; i < MAX_SEATS; i++) {
        cout << flights[flightIndex]->seats[i] << " ";
        if ((i + 1) % 10 == 0) cout << endl;
    }
}

void updateSeatingMap(int flightIndex, int seatNumber) {
    if (seatNumber < 0 || seatNumber >= MAX_SEATS) {
        cout << "Invalid seat number.\n";
        return;
    }
    if (flights[flightIndex]->seats[seatNumber] == "#") {
        flights[flightIndex]->seats[seatNumber] = "*";
        cout << "Seat " << seatNumber + 1 << " booked successfully!\n";
    } else {
        cout << "Seat already booked.\n";
    }
}

void viewSeatingMap() {
    for (int i = 0; i < flightCount; i++) {
        displaySeatingMap(i);
    }
}

void viewFlights() {
    cout << "\n--- Available Flights ---\n";
    for (int i = 0; i < flightCount; i++) {
        cout << "Flight ID: " << flights[i]->flightID
             << ", Departure: " << flights[i]->departureCity
             << ", Return: " << flights[i]->destinationCity
             << ", Fee: $" << flights[i]->seatFee << endl;
    }
}

void viewRevenue() {
    double totalRevenue = 0.0;
    cout << "\n--- Flight Revenue ---\n";
    for (int i = 0; i < flightCount; i++) {
        cout << "Flight ID: " << flights[i]->flightID
             << ", Revenue: $" << flights[i]->revenue << endl;
        totalRevenue += flights[i]->revenue;
    }
    cout << "Total Revenue: $" << totalRevenue << endl;
}

void seeRegisteredUsers() {
    cout << "\n--- Registered Users ---\n";
    for (int i = 0; i < userCount; i++) {
        cout << "Username\t" << setw(4) << "Travel History\n"
        << users[i]->username << "\t\t" << setw(4) << users[i]->history[i] << endl;
    }
}

void bookFlight(int userIndex) {
    string flightID;
    int seatNumber;

    cout << "\n--- Book a Flight ---\n";
    cout << "Enter Flight ID: ";
    cin >> flightID;

    int flightIndex = -1;
    for (int i = 0; i < flightCount; i++) {
        if (flights[i]->flightID == flightID) {
            flightIndex = i;
            break;
        }
    }

    if (flightIndex == -1) {
        cout << "Flight not found.\n";
        return;
    }

    displaySeatingMap(flightIndex);
    cout << "Enter Seat Number to Book (1-" << MAX_SEATS << "): ";
    cin >> seatNumber;

    updateSeatingMap(flightIndex, seatNumber - 1);
    flights[flightIndex]->revenue += flights[flightIndex]->seatFee;

    // Update user history
    users[userIndex]->history[users[userIndex]->historyCount++] = flightID;
}

void viewUserHistory(int userIndex) {
    cout << "\n--- Travel History for " << users[userIndex]->username << " ---\n";
    for (int i = 0; i < users[userIndex]->historyCount; i++) {
        cout << users[userIndex]->history[i] << endl;
    }
}