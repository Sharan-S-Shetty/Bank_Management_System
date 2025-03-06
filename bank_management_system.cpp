#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Account {
public:
    string accountNumber;
    string name;
    double balance;

    void createAccount() {
        cout << "Enter Account Number: ";
        cin >> accountNumber;
        cout << "Enter Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter Initial Balance: ";
        cin >> balance;
        cout << "Account Created Successfully!" << endl;
    }

    void displayAccount() {
        cout << "Account Number: " << accountNumber << endl;
        cout << "Name: " << name << endl;
        cout << "Balance: " << balance << endl;
    }

    void deposit(double amount) {
        balance += amount;
        cout << "Amount Deposited Successfully!" << endl;
    }

    void withdraw(double amount) {
        if (amount > balance) {
            cout << "Insufficient Balance!" << endl;
        } else {
            balance -= amount;
            cout << "Amount Withdrawn Successfully!" << endl;
        }
    }
};

void saveAccount(Account acc) {
    ofstream outFile("accounts.dat", ios::binary | ios::app);
    outFile.write(reinterpret_cast<char*>(&acc), sizeof(Account));
    outFile.close();
}

void displayAllAccounts() {
    Account acc;
    ifstream inFile("accounts.dat", ios::binary);
    if (!inFile) {
        cout << "File could not be opened!" << endl;
        return;
    }
    while (inFile.read(reinterpret_cast<char*>(&acc), sizeof(Account))) {
        acc.displayAccount();
        cout << "------------------------" << endl;
    }
    inFile.close();
}

int main() {
    int choice;
    Account acc;
    while (true) {
        cout << "1. Create Account" << endl;
        cout << "2. Display All Accounts" << endl;
        cout << "3. Deposit" << endl;
        cout << "4. Withdraw" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                acc.createAccount();
                saveAccount(acc);
                break;
            case 2:
                displayAllAccounts();
                break;
            case 3:
                cout << "Enter Account Number: ";
                cin >> acc.accountNumber;
                cout << "Enter Deposit Amount: ";
                double depositAmount;
                cin >> depositAmount;
                acc.deposit(depositAmount);
                break;
            case 4:
                cout << "Enter Account Number: ";
                cin >> acc.accountNumber;
                cout << "Enter Withdraw Amount: ";
                double withdrawAmount;
                cin >> withdrawAmount;
                acc.withdraw(withdrawAmount);
                break;
            case 5:
                exit(0);
            default:
                cout << "Invalid Choice!" << endl;
        }
    }
    return 0;
}