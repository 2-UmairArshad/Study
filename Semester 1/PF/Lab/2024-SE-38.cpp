#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

const int ROWS = 15;
const int SEATS_PER_ROW = 30;

// Initializes Seating Chart with "#" Symbol
void initializeSeatingChart(char seating[ROWS][SEATS_PER_ROW]) {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < SEATS_PER_ROW; ++j) {
            seating[i][j] = '#';
        }
    }
}

// Inputs row prices 
void inputRowPrices(double rowPrices[ROWS]) {
    cout << "Enter ticket prices for each row (positive values only):\n";
    for (int i = 0; i < ROWS; ++i) {
        do {
            cout << "Row " << i + 1 << ": ";
            cin >> rowPrices[i];
            if (rowPrices[i] < 0) {
                cout << "Price cannot be negative. Please try again.\n";
            }
        } while (rowPrices[i] < 0);
    }
}

// Displays seating map
void displaySeatingChart(const char seating[ROWS][SEATS_PER_ROW]) {
    cout << "\nSeating Chart:\n";
    cout << "   ";
    for (int j = 0; j < SEATS_PER_ROW; ++j) {
        cout << setw(2) << j + 1;
    }
    cout << endl;

    for (int i = 0; i < ROWS; ++i) {
        cout << "Row " << setw(2) << i + 1 << ": ";
        for (int j = 0; j < SEATS_PER_ROW; ++j) {
            cout << seating[i][j] << " ";
        }
        cout << endl;
    }
}

// Loads data from file
bool loadFromFile(char seating[ROWS][SEATS_PER_ROW], double rowPrices[ROWS], double &totalRevenue, int &seatsSold, const string &filename) {
    ifstream inFile(filename);
    if (!inFile) return false;

    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < SEATS_PER_ROW; ++j) {
            inFile >> seating[i][j];
        }
    }

    for (int i = 0; i < ROWS; ++i) {
        inFile >> rowPrices[i];
    }

    inFile >> totalRevenue >> seatsSold;
    inFile.close();
    return true;
}

// Saves data in file
void saveToFile(const char seating[ROWS][SEATS_PER_ROW], const double rowPrices[ROWS], double totalRevenue, int seatsSold, const string &filename) {
    ofstream outFile(filename);
    if (!outFile) {
        cout << "Error: Could not open file for saving.\n";
        return;
    }

    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < SEATS_PER_ROW; ++j) {
            outFile << seating[i][j] << " ";
        }
        outFile << endl;
    }

    for (int i = 0; i < ROWS; ++i) {
        outFile << rowPrices[i] << " ";
    }

    outFile << endl << totalRevenue << " " << seatsSold;
    outFile.close();
}

// Sells tickets 
void sellTickets(char seating[ROWS][SEATS_PER_ROW], double rowPrices[ROWS], double &totalRevenue, int &seatsSold) {
    int row, seat;

    cout << "\nEnter row number (1-" << ROWS << "): ";
    cin >> row;
    cout << "Enter seat number (1-" << SEATS_PER_ROW << "): ";
    cin >> seat;

    if (row < 1 || row > ROWS || seat < 1 || seat > SEATS_PER_ROW) {
        cout << "Invalid input. Please enter valid row and seat numbers.\n";
        return;
    }

    if (seating[row - 1][seat - 1] == '*') {
        cout << "Seat already sold.\n";
        return;
    }

    seating[row - 1][seat - 1] = '*';
    totalRevenue += rowPrices[row - 1];
    ++seatsSold;

    cout << "Ticket sold successfully for $" << rowPrices[row - 1] << "\n";
}

// Displays sales statistics
void displayStatistics(const char seating[ROWS][SEATS_PER_ROW], double totalRevenue, int seatsSold) {
    int availableSeats = 0;
    int rowAvailable[ROWS] = {0};

    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < SEATS_PER_ROW; ++j) {
            if (seating[i][j] == '#') {
                ++availableSeats;
                ++rowAvailable[i];
            }
        }
    }

    cout << "\nSales Statistics:\n";
    cout << "Total Revenue: $" << fixed << setprecision(2) << totalRevenue << endl;
    cout << "Total Seats Sold: " << seatsSold << endl;
    cout << "Total Available Seats: " << availableSeats << endl;

    for (int i = 0; i < ROWS; ++i) {
        cout << "Row " << i + 1 << ": " << rowAvailable[i] << " available seats\n";
    }
}

// Main Menu
void showMenu() {
    cout << "\nMenu:\n";
    cout << "1. Display Seating Chart\n";
    cout << "2. Sell Tickets\n";
    cout << "3. View Total Sales and Statistics\n";
    cout << "4. Save and Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    char seating[ROWS][SEATS_PER_ROW];
    double rowPrices[ROWS] = {0};
    double totalRevenue = 0.0;
    int seatsSold = 0;

    string filename = "theater_data.txt";

    if (!loadFromFile(seating, rowPrices, totalRevenue, seatsSold, filename)) {
        initializeSeatingChart(seating);
        inputRowPrices(rowPrices);
    }

    int choice;
    do {
        showMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                displaySeatingChart(seating);
                break;
            case 2:
                sellTickets(seating, rowPrices, totalRevenue, seatsSold);
                break;
            case 3:
                displayStatistics(seating, totalRevenue, seatsSold);
                break;
            case 4:
                saveToFile(seating, rowPrices, totalRevenue, seatsSold, filename);
                cout << "Data saved. Exiting program.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}