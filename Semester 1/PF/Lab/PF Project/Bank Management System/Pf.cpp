#include <iostream>
#include <string>
using namespace std;

// Maximum number of accounts
const int MAX_ACCOUNTS = 100;

// Global arrays to store account data
int accountNumbers[MAX_ACCOUNTS];
string accountHolders[MAX_ACCOUNTS];
string accountTypes[MAX_ACCOUNTS];
string contactNumbers[MAX_ACCOUNTS];
double balances[MAX_ACCOUNTS];
string passwords[MAX_ACCOUNTS];
int accountCreationYear[MAX_ACCOUNTS];
int accountCreationMonth[MAX_ACCOUNTS];
int accountCreationDay[MAX_ACCOUNTS];
int totalAccounts = 0;

// Transaction history
string transactionHistory[MAX_ACCOUNTS][50];
int transactionCount[MAX_ACCOUNTS] = { 0 };

// Function declarations
void displayMainMenu();
void displayAdminMenu();
void createAccount();
void depositMoney();
void withdrawMoney();
void checkBalance();
void displayAllAccounts();
void deleteAccount();
void modifyAccount();
void transferMoney();
void viewTransactionHistory();
void calculateInterest();
void searchAccount();
void displayBankStatistics();
int findAccount(int accNum);
void addTransaction(int index, string transaction);
void displayHeader();
void displayLine();
bool validatePassword(int index);
void changePassword();
void displayAccountDetails(int index);
void sortAccountsByBalance();
void displayTopAccounts();

// Main function
int main() {
    int choice;

    displayHeader();
    cout << "\n*** WELCOME TO BANKING MANAGEMENT SYSTEM ***\n";
    cout << "\nThis system helps you manage your bank accounts efficiently.\n";

    do {
        displayMainMenu();
        cin >> choice;

        switch (choice) {
        case 1:
            createAccount();
            break;
        case 2:
            depositMoney();
            break;
        case 3:
            withdrawMoney();
            break;
        case 4:
            checkBalance();
            break;
        case 5:
            displayAllAccounts();
            break;
        case 6:
            transferMoney();
            break;
        case 7:
            viewTransactionHistory();
            break;
        case 8:
            searchAccount();
            break;
        case 9:
            displayAdminMenu();
            break;
        case 10:
            cout << "\n\n==========================================\n";
            cout << "  Thank You for Using Our System!\n";
            cout << "==========================================\n";
            cout << "Your trust is our priority.\n";
            cout << "Visit us again soon!\n";
            cout << "==========================================\n\n";
            break;
        default:
            cout << "\n*** ERROR: Invalid choice! ***\n";
            cout << "Please enter a number between 1-10.\n";
        }

    } while (choice != 10);

    return 0;
}

// Function to display decorative header
void displayHeader() {
    cout << "\n\n";
    cout << "##########################################\n";
    cout << "#                                        #\n";
    cout << "#   BANKING MANAGEMENT SYSTEM            #\n";
    cout << "#                                        #\n";
    cout << "#      Secure | Fast | Reliable          #\n";
    cout << "#                                        #\n";
    cout << "##########################################\n";
}

// Function to display line
void displayLine() {
    cout << "------------------------------------------\n";
}

// Function to display main menu
void displayMainMenu() {
    cout << "\n\n==========================================\n";
    cout << "      MAIN MENU\n";
    cout << "==========================================\n";
    cout << "1. Create New Account\n";
    cout << "2. Deposit Money\n";
    cout << "3. Withdraw Money\n";
    cout << "4. Check Balance\n";
    cout << "5. Display All Accounts\n";
    cout << "6. Transfer Money\n";
    cout << "7. View Transaction History\n";
    cout << "8. Search Account\n";
    cout << "9. Admin Menu\n";
    cout << "10. Exit System\n";
    cout << "==========================================\n";
    cout << "Enter your choice: ";
}

