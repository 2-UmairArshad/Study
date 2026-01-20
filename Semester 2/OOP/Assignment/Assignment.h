#pragma once
#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H

#include <iostream>
using namespace std;

class Account {
protected:
    double balance;
    int numDeposits;
    int numWithdrawals;
    double annualInterestRate;
    double monthlyServiceCharges;

public:
    Account(double bal, double rate) : balance(bal), annualInterestRate(rate) {
        numDeposits = 0;
        numWithdrawals = 0;
        monthlyServiceCharges = 0.0;
    }
    virtual ~Account() {}

    virtual void deposit(double amount) {
        balance += amount;
        numDeposits++;
    }

    virtual void withdraw(double amount) {
        balance -= amount;
        numWithdrawals++;
    }

    virtual void calcint() {
        double monthlyInterestRate = annualInterestRate / 12;
        double monthlyInterest = balance * monthlyInterestRate;
        balance += monthlyInterest;
    }

    virtual void monthlyProc() {
        balance -= monthlyServiceCharges;
        calcint();
        numWithdrawals = 0;
        numDeposits = 0;
        monthlyServiceCharges = 0.0;
    }

    double getBalance() const { return balance; }
    int getNumDeposits() const { return numDeposits; }
    int getNumWithdrawals() const { return numWithdrawals; }
    double getAnnualInterestRate() const { return annualInterestRate; }
    double getMonthlyServiceCharges() const { return monthlyServiceCharges; }

    void setBalance(double bal) { balance = bal; }
    void setAnnualInterestRate(double rate) { annualInterestRate = rate; }
    void setMonthlyServiceCharges(double charges) { monthlyServiceCharges = charges; }

    Account& operator=(const Account& other) {
        if (this != &other) {
            balance = other.balance;
            numDeposits = other.numDeposits;
            numWithdrawals = other.numWithdrawals;
            annualInterestRate = other.annualInterestRate;
            monthlyServiceCharges = other.monthlyServiceCharges;
        }
        return *this;
    }

    friend ostream& operator<<(ostream& os, const Account& acc) {
        os << "Balance: $" << acc.balance << "\n"
            << "Number of deposits: " << acc.numDeposits << "\n"
            << "Number of withdrawals: " << acc.numWithdrawals << "\n"
            << "Annual interest rate: " << (acc.annualInterestRate * 100) << "%\n"
            << "Monthly service charges: $" << acc.monthlyServiceCharges;
        return os;
    }

    friend istream& operator>>(istream& is, Account& acc) {
        cout << "Enter initial balance: ";
        is >> acc.balance;
        cout << "Enter annual interest rate (as decimal, e.g., 0.05 for 5%): ";
        is >> acc.annualInterestRate;
        return is;
    }
};

class SavingsAccount : public Account {
private:
    bool status;

public:
    SavingsAccount(double bal, double rate) : Account(bal, rate) {
        status = (bal >= 25.0);
    }

    void withdraw(double amount) override {
        if (!status) {
            cout << "Account is inactive. No withdrawals allowed.\n";
            return;
        }
        Account::withdraw(amount);
        if (balance < 25.0) {
            status = false;
        }
    }

    void deposit(double amount) override {
        if (!status && (balance + amount) >= 25.0) {
            status = true;
            cout << "Account is now active.\n";
        }
        Account::deposit(amount);
    }

    void monthlyProc() override {
        if (numWithdrawals > 4) {
            monthlyServiceCharges += (numWithdrawals - 4) * 1.0;
        }
        Account::monthlyProc();
        if (balance < 25.0) {
            status = false;
        }
    }

    bool getStatus() const { return status; }
    void setStatus(bool s) { status = s; }

    SavingsAccount& operator=(const SavingsAccount& other) {
        if (this != &other) {
            Account::operator=(other);
            status = other.status;
        }
        return *this;
    }

    friend ostream& operator<<(ostream& os, const SavingsAccount& acc) {
        os << static_cast<const Account&>(acc) << "\n"
            << "Status: " << (acc.status ? "Active" : "Inactive");
        return os;
    }

    friend istream& operator>>(istream& is, SavingsAccount& acc) {
        is >> static_cast<Account&>(acc);
        acc.status = (acc.balance >= 25.0);
        return is;
    }
};

class CheckingAccount : public Account {
public:
    CheckingAccount(double bal, double rate) : Account(bal, rate) {}

    void withdraw(double amount) override {
        if (balance - amount < 0) {
            cout << "Insufficient funds. $15 service charge will be applied.\n";
            monthlyServiceCharges += 15.0;
            balance -= 15.0;
            return;
        }
        Account::withdraw(amount);
    }

    void monthlyProc() override {
        monthlyServiceCharges += 5.0 + (0.10 * numWithdrawals);
        Account::monthlyProc();
    }

    CheckingAccount& operator=(const CheckingAccount& other) {
        if (this != &other) {
            Account::operator=(other);
        }
        return *this;
    }

    friend ostream& operator<<(ostream& os, const CheckingAccount& acc) {
        os << static_cast<const Account&>(acc);
        return os;
    }

    friend istream& operator>>(istream& is, CheckingAccount& acc) {
        is >> static_cast<Account&>(acc);
        return is;
    }
};

#endif