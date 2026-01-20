// This is the starting point of the project. We'll build it modularly.
#include <iostream>
#include "Admin.h"
#include "Candidate.h"
#include "Voter.h"
#include "Validator.h"
#include "DatabaseManager.h"
#include <mysql.h>
using namespace std;
MYSQL* DatabaseManager::conn = nullptr;
void showMainMenu() {
    int ch;
    while (true) {
        cout << "\n--- Online Voting System ---\n";
        cout << "1. Login as Admin\n";
        cout << "2. Login as Candidate\n";
        cout << "3. Voter (Login / Signup)\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        if (!Validator::getIntInput(ch)) continue;

        switch (ch) {
        case 1: {
            Admin admin;
            if (admin.login()) admin.showMenu();
            break;
        }
        case 2: {
                  int type;
                  cout << "Are you an MNA (1) or MPA (2)? ";
                  if (!Validator::getIntInput(type)) break;

                  Candidate* candidate = nullptr;
                  if (type == 1) candidate = new MNA();
                  else if (type == 2) candidate = new MPA();
                  else {
                      cout << "Invalid candidate type.\n";
                      break;
                  }

                  if (candidate->login()) {
                      candidate->showMenu();
                  }

                  delete candidate;
                  break;
              }
        case 3: {
            Voter voter;
            int voterChoice;
            cout << "\n1. Login\n2. Signup\nChoice: ";
            if (!Validator::getIntInput(voterChoice)) break;

            if (voterChoice == 1) {
                if (voter.login()) {
                    voter.showMenu();
                }
            }
            else if (voterChoice == 2) {
                if (voter.signup()) {
                    voter.showMenu();
                }
            }
            else {
                cout << "Invalid choice.\n";
            }
            break;
        }
        case 4:
            cout << "Exiting program.\n";
            return;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    }
}

int main() {
    DatabaseManager::connect();
    showMainMenu();
    DatabaseManager::disconnect();
    return 0;
}
