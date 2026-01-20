#include "Assignment.h"

int main() {
    Account* savings = new SavingsAccount(100.0, 0.05);
    Account* checking = new CheckingAccount(50.0, 0.03);

    cout << "=== Savings Account Operations ===\n";
    cout << "Initial balance: $" << savings->getBalance() << "\n";

    double amount;
    cout << "Enter deposit amount for savings: ";
    cin >> amount;
    savings->deposit(amount);

    cout << "Enter withdrawal amount for savings: ";
    cin >> amount;
    savings->withdraw(amount);

    cout << "\n=== Checking Account Operations ===\n";
    cout << "Initial balance: $" << checking->getBalance() << "\n";

    cout << "Enter deposit amount for checking: ";
    cin >> amount;
    checking->deposit(amount);

    cout << "Enter withdrawal amount for checking: ";
    cin >> amount;
    checking->withdraw(amount);

    savings->monthlyProc();
    checking->monthlyProc();

    cout << "\n=== Monthly Statistics ===\n";
    cout << "Savings Account:\n" << *savings << "\n\n";
    cout << "Checking Account:\n" << *checking << "\n";

    delete savings;
    delete checking;

    return 0;
}