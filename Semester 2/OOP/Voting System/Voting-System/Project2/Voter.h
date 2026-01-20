#pragma once
#ifndef VOTER_H
#define VOTER_H

#include <iostream>
#include "Validator.h"
#include "DatabaseManager.h"
#include "User.h"
using namespace std;

class Voter : public User {
private:
    string cnic;
    string password;
    string name;
    string province;
    string district;
    bool isLoggedIn;
    bool hasVotedMNA;
    bool hasVotedMPA;

    bool isVotingOpen() {
        MYSQL* conn = DatabaseManager::getConnection();
        mysql_query(conn, "SELECT status FROM election_status WHERE id=1");
        MYSQL_RES* res = mysql_store_result(conn);
        MYSQL_ROW row = mysql_fetch_row(res);
        bool open = (row && string(row[0]) == "start");
        mysql_free_result(res);
        return open;
    }

public:
    Voter() : isLoggedIn(false), hasVotedMNA(false), hasVotedMPA(false) {}

    bool login() override {
        cout << "\nEnter CNIC: ";
        cin >> cnic;
        cout << "Enter Password: ";
        cin >> password;

        MYSQL* conn = DatabaseManager::getConnection();
        string query = "SELECT name, province, district, has_voted_mna, has_voted_mpa FROM voters WHERE cnic='" + cnic + "' AND password='" + password + "'";
        if (mysql_query(conn, query.c_str()) == 0) {
            MYSQL_RES* res = mysql_store_result(conn);
            MYSQL_ROW row = mysql_fetch_row(res);
            if (row) {
                name = row[0];
                province = row[1];
                district = row[2];
                hasVotedMNA = (row[3] && string(row[3]) == "1");
                hasVotedMPA = (row[4] && string(row[4]) == "1");
                isLoggedIn = true;
                cout << "\nLogin successful. Welcome, " << name << "!\n";
                mysql_free_result(res);
                return true;
            }
            mysql_free_result(res);
        }
        cout << "\nInvalid CNIC or password.\n";
        return false;
    }
    bool signup() {
        cout << "\n--- Voter Registration ---\n";

        cout << "Enter CNIC (13-15 digits): ";
        cin >> cnic;

        if (!Validator::isNumeric(cnic) || cnic.length() < 13 || cnic.length() > 15) {
            cout << "Invalid CNIC. Must be 13-15 digits.\n";
            return false;
        }

        MYSQL* conn = DatabaseManager::getConnection();
        string checkQuery = "SELECT cnic FROM voters WHERE cnic='" + cnic + "'";
        if (mysql_query(conn, checkQuery.c_str()) == 0) {
            MYSQL_RES* res = mysql_store_result(conn);
            if (mysql_num_rows(res) > 0) {
                cout << "This CNIC is already registered. Please login instead.\n";
                mysql_free_result(res);
                return false;
            }
            mysql_free_result(res);
        }

        cout << "Enter Full Name: ";
        cin.ignore();
        getline(cin, name);

        cout << "Enter Password: ";
        cin >> password;

        if (password.length() < 6) {
            cout << "Password must be at least 6 characters long.\n";
            return false;
        }

        cout << "Enter Province: ";
        cin >> province;

        if (!Validator::isAlpha(province)) {
            cout << "Province name must contain only letters.\n";
            return false;
        }

        cout << "Enter District: ";
        cin >> district;

        if (!Validator::isAlpha(district)) {
            cout << "District name must contain only letters.\n";
            return false;
        }

        string insertQuery = "INSERT INTO voters (cnic, name, password, province, district, has_voted_mna, has_voted_mpa) VALUES ('" +
            cnic + "', '" + name + "', '" + password + "', '" + province + "', '" + district + "', FALSE, FALSE)";

        if (mysql_query(conn, insertQuery.c_str()) == 0) {
            cout << "\nRegistration successful! You can now vote.\n";
            isLoggedIn = true;
            hasVotedMNA = false;
            hasVotedMPA = false;
            return true;
        }
        else {
            cout << "Registration failed: " << mysql_error(conn) << "\n";
            return false;
        }
    }
    void showMenu() override {
        if (!isLoggedIn) return;
        int ch;
        while (true) {
            cout << "\n--- Voter Menu ---\n";
            cout << "1. View Results\n";
            cout << "2. Vote for MNA\n";
            cout << "3. Vote for MPA\n";
            cout << "4. Logout\n";
            cout << "Enter choice: ";
            if (!Validator::getIntInput(ch)) continue;

            switch (ch) {
            case 1: viewResults(); break;
            case 2: voteFor("MNA"); break;
            case 3: voteFor("MPA"); break;
            case 4: return;
            default: cout << "Invalid choice. Try again.\n";
            }
        }
    }

