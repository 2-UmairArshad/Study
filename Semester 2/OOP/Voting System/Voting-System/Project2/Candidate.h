#ifndef CANDIDATE_H
#define CANDIDATE_H

#include <iostream>
#include "Validator.h"
#include "User.h"
#include "DatabaseManager.h"
#include "Admin.h"
using namespace std;

class Candidate : public User {
protected:
    string username;
    string password;
    int id;

public:
    virtual void viewDetails() = 0;
    virtual void viewVotes() = 0;

    bool login() override {
        cout << "\nEnter Candidate ID: ";
        if (!Validator::getIntInput(id)) return false;

        cin.ignore(); 

        cout << "Enter Username: ";
        getline(cin, username);

        if (username.empty()) {
            cout << "Username cannot be empty.\n";
            return false;
        }

        bool validUsername = true;
        for (int i = 0; username[i] != '\0'; i++) {
            if (!((username[i] >= 'A' && username[i] <= 'Z') ||
                (username[i] >= 'a' && username[i] <= 'z') ||
                username[i] == ' ')) {
                validUsername = false;
                break;
            }
        }

        if (!validUsername) {
            cout << "Username must contain only letters and spaces.\n";
            return false;
        }

        cout << "Enter Password: ";
        getline(cin, password);

        if (password.empty()) {
            cout << "Password cannot be empty.\n";
            return false;
        }

        if (password.length() < 6) {
            cout << "Password must be at least 6 characters long.\n";
            return false;
        }

        MYSQL* conn = DatabaseManager::getConnection();
        string query = "SELECT * FROM candidates WHERE id=" + to_string(id) +
            " AND name='" + username + "' AND password='" + password + "'";
        if (mysql_query(conn, query.c_str()) == 0) {
            MYSQL_RES* res = mysql_store_result(conn);
            if (mysql_num_rows(res) == 1) {
                cout << "Login successful.\n";
                mysql_free_result(res);
                return true;
            }
            mysql_free_result(res);
        }
        cout << "Invalid credentials.\n";
        return false;
    }

    void showMenu() override {
        int ch;
        while (true) {
            cout << "\n--- Candidate Menu ---\n";
            cout << "1. View My Details\n";
            cout << "2. View My Votes\n";
            cout << "3. Logout\n";
            cout << "Enter choice: ";
            if (!Validator::getIntInput(ch)) continue;

            if (ch == 1) viewDetails();
            else if (ch == 2) viewVotes();
            else if (ch == 3) break;
            else cout << "Invalid choice.\n";
        }
    }
};

class MNA : public Candidate {
public:
    void viewDetails() override {
        MYSQL* conn = DatabaseManager::getConnection();
        string query = "SELECT * FROM candidates WHERE id=" + to_string(id) + " AND type='MNA'";
        if (mysql_query(conn, query.c_str()) == 0) {
            MYSQL_RES* res = mysql_store_result(conn);
            MYSQL_ROW row = mysql_fetch_row(res);
            if (row) {
                cout << "\nName: " << row[1] << " | Party: " << row[2] << " | Province: " << row[4] << "\n";
            }
            else {
                cout << "No MNA details found.\n";
            }
            mysql_free_result(res);
        }
    }

    void viewVotes() override {
        MYSQL* conn = DatabaseManager::getConnection();
        string query = "SELECT votes FROM candidates WHERE id=" + to_string(id) + " AND type='MNA'";
        if (mysql_query(conn, query.c_str()) == 0) {
            MYSQL_RES* res = mysql_store_result(conn);
            MYSQL_ROW row = mysql_fetch_row(res);
            if (row) cout << "Votes: " << row[0] << "\n";
            else cout << "Votes not found.\n";
            mysql_free_result(res);
        }
    }
};

class MPA : public Candidate {
public:
    void viewDetails() override {
        MYSQL* conn = DatabaseManager::getConnection();
        string query = "SELECT * FROM candidates WHERE id=" + to_string(id) + " AND type='MPA'";
        if (mysql_query(conn, query.c_str()) == 0) {
            MYSQL_RES* res = mysql_store_result(conn);
            MYSQL_ROW row = mysql_fetch_row(res);
            if (row) {
                cout << "\nName: " << row[1] << " | Party: " << row[2] << " | District: " << row[5] << "\n";
            }
            else {
                cout << "No MPA details found.\n";
            }
            mysql_free_result(res);
        }
    }

    void viewVotes() override {
        MYSQL* conn = DatabaseManager::getConnection();
        string query = "SELECT votes FROM candidates WHERE id=" + to_string(id) + " AND type='MPA'";
        if (mysql_query(conn, query.c_str()) == 0) {
            MYSQL_RES* res = mysql_store_result(conn);
            MYSQL_ROW row = mysql_fetch_row(res);
            if (row) cout << "Votes: " << row[0] << "\n";
            else cout << "Votes not found.\n";
            mysql_free_result(res);
        }
    }
};

#endif
