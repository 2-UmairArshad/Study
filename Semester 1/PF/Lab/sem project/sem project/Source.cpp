#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Passenger {
    string userId;
    string password;
    string name;
    string address;
    string phone;
    string status;
    double totalSpent;
};

struct Flight {
    string flightNumber;
    string destination;
    string departureTime;
    string arrivalTime;
    string departureDate;
    string arrivalDate;
    int totalSeats;
    int availableSeats;
    double fareEconomy;
    double fareBusiness;
    string status;
    int timesBooked;
    double totalIncome;
    char** seatMap;
};

struct Booking {
    string bookingId;
    string passengerId;
    string flightNumber;
    string bookingDate;
    string seatNumber;
    string travelClass;
    double fare;
    string status;
};

struct Admin {
    string userId;
    string password;
};

void clearScreen() {
    system("cls");
}

void pauseScreen() {
    cout << "\nPress Enter to continue...";
    string dummy;
    getline(cin, dummy);
}

bool isValidDate(string date) {
    if (date.length() != 10) return false;
    if (date[2] != '-' || date[5] != '-') return false;

    for (int i = 0; i < 10; i++) {
        if (i != 2 && i != 5) {
            if (date[i] < '0' || date[i] > '9') return false;
        }
    }

    int day = (date[0] - '0') * 10 + (date[1] - '0');
    int month = (date[3] - '0') * 10 + (date[4] - '0');
    int year = (date[6] - '0') * 1000 + (date[7] - '0') * 100 + (date[8] - '0') * 10 + (date[9] - '0');

    if (day < 1 || day > 31 || month < 1 || month > 12 || year < 2024) return false;

    return true;
}

bool isValidTime(string time) {
    if (time.length() < 4 || time.length() > 5) return false;

    int colonPos = -1;
    for (int i = 0; i < time.length(); i++) {
        if (time[i] == ':') {
            colonPos = i;
            break;
        }
    }

    if (colonPos == -1) return false;

    for (int i = 0; i < time.length(); i++) {
        if (i != colonPos) {
            if (time[i] < '0' || time[i] > '9') return false;
        }
    }

    int hour = 0, minute = 0;
    for (int i = 0; i < colonPos; i++) {
        hour = hour * 10 + (time[i] - '0');
    }
    for (int i = colonPos + 1; i < time.length(); i++) {
        minute = minute * 10 + (time[i] - '0');
    }

    if (hour < 0 || hour > 23 || minute < 0 || minute > 59) return false;

    return true;
}

bool isValidPhone(string phone) {
    if (phone.length() < 10 || phone.length() > 15) return false;
    for (int i = 0; i < phone.length(); i++) {
        if (phone[i] < '0' || phone[i] > '9') return false;
    }
    return true;
}

void initializeSeatMap(Flight& flight) {
    int rows = (flight.totalSeats + 3) / 4;
    flight.seatMap = new char* [rows];
    for (int i = 0; i < rows; i++) {
        flight.seatMap[i] = new char[4];
        for (int j = 0; j < 4; j++) {
            if (i * 4 + j < flight.totalSeats) {
                flight.seatMap[i][j] = '#';
            }
            else {
                flight.seatMap[i][j] = ' ';
            }
        }
    }
}

void deleteSeatMap(Flight& flight) {
    int rows = (flight.totalSeats + 3) / 4;
    for (int i = 0; i < rows; i++) {
        delete[] flight.seatMap[i];
    }
    delete[] flight.seatMap;
}

void displaySeatMap(Flight flight) {
    int rows = (flight.totalSeats + 3) / 4;
    cout << "\n=== Seat Map for Flight " << flight.flightNumber << " ===\n";
    cout << "# = Available, * = Occupied\n\n";
    cout << "   A B C D\n";
    cout << "  ---------\n";

    for (int i = 0; i < rows; i++) {
        cout << i + 1;
        if (i + 1 < 10) cout << " ";
        cout << "|";
        for (int j = 0; j < 4; j++) {
            if (flight.seatMap[i][j] == ' ') {
                cout << "  ";
            }
            else {
                cout << flight.seatMap[i][j] << " ";
            }
        }
        cout << "|\n";
    }
    cout << "  ---------\n";
}

string getSeatNumber(int row, int col) {
    string seat = "";
    seat += (char)('0' + row);
    seat += (char)('A' + col);
    return seat;
}

void loadAdmins(Admin**& admins, int& adminCount) {
    ifstream file("admins.txt");
    if (!file.is_open()) {
        adminCount = 1;
        admins = new Admin * [adminCount];
        admins[0] = new Admin;
        admins[0]->userId = "admin";
        admins[0]->password = "admin123";
        return;
    }

    file >> adminCount;
    file.ignore();

    admins = new Admin * [adminCount];
    for (int i = 0; i < adminCount; i++) {
        admins[i] = new Admin;
        getline(file, admins[i]->userId);
        getline(file, admins[i]->password);
    }

    file.close();
}

void saveAdmins(Admin** admins, int adminCount) {
    ofstream file("admins.txt");
    file << adminCount << endl;
    for (int i = 0; i < adminCount; i++) {
        file << admins[i]->userId << endl;
        file << admins[i]->password << endl;
    }
    file.close();
}

