#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Account {
protected:
    string accountNumber;
    string name;
    double balance;

public:
    Account(string accNum, string accName, double accBalance)
        : accountNumber(accNum), name(accName), balance(accBalance) {}

    virtual void deposit(double amount) {
        balance += amount;
    }

    virtual bool withdraw(double amount) {
        if (amount > balance) {
            cout << "Insufficient balance!\n";
            return false;
        }
        balance -= amount;
        return true;
    }

    virtual void display() const {
        cout << "Account Number: " << accountNumber << "\n"
             << "Name: " << name << "\n"
             << "Balance: " << balance << "\n";
    }

    string getAccountNumber() const { return accountNumber; }
    double getBalance() const { return balance; }
};

class SavingsAccount : public Account {
private:
    double interestRate;

public:
    SavingsAccount(string accNum, string accName, double accBalance, double rate)
        : Account(accNum, accName, accBalance), interestRate(rate) {}

    void applyInterest() {
        balance += balance * (interestRate / 100);
    }
};

class CurrentAccount : public Account {
public:
    CurrentAccount(string accNum, string accName, double accBalance)
        : Account(accNum, accName, accBalance) {}
};

class Bank {
private:
    vector<Account*> accounts;

public:
    void createAccount() {
        string accNum, name;
        double balance;
        int type;
        cout << "Enter Account Number: "; cin >> accNum;
        cout << "Enter Name: "; cin >> name;
        cout << "Enter Initial Balance: "; cin >> balance;
        cout << "Choose Account Type (1. Savings 2. Current): "; cin >> type;

        if (type == 1) {
            double rate;
            cout << "Enter Interest Rate (%): "; cin >> rate;
            accounts.push_back(new SavingsAccount(accNum, name, balance, rate));
        } else {
            accounts.push_back(new CurrentAccount(accNum, name, balance));
        }
        cout << "Account Created Successfully!\n";
    }

    void depositMoney() {
        string accNum;
        double amount;
        cout << "Enter Account Number: "; cin >> accNum;
        for (auto acc : accounts) {
            if (acc->getAccountNumber() == accNum) {
                cout << "Enter Amount to Deposit: "; cin >> amount;
                acc->deposit(amount);
                cout << "Deposit Successful!\n";
                return;
            }
        }
        cout << "Account not found!\n";
    }

    void withdrawMoney() {
        string accNum;
        double amount;
        cout << "Enter Account Number: "; cin >> accNum;
        for (auto acc : accounts) {
            if (acc->getAccountNumber() == accNum) {
                cout << "Enter Amount to Withdraw: "; cin >> amount;
                if (acc->withdraw(amount)) {
                    cout << "Withdrawal Successful!\n";
                }
                return;
            }
        }
        cout << "Account not found!\n";
    }

    void displayAccounts() {
        for (auto acc : accounts) {
            acc->display();
            cout << "------------------\n";
        }
    }
};

int main() {
    Bank bank;
    int choice;
    do {
        cout << "\nBank Management System";
        cout << "\n1. Create Account";
        cout << "\n2. Deposit Money";
        cout << "\n3. Withdraw Money";
        cout << "\n4. Display Accounts";
        cout << "\n5. Exit";
        cout << "\nEnter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: bank.createAccount(); break;
            case 2: bank.depositMoney(); break;
            case 3: bank.withdrawMoney(); break;
            case 4: bank.displayAccounts(); break;
            case 5: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 5);

    return 0;
}