// Function to display admin menu
void displayAdminMenu() {
    int adminChoice;

    cout << "\n--- ADMIN AUTHENTICATION ---\n";
    cout << "Enter Admin Password: ";
    string adminPass;
    cin >> adminPass;

    if (adminPass != "admin123") {
        cout << "\n*** ACCESS DENIED! ***\n";
        cout << "Incorrect admin password.\n";
        return;
    }

    do {
        cout << "\n\n==========================================\n";
        cout << "      ADMIN MENU\n";
        cout << "==========================================\n";
        cout << "1. Modify Account\n";
        cout << "2. Delete Account\n";
        cout << "3. Calculate Interest\n";
        cout << "4. Display Bank Statistics\n";
        cout << "5. Display Top Accounts\n";
        cout << "6. Change Account Password\n";
        cout << "7. Back to Main Menu\n";
        cout << "==========================================\n";
        cout << "Enter your choice: ";
        cin >> adminChoice;

        switch (adminChoice) {
        case 1:
            modifyAccount();
            break;
        case 2:
            deleteAccount();
            break;
        case 3:
            calculateInterest();
            break;
        case 4:
            displayBankStatistics();
            break;
        case 5:
            displayTopAccounts();
            break;
        case 6:
            changePassword();
            break;
        case 7:
            cout << "\nReturning to Main Menu...\n";
            break;
        default:
            cout << "\n*** Invalid choice! ***\n";
        }

    } while (adminChoice != 7);
}

// Function to find account by account number
int findAccount(int accNum) {
    for (int i = 0; i < totalAccounts; i++) {
        if (accountNumbers[i] == accNum) {
            return i;
        }
    }
    return -1;
}

// Function to add transaction to history
void addTransaction(int index, string transaction) {
    if (transactionCount[index] < 50) {
        transactionHistory[index][transactionCount[index]] = transaction;
        transactionCount[index]++;
    }
}

// Function to create new account
void createAccount() {
    if (totalAccounts >= MAX_ACCOUNTS) {
        cout << "\n*** BANK CAPACITY FULL! ***\n";
        cout << "Cannot create more accounts.\n";
        cout << "Maximum accounts limit reached: " << MAX_ACCOUNTS << "\n";
        return;
    }

    cout << "\n==========================================\n";
    cout << "    CREATE NEW ACCOUNT\n";
    cout << "==========================================\n";

    int accNum;
    cout << "Enter Account Number (4-6 digits): ";
    cin >> accNum;

    // Validate account number
    if (accNum < 1000 || accNum > 999999) {
        cout << "\n*** Invalid Account Number! ***\n";
        cout << "Account number must be between 1000-999999.\n";
        return;
    }

    // Check if account already exists
    if (findAccount(accNum) != -1) {
        cout << "\n*** Account Number Already Exists! ***\n";
        cout << "Please use a different account number.\n";
        return;
    }

    cin.ignore();
    cout << "Enter Account Holder Name: ";
    getline(cin, accountHolders[totalAccounts]);

    cout << "Enter Account Type (Savings/Current/Fixed): ";
    getline(cin, accountTypes[totalAccounts]);

    cout << "Enter Contact Number: ";
    getline(cin, contactNumbers[totalAccounts]);

    cout << "Set Account Password (4 digits): ";
    cin >> passwords[totalAccounts];

    double initialDeposit;
    cout << "Enter Initial Deposit Amount: $";
    cin >> initialDeposit;

    if (initialDeposit < 0) {
        cout << "\n*** Invalid Amount! ***\n";
        cout << "Initial deposit cannot be negative.\n";
        return;
    }

    if (initialDeposit < 100) {
        cout << "\n*** Warning! ***\n";
        cout << "Minimum initial deposit recommended: $100\n";
        cout << "Do you want to continue? (y/n): ";
        char confirm;
        cin >> confirm;
        if (confirm != 'y' && confirm != 'Y') {
            cout << "\nAccount creation cancelled.\n";
            return;
        }
    }

    // Store account details
    accountNumbers[totalAccounts] = accNum;
    balances[totalAccounts] = initialDeposit;

    // Store creation date (simplified)
    accountCreationDay[totalAccounts] = 11;
    accountCreationMonth[totalAccounts] = 1;
    accountCreationYear[totalAccounts] = 2026;

    // Initialize transaction count
    transactionCount[totalAccounts] = 0;

    // Add first transaction
    string transaction = "Account created with initial deposit: $";
    addTransaction(totalAccounts, transaction);

    totalAccounts++;

    cout << "\n==========================================\n";
    cout << " *** ACCOUNT CREATED SUCCESSFULLY! ***\n";
    cout << "==========================================\n";
    cout << "Account Number: " << accNum << "\n";
    cout << "Account Holder: " << accountHolders[totalAccounts - 1] << "\n";
    cout << "Initial Balance: $" << initialDeposit << "\n";
    cout << "==========================================\n";
}

