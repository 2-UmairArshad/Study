#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
bool loginAdmin() {
    const string adminUsername = "admin";
    const string adminPassword = "password";

    string username, password;
    cout << "Enter Admin Username: ";
    cin >> username;
    cout << "Enter Admin Password: ";
    cin >> password;

    if (username == adminUsername && password == adminPassword) {
        cout << "Login successful!\n";
        return true;
    }
    return false;
}