void loadPassengers(Passenger**& passengers, int& passengerCount) {
    ifstream file("passengers.txt");
    if (!file.is_open()) {
        passengerCount = 0;
        passengers = new Passenger * [100];
        return;
    }

    file >> passengerCount;
    file.ignore();

    passengers = new Passenger * [passengerCount];
    for (int i = 0; i < passengerCount; i++) {
        passengers[i] = new Passenger;
        getline(file, passengers[i]->userId);
        getline(file, passengers[i]->password);
        getline(file, passengers[i]->name);
        getline(file, passengers[i]->address);
        getline(file, passengers[i]->phone);
        getline(file, passengers[i]->status);
        file >> passengers[i]->totalSpent;
        file.ignore();
    }

    file.close();
}

void savePassengers(Passenger** passengers, int passengerCount) {
    ofstream file("passengers.txt");
    file << passengerCount << endl;
    for (int i = 0; i < passengerCount; i++) {
        file << passengers[i]->userId << endl;
        file << passengers[i]->password << endl;
        file << passengers[i]->name << endl;
        file << passengers[i]->address << endl;
        file << passengers[i]->phone << endl;
        file << passengers[i]->status << endl;
        file << passengers[i]->totalSpent << endl;
    }
    file.close();
}

void loadFlights(Flight**& flights, int& flightCount) {
    ifstream file("flights.txt");
    if (!file.is_open()) {
        flightCount = 0;
        flights = new Flight * [100];
        return;
    }

    file >> flightCount;
    file.ignore();

    flights = new Flight * [flightCount];
    for (int i = 0; i < flightCount; i++) {
        flights[i] = new Flight;
        getline(file, flights[i]->flightNumber);
        getline(file, flights[i]->destination);
        getline(file, flights[i]->departureTime);
        getline(file, flights[i]->arrivalTime);
        getline(file, flights[i]->departureDate);
        getline(file, flights[i]->arrivalDate);
        file >> flights[i]->totalSeats;
        file >> flights[i]->availableSeats;
        file >> flights[i]->fareEconomy;
        file >> flights[i]->fareBusiness;
        file.ignore();
        getline(file, flights[i]->status);
        file >> flights[i]->timesBooked;
        file >> flights[i]->totalIncome;
        file.ignore();

        initializeSeatMap(*flights[i]);

        int rows = (flights[i]->totalSeats + 3) / 4;
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < 4; c++) {
                if (r * 4 + c < flights[i]->totalSeats) {
                    file >> flights[i]->seatMap[r][c];
                }
            }
        }
        file.ignore();
    }

    file.close();
}

void saveFlights(Flight** flights, int flightCount) {
    ofstream file("flights.txt");
    file << flightCount << endl;
    for (int i = 0; i < flightCount; i++) {
        file << flights[i]->flightNumber << endl;
        file << flights[i]->destination << endl;
        file << flights[i]->departureTime << endl;
        file << flights[i]->arrivalTime << endl;
        file << flights[i]->departureDate << endl;
        file << flights[i]->arrivalDate << endl;
        file << flights[i]->totalSeats << endl;
        file << flights[i]->availableSeats << endl;
        file << flights[i]->fareEconomy << endl;
        file << flights[i]->fareBusiness << endl;
        file << flights[i]->status << endl;
        file << flights[i]->timesBooked << endl;
        file << flights[i]->totalIncome << endl;

        int rows = (flights[i]->totalSeats + 3) / 4;
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < 4; c++) {
                if (r * 4 + c < flights[i]->totalSeats) {
                    file << flights[i]->seatMap[r][c] << " ";
                }
            }
        }
        file << endl;
    }
    file.close();
}

void loadBookings(Booking**& bookings, int& bookingCount) {
    ifstream file("bookings.txt");
    if (!file.is_open()) {
        bookingCount = 0;
        bookings = new Booking * [1000];
        return;
    }

    file >> bookingCount;
    file.ignore();

    bookings = new Booking * [bookingCount];
    for (int i = 0; i < bookingCount; i++) {
        bookings[i] = new Booking;
        getline(file, bookings[i]->bookingId);
        getline(file, bookings[i]->passengerId);
        getline(file, bookings[i]->flightNumber);
        getline(file, bookings[i]->bookingDate);
        getline(file, bookings[i]->seatNumber);
        getline(file, bookings[i]->travelClass);
        file >> bookings[i]->fare;
        file.ignore();
        getline(file, bookings[i]->status);
    }

    file.close();
}

void saveBookings(Booking** bookings, int bookingCount) {
    ofstream file("bookings.txt");
    file << bookingCount << endl;
    for (int i = 0; i < bookingCount; i++) {
        file << bookings[i]->bookingId << endl;
        file << bookings[i]->passengerId << endl;
        file << bookings[i]->flightNumber << endl;
        file << bookings[i]->bookingDate << endl;
        file << bookings[i]->seatNumber << endl;
        file << bookings[i]->travelClass << endl;
        file << bookings[i]->fare << endl;
        file << bookings[i]->status << endl;
    }
    file.close();
}

