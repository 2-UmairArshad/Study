#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

const string USER_FILE = "users.txt";  // File to store user credentials
const int MAX_FLIGHTS = 10;

// Structure to store flight information
struct Flight {
    string flightNumber;
    string departureCity;
    string destinationCity;
    string departureDateTime;
};

Flight flights[MAX_FLIGHTS];

// Function to input city (allow multi-word cities)
void inputCity(string& city) {
    cin.ignore();  // To ignore the newline character left by previous input
    getline(cin, city);
}

// Function to input date in the format: day, month, year
void inputDate(int& day, int& month, int& year) {
    cout << "Enter day: ";
    cin >> day;
    cout << "Enter month: ";
    cin >> month;
    cout << "Enter year: ";
    cin >> year;
}

// Function to generate flights
void generateFlights() {
    string departureCity, destinationCity, ticketType;
    int depDay, depMonth, depYear, retDay = 0, retMonth = 0, retYear = 0;
    int numCities = 0;
    bool flag=true;
    // Ask for the trip type
    cout << "Do you want a one-way, two-way, or multi-city trip? ";
    cin >> ticketType;

    // Input city names using getline for multi-word cities
    cout<<"Enter Departure City";
    inputCity(departureCity);
    cout<<"Enter Destination City";
    inputCity(destinationCity);
while(flag) {
    // Ask for dates based on ticket type
    if (ticketType == "one-way") {
        cout << "Enter departure date:\n";
        inputDate(depDay, depMonth, depYear);
        flag=false;
    } else if (ticketType == "two-way") {
        cout << "Enter departure date:\n";
        inputDate(depDay, depMonth, depYear);
        cout << "Enter return date:\n";
        inputDate(retDay, retMonth, retYear);
        flag=false;
    } else if (ticketType == "multi-city") {
        // First, ask for how many cities the user is traveling to
        cout << "How many cities are you traveling to? ";
        cin >> numCities;

        // Loop to input cities and dates for each city
        for (int i = 0; i < numCities; i++) {
            cout << "Enter city " << i + 1 << " name: ";
            inputCity(destinationCity);

            cout << "Enter departure date for city " << i + 1 << ":\n";
            inputDate(depDay, depMonth, depYear);

            cout << "Enter return date for city " << i + 1 << ":\n";
            inputDate(retDay, retMonth, retYear);
            
        }
        flag=false;
    } else{
        cout<<"Wrong Input!";
    }
}
    cout << "Flights have been generated successfully!\n";
}

// User registration function (with file handling)
void registerUser() {
    string username, password;
    cout << "Enter your username: ";
    cin >> username;
    cout << "Enter your password: ";
    cin >> password;

    // Open file to store the credentials
    ofstream userFile(USER_FILE, ios::app);  // Open file in append mode
    if (userFile.is_open()) {
        userFile << username << " " << password << endl;  // Store username and password
        userFile.close();
        cout << "User registered successfully!\n";
    } else {
        cout << "Error opening file for registration.\n";
    }
}

// User login function (with file handling)
void loginUser() {
    string username, password;
    bool loggedIn = false;

    cout << "Enter your username: ";
    cin >> username;
    cout << "Enter your password: ";
    cin >> password;

    // Open file to read the stored credentials
    ifstream userFile(USER_FILE);
    string fileUsername, filePassword;
    if (userFile.is_open()) {
        while (userFile >> fileUsername >> filePassword) {
            if (fileUsername == username && filePassword == password) {
                loggedIn = true;
                cout << "Login successful!\n";
                break;
            }
        }
        userFile.close();
    } else {
        cout << "Error opening file for login.\n";
    }

    if (!loggedIn) {
        cout << "Invalid credentials. Please try again.\n";
    }
}

int main() {
    int choice;

    // Main menu
    while (true) {
        cout << "\nWelcome to the Airline Management System!\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Generate Flights\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                loginUser();
                break;
            case 3:
                generateFlights();
                break;
            case 4:
                cout << "Exiting the system...\n";
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}