// Function to deposit money
void depositMoney() {
    int accNum;
    cout << "\n==========================================\n";
    cout << "      DEPOSIT MONEY\n";
    cout << "==========================================\n";
    cout << "Enter Account Number: ";
    cin >> accNum;

    int index = findAccount(accNum);

    if (index == -1) {
        cout << "\n*** ACCOUNT NOT FOUND! ***\n";
        cout << "Please check the account number and try again.\n";
        return;
    }

    cout << "\nAccount Holder: " << accountHolders[index] << "\n";
    cout << "Current Balance: $" << balances[index] << "\n";
    displayLine();

    double amount;
    cout << "Enter amount to deposit: $";
    cin >> amount;

    if (amount <= 0) {
        cout << "\n*** Invalid Amount! ***\n";
        cout << "Deposit amount must be greater than zero.\n";
        return;
    }

    if (amount > 100000) {
        cout << "\n*** Large Deposit Alert! ***\n";
        cout << "Deposits over $100,000 require additional verification.\n";
        cout << "Please visit the nearest branch.\n";
        return;
    }

    balances[index] += amount;

    // Add transaction to history
    string transaction = "Deposited: $";
    addTransaction(index, transaction);

    cout << "\n==========================================\n";
    cout << " *** DEPOSIT SUCCESSFUL! ***\n";
    cout << "==========================================\n";
    cout << "Amount Deposited: $" << amount << "\n";
    cout << "New Balance: $" << balances[index] << "\n";
    cout << "==========================================\n";
}

// Function to withdraw money
void withdrawMoney() {
    int accNum;
    cout << "\n==========================================\n";
    cout << "      WITHDRAW MONEY\n";
    cout << "==========================================\n";
    cout << "Enter Account Number: ";
    cin >> accNum;

    int index = findAccount(accNum);

    if (index == -1) {
        cout << "\n*** ACCOUNT NOT FOUND! ***\n";
        cout << "Please check the account number and try again.\n";
        return;
    }

    // Password verification
    if (!validatePassword(index)) {
        return;
    }

    cout << "\nAccount Holder: " << accountHolders[index] << "\n";
    cout << "Available Balance: $" << balances[index] << "\n";
    displayLine();

    double amount;
    cout << "Enter amount to withdraw: $";
    cin >> amount;

    if (amount <= 0) {
        cout << "\n*** Invalid Amount! ***\n";
        cout << "Withdrawal amount must be greater than zero.\n";
        return;
    }

    if (amount > balances[index]) {
        cout << "\n==========================================\n";
        cout << " *** INSUFFICIENT BALANCE! ***\n";
        cout << "==========================================\n";
        cout << "Requested Amount: $" << amount << "\n";
        cout << "Available Balance: $" << balances[index] << "\n";
        cout << "Shortage: $" << (amount - balances[index]) << "\n";
        cout << "==========================================\n";
        return;
    }

    // Check for minimum balance
    if ((balances[index] - amount) < 100) {
        cout << "\n*** Warning! ***\n";
        cout << "Minimum balance of $100 recommended.\n";
        cout << "Remaining balance will be: $" << (balances[index] - amount) << "\n";
        cout << "Do you want to continue? (y/n): ";
        char confirm;
        cin >> confirm;
        if (confirm != 'y' && confirm != 'Y') {
            cout << "\nWithdrawal cancelled.\n";
            return;
        }
    }

    balances[index] -= amount;

    // Add transaction to history
    string transaction = "Withdrawn: $";
    addTransaction(index, transaction);

    cout << "\n==========================================\n";
    cout << " *** WITHDRAWAL SUCCESSFUL! ***\n";
    cout << "==========================================\n";
    cout << "Amount Withdrawn: $" << amount << "\n";
    cout << "Remaining Balance: $" << balances[index] << "\n";
    cout << "==========================================\n";
}