void viewAvailableFlights(Flight** flights, int flightCount) {
    clearScreen();
    cout << "\n========== Available Flights ==========\n";

    bool found = false;
    for (int i = 0; i < flightCount; i++) {
        if (flights[i]->availableSeats > 0 && flights[i]->status == "Available") {
            found = true;
            cout << "\nFlight Number: " << flights[i]->flightNumber << endl;
            cout << "Destination: " << flights[i]->destination << endl;
            cout << "Departure: " << flights[i]->departureDate << " at " << flights[i]->departureTime << endl;
            cout << "Arrival: " << flights[i]->arrivalDate << " at " << flights[i]->arrivalTime << endl;
            cout << "Available Seats: " << flights[i]->availableSeats << "/" << flights[i]->totalSeats << endl;
            cout << "Economy Fare: $" << flights[i]->fareEconomy << endl;
            cout << "Business Fare: $" << flights[i]->fareBusiness << endl;
            cout << "---------------------------------------\n";
        }
    }

    if (!found) {
        cout << "\nNo available flights at the moment.\n";
    }
}

void bookFlight(Passenger** passengers, int passengerCount, Flight** flights, int flightCount, Booking**& bookings, int& bookingCount, string currentUserId) {
    clearScreen();
    cout << "\n========== Book a Flight ==========\n";

    viewAvailableFlights(flights, flightCount);

    string flightNumber;
    cout << "\nEnter Flight Number to book: ";
    cin >> flightNumber;

    int flightIndex = -1;
    for (int i = 0; i < flightCount; i++) {
        if (flights[i]->flightNumber == flightNumber) {
            flightIndex = i;
            break;
        }
    }

    if (flightIndex == -1) {
        cout << "\nError: Flight not found!\n";
        pauseScreen();
        return;
    }

    if (flights[flightIndex]->availableSeats <= 0) {
        cout << "\nError: Flight is full!\n";
        pauseScreen();
        return;
    }

    displaySeatMap(*flights[flightIndex]);

    int row, col;
    cout << "\nEnter seat row (1-" << (flights[flightIndex]->totalSeats + 3) / 4 << "): ";
    cin >> row;

    if (row < 1 || row >(flights[flightIndex]->totalSeats + 3) / 4) {
        cout << "\nError: Invalid row number!\n";
        pauseScreen();
        return;
    }

    char colChar;
    cout << "Enter seat column (A-D): ";
    cin >> colChar;

    if (colChar >= 'a' && colChar <= 'd') {
        colChar = colChar - 32;
    }

    if (colChar < 'A' || colChar > 'D') {
        cout << "\nError: Invalid column!\n";
        pauseScreen();
        return;
    }

    col = colChar - 'A';

    if ((row - 1) * 4 + col >= flights[flightIndex]->totalSeats) {
        cout << "\nError: Seat does not exist!\n";
        pauseScreen();
        return;
    }

    if (flights[flightIndex]->seatMap[row - 1][col] == '*') {
        cout << "\nError: Seat already occupied!\n";
        pauseScreen();
        return;
    }

    string travelClass;
    cout << "\nSelect Class:\n";
    cout << "1. Economy ($" << flights[flightIndex]->fareEconomy << ")\n";
    cout << "2. Business ($" << flights[flightIndex]->fareBusiness << ")\n";
    cout << "Enter choice (1-2): ";
    int classChoice;
    cin >> classChoice;

    double fare;
    if (classChoice == 1) {
        travelClass = "Economy";
        fare = flights[flightIndex]->fareEconomy;
    }
    else if (classChoice == 2) {
        travelClass = "Business";
        fare = flights[flightIndex]->fareBusiness;
    }
    else {
        cout << "\nError: Invalid class selection!\n";
        pauseScreen();
        return;
    }

    flights[flightIndex]->seatMap[row - 1][col] = '*';
    flights[flightIndex]->availableSeats--;
    flights[flightIndex]->timesBooked++;
    flights[flightIndex]->totalIncome += fare;

    if (flights[flightIndex]->availableSeats == 0) {
        flights[flightIndex]->status = "Full";
    }

    Booking** newBookings = new Booking * [bookingCount + 1];
    for (int i = 0; i < bookingCount; i++) {
        newBookings[i] = bookings[i];
    }

    newBookings[bookingCount] = new Booking;
    newBookings[bookingCount]->bookingId = "BK" + to_string(bookingCount + 1001);
    newBookings[bookingCount]->passengerId = currentUserId;
    newBookings[bookingCount]->flightNumber = flightNumber;
    newBookings[bookingCount]->bookingDate = "03-01-2026";
    newBookings[bookingCount]->seatNumber = getSeatNumber(row, col);
    newBookings[bookingCount]->travelClass = travelClass;
    newBookings[bookingCount]->fare = fare;
    newBookings[bookingCount]->status = "Booked";

    delete[] bookings;
    bookings = newBookings;
    bookingCount++;

    for (int i = 0; i < passengerCount; i++) {
        if (passengers[i]->userId == currentUserId) {
            passengers[i]->status = "Booked";
            passengers[i]->totalSpent += fare;
            break;
        }
    }

    saveFlights(flights, flightCount);
    saveBookings(bookings, bookingCount);
    savePassengers(passengers, passengerCount);

    clearScreen();
    cout << "\n========== Booking Receipt ==========\n";
    cout << "Booking ID: " << newBookings[bookingCount - 1]->bookingId << endl;
    cout << "Passenger ID: " << currentUserId << endl;
    cout << "Flight Number: " << flightNumber << endl;
    cout << "Destination: " << flights[flightIndex]->destination << endl;
    cout << "Departure: " << flights[flightIndex]->departureDate << " at " << flights[flightIndex]->departureTime << endl;
    cout << "Arrival: " << flights[flightIndex]->arrivalDate << " at " << flights[flightIndex]->arrivalTime << endl;
    cout << "Seat: " << newBookings[bookingCount - 1]->seatNumber << endl;
    cout << "Class: " << travelClass << endl;
    cout << "Fare: $" << fare << endl;
    cout << "Status: Booked\n";
    cout << "=====================================\n";

    pauseScreen();
}