    void viewResults() {
        MYSQL* conn = DatabaseManager::getConnection();
        string query = "SELECT id, name, party, type, votes FROM candidates WHERE province='" + province + "' OR district='" + district + "' ORDER BY votes DESC";
        mysql_query(conn, query.c_str());
        MYSQL_RES* res = mysql_store_result(conn);
        MYSQL_ROW row;

        cout << "\n--- Election Results for your Region ---\n";
        while ((row = mysql_fetch_row(res))) {
            cout << "ID: " << row[0]
                << " | Name: " << row[1]
                << " | Party: " << row[2]
                << " | Type: " << row[3]
                << " | Votes: " << row[4] << "\n";
        }
        mysql_free_result(res);
    }

    void voteFor(string type) {
        if (!isVotingOpen()) {
            cout << "Voting is currently closed. Please try again later.\n";
            return;
        }

        // Check if already voted for this type
        if (type == "MNA" && hasVotedMNA) {
            cout << "You have already voted for MNA.\n";
            return;
        }
        if (type == "MPA" && hasVotedMPA) {
            cout << "You have already voted for MPA.\n";
            return;
        }

        MYSQL* conn = DatabaseManager::getConnection();
        string filter = (type == "MNA") ? ("province='" + province + "'") : ("district='" + district + "'");
        string query = "SELECT id, name, party FROM candidates WHERE type='" + type + "' AND " + filter;
        mysql_query(conn, query.c_str());
        MYSQL_RES* res = mysql_store_result(conn);
        MYSQL_ROW row;

        int ids[100]; int idx = 0;
        cout << "\n--- " << type << " Candidates ---\n";
        while ((row = mysql_fetch_row(res))) {
            int cid = atoi(row[0]);
            if (idx < 100) ids[idx++] = cid;
            cout << "ID: " << cid
                << " | Name: " << row[1]
                << " | Party: " << row[2] << "\n";
        }
        mysql_free_result(res);

        if (idx == 0) {
            cout << "No candidates available for your region.\n";
            return;
        }

        int voteId;
        cout << "Enter Candidate ID to vote for: ";
        if (!Validator::getIntInput(voteId)) return;

        bool valid = false;
        for (int i = 0; i < idx; ++i) {
            if (voteId == ids[i]) {
                valid = true;
                break;
            }
        }
        if (!valid) {
            cout << "Invalid Candidate ID for your region.\n";
            return;
        }

        string updateVotes = "UPDATE candidates SET votes = votes + 1 WHERE id=" + to_string(voteId);
        mysql_query(conn, updateVotes.c_str());

        string columnName = (type == "MNA") ? "has_voted_mna" : "has_voted_mpa";
        string updateVoted = "UPDATE voters SET " + columnName + "=TRUE WHERE cnic='" + cnic + "'";
        mysql_query(conn, updateVoted.c_str());

        if (type == "MNA") hasVotedMNA = true;
        else hasVotedMPA = true;

        cout << "Your vote has been cast for " << type << ". Thank you!\n";
    }
};

#endif