// Function to validate password
bool validatePassword(int index) {
    string inputPass;
    cout << "Enter Account Password: ";
    cin >> inputPass;

    if (inputPass != passwords[index]) {
        cout << "\n*** INCORRECT PASSWORD! ***\n";
        cout << "Access denied.\n";
        return false;
    }
    return true;
}

// Function to check balance
void checkBalance() {
    int accNum;
    cout << "\n==========================================\n";
    cout << "      CHECK BALANCE\n";
    cout << "==========================================\n";
    cout << "Enter Account Number: ";
    cin >> accNum;

    int index = findAccount(accNum);

    if (index == -1) {
        cout << "\n*** ACCOUNT NOT FOUND! ***\n";
        return;
    }

    // Password verification
    if (!validatePassword(index)) {
        return;
    }
    displayAccountDetails(index);
}

// Function to display account details
void displayAccountDetails(int index) {
    cout << "\n==========================================\n";
    cout << "      ACCOUNT DETAILS\n";
    cout << "==========================================\n";
    cout << "Account Number: " << accountNumbers[index] << "\n";
    cout << "Account Holder: " << accountHolders[index] << "\n";
    cout << "Account Type: " << accountTypes[index] << "\n";
    cout << "Contact Number: " << contactNumbers[index] << "\n";
    cout << "Current Balance: $" << balances[index] << "\n";
    cout << "Account Created: " << accountCreationDay[index] << "/"
        << accountCreationMonth[index] << "/" << accountCreationYear[index] << "\n";
    cout << "==========================================\n";
}

// Function to display all accounts
void displayAllAccounts() {
    if (totalAccounts == 0) {
        cout << "\n*** NO ACCOUNTS IN THE SYSTEM! ***\n";
        cout << "Please create an account first.\n";
        return;
    }

    cout << "\n==========================================\n";
    cout << "      ALL BANK ACCOUNTS\n";
    cout << "==========================================\n";
    cout << "Total Accounts: " << totalAccounts << "\n";
    displayLine();

    for (int i = 0; i < totalAccounts; i++) {
        cout << "\nAccount #" << (i + 1) << "\n";
        cout << "Account Number: " << accountNumbers[i] << "\n";
        cout << "Account Holder: " << accountHolders[i] << "\n";
        cout << "Account Type: " << accountTypes[i] << "\n";
        cout << "Balance: $" << balances[i] << "\n";
        displayLine();
    }
}

// Function to transfer money
void transferMoney() {
    int fromAcc, toAcc;

    cout << "\n==========================================\n";
    cout << "      TRANSFER MONEY\n";
    cout << "==========================================\n";
    cout << "Enter Source Account Number: ";
    cin >> fromAcc;

    int fromIndex = findAccount(fromAcc);

    if (fromIndex == -1) {
        cout << "\n*** SOURCE ACCOUNT NOT FOUND! ***\n";
        return;
    }

    // Password verification
    if (!validatePassword(fromIndex)) {
        return;
    }

    cout << "Enter Destination Account Number: ";
    cin >> toAcc;

    int toIndex = findAccount(toAcc);

    if (toIndex == -1) {
        cout << "\n*** DESTINATION ACCOUNT NOT FOUND! ***\n";
        return;
    }

    if (fromAcc == toAcc) {
        cout << "\n*** ERROR! ***\n";
        cout << "Cannot transfer to the same account.\n";
        return;
    }

    cout << "\nFrom: " << accountHolders[fromIndex] << " (Balance: $" << balances[fromIndex] << ")\n";
    cout << "To: " << accountHolders[toIndex] << "\n";
    displayLine();

    double amount;
    cout << "Enter amount to transfer: $";
    cin >> amount;

    if (amount <= 0) {
        cout << "\n*** Invalid Amount! ***\n";
        return;
    }

    if (amount > balances[fromIndex]) {
        cout << "\n*** INSUFFICIENT BALANCE! ***\n";
        return;
    }

    balances[fromIndex] -= amount;
    balances[toIndex] += amount;

    // Add transactions to history
    addTransaction(fromIndex, "Transferred out: $");
    addTransaction(toIndex, "Transferred in: $");

    cout << "\n==========================================\n";
    cout << " *** TRANSFER SUCCESSFUL! ***\n";
    cout << "==========================================\n";
    cout << "Amount Transferred: $" << amount << "\n";
    cout << "From: " << accountHolders[fromIndex] << "\n";
    cout << " New Balance: $" << balances[fromIndex] << "\n";
    cout << "To: " << accountHolders[toIndex] << "\n";
    cout << " New Balance: $" << balances[toIndex] << "\n";
    cout << "==========================================\n";
}