void cancelReservation(Passenger** passengers, int passengerCount, Flight** flights, int flightCount, Booking** bookings, int bookingCount, string currentUserId) {
    clearScreen();
    cout << "\n========== Cancel Reservation ==========\n";

    bool hasBookings = false;
    for (int i = 0; i < bookingCount; i++) {
        if (bookings[i]->passengerId == currentUserId && bookings[i]->status == "Booked") {
            hasBookings = true;
            cout << "\nBooking ID: " << bookings[i]->bookingId << endl;
            cout << "Flight Number: " << bookings[i]->flightNumber << endl;
            cout << "Seat: " << bookings[i]->seatNumber << endl;
            cout << "Class: " << bookings[i]->travelClass << endl;
            cout << "Fare: $" << bookings[i]->fare << endl;
            cout << "---------------------------------------\n";
        }
    }

    if (!hasBookings) {
        cout << "\nYou have no active bookings.\n";
        pauseScreen();
        return;
    }

    string bookingId;
    cout << "\nEnter Booking ID to cancel: ";
    cin >> bookingId;

    int bookingIndex = -1;
    for (int i = 0; i < bookingCount; i++) {
        if (bookings[i]->bookingId == bookingId && bookings[i]->passengerId == currentUserId) {
            bookingIndex = i;
            break;
        }
    }

    if (bookingIndex == -1) {
        cout << "\nError: Booking not found!\n";
        pauseScreen();
        return;
    }

    if (bookings[bookingIndex]->status == "Cancelled") {
        cout << "\nError: Booking already cancelled!\n";
        pauseScreen();
        return;
    }

    double refund = bookings[bookingIndex]->fare * 0.8;

    int flightIndex = -1;
    for (int i = 0; i < flightCount; i++) {
        if (flights[i]->flightNumber == bookings[bookingIndex]->flightNumber) {
            flightIndex = i;
            break;
        }
    }

    if (flightIndex != -1) {
        int row = bookings[bookingIndex]->seatNumber[0] - '0';
        int col = bookings[bookingIndex]->seatNumber[1] - 'A';

        flights[flightIndex]->seatMap[row - 1][col] = '#';
        flights[flightIndex]->availableSeats++;
        flights[flightIndex]->status = "Available";
        flights[flightIndex]->totalIncome -= bookings[bookingIndex]->fare;
        flights[flightIndex]->timesBooked--;
    }

    bookings[bookingIndex]->status = "Cancelled";

    for (int i = 0; i < passengerCount; i++) {
        if (passengers[i]->userId == currentUserId) {
            passengers[i]->totalSpent -= bookings[bookingIndex]->fare;

            bool hasOtherBookings = false;
            for (int j = 0; j < bookingCount; j++) {
                if (bookings[j]->passengerId == currentUserId && bookings[j]->status == "Booked") {
                    hasOtherBookings = true;
                    break;
                }
            }

            if (!hasOtherBookings) {
                passengers[i]->status = "Active";
            }
            break;
        }
    }

    saveFlights(flights, flightCount);
    saveBookings(bookings, bookingCount);
    savePassengers(passengers, passengerCount);

    cout << "\nReservation cancelled successfully!\n";
    cout << "Refund Amount (80%): $" << refund << endl;

    pauseScreen();
}

void generatePassengerReport(Booking** bookings, int bookingCount, string currentUserId) {
    clearScreen();
    cout << "\n========== Your Booking Report ==========\n";

    double totalSpent = 0;
    bool hasBookings = false;

    for (int i = 0; i < bookingCount; i++) {
        if (bookings[i]->passengerId == currentUserId) {
            hasBookings = true;
            cout << "\nBooking ID: " << bookings[i]->bookingId << endl;
            cout << "Flight Number: " << bookings[i]->flightNumber << endl;
            cout << "Booking Date: " << bookings[i]->bookingDate << endl;
            cout << "Seat: " << bookings[i]->seatNumber << endl;
            cout << "Class: " << bookings[i]->travelClass << endl;
            cout << "Fare: $" << bookings[i]->fare << endl;
            cout << "Status: " << bookings[i]->status << endl;
            cout << "---------------------------------------\n";

            if (bookings[i]->status == "Booked") {
                totalSpent += bookings[i]->fare;
            }
        }
    }

    if (!hasBookings) {
        cout << "\nNo booking history found.\n";
    }
    else {
        cout << "\nTotal Money Spent (Active Bookings): $" << totalSpent << endl;
    }

    pauseScreen();
}

void passengerMenu(Passenger** passengers, int passengerCount, Flight** flights, int flightCount, Booking**& bookings, int& bookingCount, string currentUserId) {
    int choice;

    while (true) {
        clearScreen();
        cout << "\n========== Passenger Menu ==========\n";
        cout << "1. View Available Flights\n";
        cout << "2. Book a Flight\n";
        cout << "3. Cancel Reservation\n";
        cout << "4. View My Booking Report\n";
        cout << "5. Logout\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "\nError: Invalid input! Please enter a number.\n";
            pauseScreen();
            continue;
        }

        switch (choice) {
        case 1:
            viewAvailableFlights(flights, flightCount);
            pauseScreen();
            break;
        case 2:
            bookFlight(passengers, passengerCount, flights, flightCount, bookings, bookingCount, currentUserId);
            break;
        case 3:
            cancelReservation(passengers, passengerCount, flights, flightCount, bookings, bookingCount, currentUserId);
            break;
        case 4:
            generatePassengerReport(bookings, bookingCount, currentUserId);
            break;
        case 5:
            return;
        default:
            cout << "\nError: Invalid choice! Please enter a number between 1-5.\n";
            pauseScreen();
        }
    }
}

void addPassenger(Passenger**& passengers, int& passengerCount) {
    clearScreen();
    cout << "\n========== Add New Passenger ==========\n";

    Passenger** newPassengers = new Passenger * [passengerCount + 1];
    for (int i = 0; i < passengerCount; i++) {
        newPassengers[i] = passengers[i];
    }

    newPassengers[passengerCount] = new Passenger;

    cout << "Enter User ID: ";
    cin >> newPassengers[passengerCount]->userId;

    for (int i = 0; i < passengerCount; i++) {
        if (passengers[i]->userId == newPassengers[passengerCount]->userId) {
            cout << "\nError: User ID already exists!\n";
            delete newPassengers[passengerCount];
            delete[] newPassengers;
            pauseScreen();
            return;
        }
    }

    cout << "Enter Password: ";
    cin >> newPassengers[passengerCount]->password;

    cin.ignore();
    cout << "Enter Name: ";
    getline(cin, newPassengers[passengerCount]->name);

    cout << "Enter Address: ";
    getline(cin, newPassengers[passengerCount]->address);

    while (true) {
        cout << "Enter Phone (10-15 digits): ";
        getline(cin, newPassengers[passengerCount]->phone);

        if (isValidPhone(newPassengers[passengerCount]->phone)) {
            break;
        }
        else {
            cout << "Error: Invalid phone number! Must be 10-15 digits.\n";
        }
    }

    newPassengers[passengerCount]->status = "Active";
    newPassengers[passengerCount]->totalSpent = 0.0;

    delete[] passengers;
    passengers = newPassengers;
    passengerCount++;

    savePassengers(passengers, passengerCount);

    cout << "\nPassenger added successfully!\n";
    pauseScreen();
}

void removePassenger(Passenger**& passengers, int& passengerCount) {
    clearScreen();
    cout << "\n========== Remove Passenger ==========\n";

    if (passengerCount == 0) {
        cout << "\nNo passengers in the system.\n";
        pauseScreen();
        return;
    }

    string userId;
    cout << "Enter Passenger User ID to remove: ";
    cin >> userId;

    int passengerIndex = -1;
    for (int i = 0; i < passengerCount; i++) {
        if (passengers[i]->userId == userId) {
            passengerIndex = i;
            break;
        }
    }

    if (passengerIndex == -1) {
        cout << "\nError: Passenger not found!\n";
        pauseScreen();
        return;
    }

    Passenger** newPassengers = new Passenger * [passengerCount - 1];
    int newIndex = 0;

    for (int i = 0; i < passengerCount; i++) {
        if (i != passengerIndex) {
            newPassengers[newIndex] = passengers[i];
            newIndex++;
        }
        else {
            delete passengers[i];
        }
    }

    delete[] passengers;
    passengers = newPassengers;
    passengerCount--;

    savePassengers(passengers, passengerCount);

    cout << "\nPassenger removed successfully!\n";
    pauseScreen();
}

void updatePassengerData(Passenger** passengers, int passengerCount) {
    clearScreen();
    cout << "\n========== Update Passenger Data ==========\n";

    if (passengerCount == 0) {
        cout << "\nNo passengers in the system.\n";
        pauseScreen();
        return;
    }

    string userId;
    cout << "Enter Passenger User ID to update: ";
    cin >> userId;

    int passengerIndex = -1;
    for (int i = 0; i < passengerCount; i++) {
        if (passengers[i]->userId == userId) {
            passengerIndex = i;
            break;
        }
    }

    if (passengerIndex == -1) {
        cout << "\nError: Passenger not found!\n";
        pauseScreen();
        return;
    }

    cin.ignore();

    cout << "\nCurrent Data:\n";
    cout << "Name: " << passengers[passengerIndex]->name << endl;
    cout << "Address: " << passengers[passengerIndex]->address << endl;
    cout << "Phone: " << passengers[passengerIndex]->phone << endl;

    cout << "\nEnter new Name (or press Enter to keep current): ";
    string newName;
    getline(cin, newName);
    if (newName != "") {
        passengers[passengerIndex]->name = newName;
    }

    cout << "Enter new Address (or press Enter to keep current): ";
    string newAddress;
    getline(cin, newAddress);
    if (newAddress != "") {
        passengers[passengerIndex]->address = newAddress;
    }

    cout << "Enter new Phone (or press Enter to keep current): ";
    string newPhone;
    getline(cin, newPhone);
    if (newPhone != "") {
        if (isValidPhone(newPhone)) {
            passengers[passengerIndex]->phone = newPhone;
        }
        else {
            cout << "Error: Invalid phone number! Keeping previous value.\n";
        }
    }

    savePassengers(passengers, passengerCount);

    cout << "\nPassenger data updated successfully!\n";
    pauseScreen();
}