// Function to view transaction history
void viewTransactionHistory() {
    int accNum;
    cout << "\n==========================================\n";
    cout << "      TRANSACTION HISTORY\n";
    cout << "==========================================\n";
    cout << "Enter Account Number: ";
    cin >> accNum;

    int index = findAccount(accNum);

    if (index == -1) {
        cout << "\n*** ACCOUNT NOT FOUND! ***\n";
        return;
    }

    if (!validatePassword(index)) {
        return;
    }

    cout << "\nAccount Holder: " << accountHolders[index] << "\n";
    cout << "Total Transactions: " << transactionCount[index] << "\n";
    displayLine();

    if (transactionCount[index] == 0) {
        cout << "No transactions yet.\n";
        return;
    }

    for (int i = 0; i < transactionCount[index]; i++) {
        cout << (i + 1) << ". " << transactionHistory[index][i] << "\n";
    }
    displayLine();
}

// Function to search account
void searchAccount() {
    cout << "\n==========================================\n";
    cout << "      SEARCH ACCOUNT\n";
    cout << "==========================================\n";
    cout << "1. Search by Account Number\n";
    cout << "2. Search by Account Holder Name\n";
    cout << "Enter choice: ";

    int choice;
    cin >> choice;

    if (choice == 1) {
        int accNum;
        cout << "Enter Account Number: ";
        cin >> accNum;

        int index = findAccount(accNum);
        if (index != -1) {
            displayAccountDetails(index);
        }
        else {
            cout << "\n*** ACCOUNT NOT FOUND! ***\n";
        }
    }
    else if (choice == 2) {
        string name;
        cout << "Enter Account Holder Name: ";
        cin.ignore();
        getline(cin, name);

        bool found = false;
        for (int i = 0; i < totalAccounts; i++) {
            if (accountHolders[i].find(name) != string::npos) {
                displayAccountDetails(i);
                found = true;
            }
        }

        if (!found) {
            cout << "\n*** NO MATCHING ACCOUNTS FOUND! ***\n";
        }
    }
    else {
        cout << "\n*** Invalid choice! ***\n";
    }
}

// Function to modify account
void modifyAccount() {
    int accNum;
    cout << "\n==========================================\n";
    cout << "      MODIFY ACCOUNT\n";
    cout << "==========================================\n";
    cout << "Enter Account Number: ";
    cin >> accNum;

    int index = findAccount(accNum);

    if (index == -1) {
        cout << "\n*** ACCOUNT NOT FOUND! ***\n";
        return;
    }

    cout << "\nCurrent Details:\n";
    displayAccountDetails(index);

    cin.ignore();
    cout << "\nEnter New Account Holder Name: ";
    getline(cin, accountHolders[index]);

    cout << "Enter New Account Type: ";
    getline(cin, accountTypes[index]);

    cout << "Enter New Contact Number: ";
    getline(cin, contactNumbers[index]);

    cout << "\n*** ACCOUNT MODIFIED SUCCESSFULLY! ***\n";
}