void addFlight(Flight**& flights, int& flightCount) {
    clearScreen();
    cout << "\n========== Add New Flight ==========\n";

    Flight** newFlights = new Flight * [flightCount + 1];
    for (int i = 0; i < flightCount; i++) {
        newFlights[i] = flights[i];
    }

    newFlights[flightCount] = new Flight;

    cout << "Enter Flight Number: ";
    cin >> newFlights[flightCount]->flightNumber;

    for (int i = 0; i < flightCount; i++) {
        if (flights[i]->flightNumber == newFlights[flightCount]->flightNumber) {
            cout << "\nError: Flight number already exists!\n";
            delete newFlights[flightCount];
            delete[] newFlights;
            pauseScreen();
            return;
        }
    }

    cin.ignore();
    cout << "Enter Destination: ";
    getline(cin, newFlights[flightCount]->destination);

    while (true) {
        cout << "Enter Departure Date (DD-MM-YYYY): ";
        getline(cin, newFlights[flightCount]->departureDate);
        if (isValidDate(newFlights[flightCount]->departureDate)) {
            break;
        }
        else {
            cout << "Error: Invalid date format!\n";
        }
    }

    while (true) {
        cout << "Enter Departure Time (HH:MM): ";
        getline(cin, newFlights[flightCount]->departureTime);
        if (isValidTime(newFlights[flightCount]->departureTime)) {
            break;
        }
        else {
            cout << "Error: Invalid time format!\n";
        }
    }

    while (true) {
        cout << "Enter Arrival Date (DD-MM-YYYY): ";
        getline(cin, newFlights[flightCount]->arrivalDate);
        if (isValidDate(newFlights[flightCount]->arrivalDate)) {
            break;
        }
        else {
            cout << "Error: Invalid date format!\n";
        }
    }

    while (true) {
        cout << "Enter Arrival Time (HH:MM): ";
        getline(cin, newFlights[flightCount]->arrivalTime);
        if (isValidTime(newFlights[flightCount]->arrivalTime)) {
            break;
        }
        else {
            cout << "Error: Invalid time format!\n";
        }
    }

    while (true) {
        cout << "Enter Total Seats (multiple of 4, max 40): ";
        cin >> newFlights[flightCount]->totalSeats;

        if (cin.fail() || newFlights[flightCount]->totalSeats <= 0 || newFlights[flightCount]->totalSeats > 40 || newFlights[flightCount]->totalSeats % 4 != 0) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Error: Invalid seats! Must be multiple of 4 and between 4-40.\n";
        }
        else {
            break;
        }
    }

    newFlights[flightCount]->availableSeats = newFlights[flightCount]->totalSeats;

    while (true) {
        cout << "Enter Economy Class Fare: $";
        cin >> newFlights[flightCount]->fareEconomy;

        if (cin.fail() || newFlights[flightCount]->fareEconomy <= 0) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Error: Invalid fare! Must be greater than 0.\n";
        }
        else {
            break;
        }
    }

    while (true) {
        cout << "Enter Business Class Fare: $";
        cin >> newFlights[flightCount]->fareBusiness;

        if (cin.fail() || newFlights[flightCount]->fareBusiness <= 0) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Error: Invalid fare! Must be greater than 0.\n";
        }
        else {
            break;
        }
    }

    newFlights[flightCount]->status = "Available";
    newFlights[flightCount]->timesBooked = 0;
    newFlights[flightCount]->totalIncome = 0.0;

    initializeSeatMap(*newFlights[flightCount]);

    delete[] flights;
    flights = newFlights;
    flightCount++;

    saveFlights(flights, flightCount);

    cout << "\nFlight added successfully!\n";
    pauseScreen();
}

void removeFlight(Flight**& flights, int& flightCount) {
    clearScreen();
    cout << "\n========== Remove Flight ==========\n";

    if (flightCount == 0) {
        cout << "\nNo flights in the system.\n";
        pauseScreen();
        return;
    }

    string flightNumber;
    cout << "Enter Flight Number to remove: ";
    cin >> flightNumber;

    int flightIndex = -1;
    for (int i = 0; i < flightCount; i++) {
        if (flights[i]->flightNumber == flightNumber) {
            flightIndex = i;
            break;
        }
    }

    if (flightIndex == -1) {
        cout << "\nError: Flight not found!\n";
        pauseScreen();
        return;
    }

    Flight** newFlights = new Flight * [flightCount - 1];
    int newIndex = 0;

    for (int i = 0; i < flightCount; i++) {
        if (i != flightIndex) {
            newFlights[newIndex] = flights[i];
            newIndex++;
        }
        else {
            deleteSeatMap(*flights[i]);
            delete flights[i];
        }
    }

    delete[] flights;
    flights = newFlights;
    flightCount--;

    saveFlights(flights, flightCount);

    cout << "\nFlight removed successfully!\n";
    pauseScreen();
}