// Function to delete account
void deleteAccount() {
    int accNum;
    cout << "\n==========================================\n";
    cout << "      DELETE ACCOUNT\n";
    cout << "==========================================\n";
    cout << "WARNING: This action cannot be undone!\n";
    displayLine();
    cout << "Enter Account Number to Delete: ";
    cin >> accNum;

    int index = findAccount(accNum);

    if (index == -1) {
        cout << "\n*** ACCOUNT NOT FOUND! ***\n";
        return;
    }

    cout << "\nAccount to be deleted:\n";
    cout << "Account Holder: " << accountHolders[index] << "\n";
    cout << "Balance: $" << balances[index] << "\n";
    cout << "\nAre you sure? (y/n): ";
    char confirm;
    cin >> confirm;

    if (confirm != 'y' && confirm != 'Y') {
        cout << "\nDeletion cancelled.\n";
        return;
    }

    // Shift all accounts after deleted account
    for (int i = index; i < totalAccounts - 1; i++) {
        accountNumbers[i] = accountNumbers[i + 1];
        accountHolders[i] = accountHolders[i + 1];
        accountTypes[i] = accountTypes[i + 1];
        contactNumbers[i] = contactNumbers[i + 1];
        balances[i] = balances[i + 1];
        passwords[i] = passwords[i + 1];
    }

    totalAccounts--;
    cout << "\n*** ACCOUNT DELETED SUCCESSFULLY! ***\n";
}

// Function to calculate interest
void calculateInterest() {
    cout << "\n==========================================\n";
    cout << "      CALCULATE INTEREST\n";
    cout << "==========================================\n";

    double interestRate;
    cout << "Enter Interest Rate (%): ";
    cin >> interestRate;

    cout << "\nInterest will be applied to all accounts.\n";
    displayLine();

    for (int i = 0; i < totalAccounts; i++) {
        double interest = (balances[i] * interestRate) / 100;
        balances[i] += interest;
        cout << "Account " << accountNumbers[i] << ": Interest added $" << interest << "\n";
    }

    cout << "\n*** INTEREST CALCULATED AND ADDED! ***\n";
}

// Function to display bank statistics
void displayBankStatistics() {
    if (totalAccounts == 0) {
        cout << "\n*** NO DATA AVAILABLE! ***\n";
        return;
    }

    double totalBalance = 0;
    double maxBalance = balances[0];
    double minBalance = balances[0];

    for (int i = 0; i < totalAccounts; i++) {
        totalBalance += balances[i];
        if (balances[i] > maxBalance) maxBalance = balances[i];
        if (balances[i] < minBalance) minBalance = balances[i];
    }

    double avgBalance = totalBalance / totalAccounts;

    cout << "\n==========================================\n";
    cout << "      BANK STATISTICS\n";
    cout << "==========================================\n";
    cout << "Total Accounts: " << totalAccounts << "\n";
    cout << "Total Bank Balance: $" << totalBalance << "\n";
    cout << "Average Balance: $" << avgBalance << "\n";
    cout << "Highest Balance: $" << maxBalance << "\n";
    cout << "Lowest Balance: $" << minBalance << "\n";
    cout << "==========================================\n";
}

// Function to change password
void changePassword() {
    int accNum;
    cout << "\n==========================================\n";
    cout << "      CHANGE PASSWORD\n";
    cout << "==========================================\n";
    cout << "Enter Account Number: ";
    cin >> accNum;

    int index = findAccount(accNum);

    if (index == -1) {
        cout << "\n*** ACCOUNT NOT FOUND! ***\n";
        return;
    }

    if (!validatePassword(index)) {
        return;
    }

    string newPass;
    cout << "Enter New Password: ";
    cin >> newPass;

    passwords[index] = newPass;
    cout << "\n*** PASSWORD CHANGED SUCCESSFULLY! ***\n";
}