void viewPassengersAndFlights(Passenger** passengers, int passengerCount, Flight** flights, int flightCount) {
    clearScreen();
    cout << "\n========== Registered Passengers ==========\n";

    if (passengerCount == 0) {
        cout << "\nNo passengers registered.\n";
    }
    else {
        for (int i = 0; i < passengerCount; i++) {
            cout << "\nUser ID: " << passengers[i]->userId << endl;
            cout << "Name: " << passengers[i]->name << endl;
            cout << "Phone: " << passengers[i]->phone << endl;
            cout << "Status: " << passengers[i]->status << endl;
            cout << "Total Spent: $" << passengers[i]->totalSpent << endl;
            cout << "---------------------------------------\n";
        }
    }

    cout << "\n========== Registered Flights ==========\n";

    if (flightCount == 0) {
        cout << "\nNo flights registered.\n";
    }
    else {
        for (int i = 0; i < flightCount; i++) {
            cout << "\nFlight Number: " << flights[i]->flightNumber << endl;
            cout << "Destination: " << flights[i]->destination << endl;
            cout << "Departure: " << flights[i]->departureDate << " at " << flights[i]->departureTime << endl;
            cout << "Arrival: " << flights[i]->arrivalDate << " at " << flights[i]->arrivalTime << endl;
            cout << "Seats: " << flights[i]->availableSeats << "/" << flights[i]->totalSeats << endl;
            cout << "Status: " << flights[i]->status << endl;
            cout << "---------------------------------------\n";
        }
    }

    pauseScreen();
}

void viewPassengerReports(Passenger** passengers, int passengerCount, Booking** bookings, int bookingCount) {
    clearScreen();
    cout << "\n========== Passenger Transaction Reports ==========\n";

    if (passengerCount == 0) {
        cout << "\nNo passengers in the system.\n";
        pauseScreen();
        return;
    }

    for (int i = 0; i < passengerCount; i++) {
        cout << "\nPassenger: " << passengers[i]->name << " (" << passengers[i]->userId << ")" << endl;
        cout << "Total Spent: $" << passengers[i]->totalSpent << endl;

        bool hasBookings = false;
        for (int j = 0; j < bookingCount; j++) {
            if (bookings[j]->passengerId == passengers[i]->userId) {
                if (!hasBookings) {
                    cout << "Bookings:\n";
                    hasBookings = true;
                }
                cout << "  - " << bookings[j]->bookingDate << " | Flight: " << bookings[j]->flightNumber
                    << " | $" << bookings[j]->fare << " | " << bookings[j]->status << endl;
            }
        }

        if (!hasBookings) {
            cout << "No bookings found.\n";
        }

        cout << "---------------------------------------\n";
    }

    pauseScreen();
}

void viewFlightReports(Flight** flights, int flightCount) {
    clearScreen();
    cout << "\n========== Flight Inventory Reports ==========\n";

    if (flightCount == 0) {
        cout << "\nNo flights in the system.\n";
        pauseScreen();
        return;
    }

    for (int i = 0; i < flightCount; i++) {
        cout << "\nFlight Number: " << flights[i]->flightNumber << endl;
        cout << "Destination: " << flights[i]->destination << endl;
        cout << "Times Booked: " << flights[i]->timesBooked << endl;
        cout << "Total Passengers Carried: " << flights[i]->totalSeats - flights[i]->availableSeats << endl;
        cout << "Total Income Generated: $" << flights[i]->totalIncome << endl;
        cout << "Current Status: " << flights[i]->status << endl;
        cout << "Available Seats: " << flights[i]->availableSeats << "/" << flights[i]->totalSeats << endl;

        double utilizationRate = 0.0;
        if (flights[i]->totalSeats > 0) {
            utilizationRate = ((double)(flights[i]->totalSeats - flights[i]->availableSeats) / flights[i]->totalSeats) * 100;
        }
        cout << "Utilization Rate: " << utilizationRate << "%" << endl;

        cout << "---------------------------------------\n";
    }

    pauseScreen();
}

void changeAdminPassword(Admin** admins, int adminCount, string currentUserId) {
    clearScreen();
    cout << "\n========== Change Password ==========\n";

    int adminIndex = -1;
    for (int i = 0; i < adminCount; i++) {
        if (admins[i]->userId == currentUserId) {
            adminIndex = i;
            break;
        }
    }

    if (adminIndex == -1) {
        cout << "\nError: Admin not found!\n";
        pauseScreen();
        return;
    }

    string oldPassword, newPassword, confirmPassword;

    cout << "Enter current password: ";
    cin >> oldPassword;

    if (oldPassword != admins[adminIndex]->password) {
        cout << "\nError: Incorrect current password!\n";
        pauseScreen();
        return;
    }

    cout << "Enter new password: ";
    cin >> newPassword;

    if (newPassword.length() < 4) {
        cout << "\nError: Password must be at least 4 characters!\n";
        pauseScreen();
        return;
    }

    cout << "Confirm new password: ";
    cin >> confirmPassword;

    if (newPassword != confirmPassword) {
        cout << "\nError: Passwords do not match!\n";
        pauseScreen();
        return;
    }

    admins[adminIndex]->password = newPassword;
    saveAdmins(admins, adminCount);

    cout << "\nPassword changed successfully!\n";
    pauseScreen();
}

void adminMenu(Admin** admins, int adminCount, Passenger**& passengers, int& passengerCount, Flight**& flights, int& flightCount, Booking** bookings, int bookingCount, string currentUserId) {
    int choice;

    while (true) {
        clearScreen();
        cout << "\n========== Admin Menu ==========\n";
        cout << "1. View Registered Flights and Passengers\n";
        cout << "2. Add Passenger\n";
        cout << "3. Remove Passenger\n";
        cout << "4. Update Passenger Data\n";
        cout << "5. Add Flight\n";
        cout << "6. Remove Flight\n";
        cout << "7. View Passenger Reports\n";
        cout << "8. View Flight Reports\n";
        cout << "9. Change Password\n";
        cout << "10. Logout\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "\nError: Invalid input! Please enter a number.\n";
            pauseScreen();
            continue;
        }

        switch (choice) {
        case 1:
            viewPassengersAndFlights(passengers, passengerCount, flights, flightCount);
            break;
        case 2:
            addPassenger(passengers, passengerCount);
            break;
        case 3:
            removePassenger(passengers, passengerCount);
            break;
        case 4:
            updatePassengerData(passengers, passengerCount);
            break;
        case 5:
            addFlight(flights, flightCount);
            break;
        case 6:
            removeFlight(flights, flightCount);
            break;
        case 7:
            viewPassengerReports(passengers, passengerCount, bookings, bookingCount);
            break;
        case 8:
            viewFlightReports(flights, flightCount);
            break;
        case 9:
            changeAdminPassword(admins, adminCount, currentUserId);
            break;
        case 10:
            return;
        default:
            cout << "\nError: Invalid choice! Please enter a number between 1-10.\n";
            pauseScreen();
        }
    }
}

int main() {
    Admin** admins = nullptr;
    Passenger** passengers = nullptr;
    Flight** flights = nullptr;
    Booking** bookings = nullptr;

    int adminCount = 0;
    int passengerCount = 0;
    int flightCount = 0;
    int bookingCount = 0;

    loadAdmins(admins, adminCount);
    loadPassengers(passengers, passengerCount);
    loadFlights(flights, flightCount);
    loadBookings(bookings, bookingCount);

    int choice;

    while (true) {
        clearScreen();
        cout << "\n========================================\n";
        cout << "   AIRLINE RESERVATION SYSTEM\n";
        cout << "========================================\n";
        cout << "1. Passenger Login\n";
        cout << "2. Admin Login\n";
        cout << "3. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "\nError: Invalid input! Please enter a number.\n";
            pauseScreen();
            continue;
        }

        if (choice == 1) {
            clearScreen();
            cout << "\n========== Passenger Login ==========\n";

            string userId, password;
            cout << "Enter User ID: ";
            cin >> userId;
            cout << "Enter Password: ";
            cin >> password;

            bool found = false;
            for (int i = 0; i < passengerCount; i++) {
                if (passengers[i]->userId == userId && passengers[i]->password == password) {
                    found = true;
                    cout << "\nLogin successful! Welcome, " << passengers[i]->name << "!\n";
                    pauseScreen();
                    passengerMenu(passengers, passengerCount, flights, flightCount, bookings, bookingCount, userId);
                    break;
                }
            }

            if (!found) {
                cout << "\nError: Invalid credentials!\n";
                pauseScreen();
            }

        }
        else if (choice == 2) {
            clearScreen();
            cout << "\n========== Admin Login ==========\n";

            string userId, password;
            cout << "Enter User ID: ";
            cin >> userId;
            cout << "Enter Password: ";
            cin >> password;

            bool found = false;
            for (int i = 0; i < adminCount; i++) {
                if (admins[i]->userId == userId && admins[i]->password == password) {
                    found = true;
                    cout << "\nLogin successful! Welcome, Admin!\n";
                    pauseScreen();
                    adminMenu(admins, adminCount, passengers, passengerCount, flights, flightCount, bookings, bookingCount, userId);
                    break;
                }
            }

            if (!found) {
                cout << "\nError: Invalid credentials!\n";
                pauseScreen();
            }

        }
        else if (choice == 3) {
            cout << "\nThank you for using the Airline Reservation System!\n";

            for (int i = 0; i < adminCount; i++) {
                delete admins[i];
            }
            delete[] admins;

            for (int i = 0; i < passengerCount; i++) {
                delete passengers[i];
            }
            delete[] passengers;

            for (int i = 0; i < flightCount; i++) {
                deleteSeatMap(*flights[i]);
                delete flights[i];
            }
            delete[] flights;

            for (int i = 0; i < bookingCount; i++) {
                delete bookings[i];
            }
            delete[] bookings;

            break;

        }
        else {
            cout << "\nError: Invalid choice! Please enter a number between 1-3.\n";
            pauseScreen();
        }
    }

    return 0;
}