// Function to display top accounts by balance
void displayTopAccounts() {
    if (totalAccounts == 0) {
        cout << "\n*** NO ACCOUNTS AVAILABLE! ***\n";
        return;
    }

    // Create temporary arrays for sorting
    int tempAccNum[MAX_ACCOUNTS];
    string tempHolders[MAX_ACCOUNTS];
    double tempBalances[MAX_ACCOUNTS];

    // Copy data
    for (int i = 0; i < totalAccounts; i++) {
        tempAccNum[i] = accountNumbers[i];
        tempHolders[i] = accountHolders[i];
        tempBalances[i] = balances[i];
    }

    // Simple bubble sort
    for (int i = 0; i < totalAccounts - 1; i++) {
        for (int j = 0; j < totalAccounts - i - 1; j++) {
            if (tempBalances[j] < tempBalances[j + 1]) {
                // Swap balances
                double tempBal = tempBalances[j];
                tempBalances[j] = tempBalances[j + 1];
                tempBalances[j + 1] = tempBal;

                // Swap account numbers
                int tempAcc = tempAccNum[j];
                tempAccNum[j] = tempAccNum[j + 1];
                tempAccNum[j + 1] = tempAcc;

                // Swap holders
                string tempHolder = tempHolders[j];
                tempHolders[j] = tempHolders[j + 1];
                tempHolders[j + 1] = tempHolder;
            }
        }
    }

    cout << "\n==========================================\n";
    cout << "      TOP ACCOUNTS BY BALANCE\n";
    cout << "==========================================\n";

    int displayCount = (totalAccounts < 5) ? totalAccounts : 5;

    for (int i = 0; i < displayCount; i++) {
        cout << "\n#" << (i + 1) << "\n";
        cout << "Account Number: " << tempAccNum[i] << "\n";
        cout << "Account Holder: " << tempHolders[i] << "\n";
        cout << "Balance: $" << tempBalances[i] << "\n";
        displayLine();
    }
}
void sortAccountsByBalance() {
    if (totalAccounts <= 1) {
        return; // Nothing to sort
    }

    // Bubble sort based on balances (descending)
    for (int i = 0; i < totalAccounts - 1; i++) {
        for (int j = 0; j < totalAccounts - i - 1; j++) {
            if (balances[j] < balances[j + 1]) {

                // Swap balances
                double tempBalance = balances[j];
                balances[j] = balances[j + 1];
                balances[j + 1] = tempBalance;

                // Swap account numbers
                int tempAccNum = accountNumbers[j];
                accountNumbers[j] = accountNumbers[j + 1];
                accountNumbers[j + 1] = tempAccNum;

                // Swap account holders
                string tempHolder = accountHolders[j];
                accountHolders[j] = accountHolders[j + 1];
                accountHolders[j + 1] = tempHolder;

                // Swap account types
                string tempType = accountTypes[j];
                accountTypes[j] = accountTypes[j + 1];
                accountTypes[j + 1] = tempType;

                // Swap contact numbers
                string tempContact = contactNumbers[j];
                contactNumbers[j] = contactNumbers[j + 1];
                contactNumbers[j + 1] = tempContact;

                // Swap passwords
                string tempPass = passwords[j];
                passwords[j] = passwords[j + 1];
                passwords[j + 1] = tempPass;

                // Swap creation dates
                int tempDay = accountCreationDay[j];
                int tempMonth = accountCreationMonth[j];
                int tempYear = accountCreationYear[j];

                accountCreationDay[j] = accountCreationDay[j + 1];
                accountCreationMonth[j] = accountCreationMonth[j + 1];
                accountCreationYear[j] = accountCreationYear[j + 1];

                accountCreationDay[j + 1] = tempDay;
                accountCreationMonth[j + 1] = tempMonth;
                accountCreationYear[j + 1] = tempYear;

                // Swap transaction counts
                int tempTransCount = transactionCount[j];
                transactionCount[j] = transactionCount[j + 1];
                transactionCount[j + 1] = tempTransCount;

                // Swap transaction history
                for (int k = 0; k < 50; k++) {
                    string tempTrans = transactionHistory[j][k];
                    transactionHistory[j][k] = transactionHistory[j + 1][k];
                    transactionHistory[j + 1][k] = tempTrans;
                }
            }
        }
    }
}
