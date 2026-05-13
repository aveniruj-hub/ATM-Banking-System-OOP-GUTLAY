#include <iostream>
#include <fstream>
#include <vector>
using namespace std;


class Account {
private:
    int id;
    string name;
    string pin;
    double balance;

public:
    Account(int i, string n, string p, double b) {
        id = i;
        name = n;
        pin = p;
        balance = b;
    }

    string getName() { return name; }
    string getPin() { return pin; }

    void checkBalance() {
        cout << "Current Balance: " << balance << endl;
    }

    void deposit(double amount) {
        balance += amount;
        cout << "Deposit successful!\n";
    }

    void withdraw(double amount) {
        if (amount > balance) {
            cout << "Insufficient balance!\n";
        } else {
            balance -= amount;
            cout << "Withdrawal successful!\n";
        }
    }

    void changePin(string newPin) {
        pin = newPin;
        cout << "PIN successfully changed!\n";
    }

    void display() {
        cout << id << " " << name << " " << pin << " " << balance << endl;
    }

    
    int getId() { return id; }
    double getBalance() { return balance; }
};


vector<Account> loadAccounts() {
    vector<Account> accounts;
    ifstream file("accounts.txt");

    int id;
    string name, pin;
    double balance;

    while (file >> id >> name >> pin >> balance) {
        accounts.push_back(Account(id, name, pin, balance));
    }

    file.close();
    return accounts;
}


void saveAccounts(vector<Account>& accounts) {
    ofstream file("accounts.txt");

    for (auto& acc : accounts) {
        file << acc.getId() << " "
             << acc.getName() << " "
             << acc.getPin() << " "
             << acc.getBalance() << endl;
    }

    file.close();
}


int main() {
    vector<Account> accounts = loadAccounts();

    string name, pin;
    cout << "=== ATM LOGIN ===\n";
    cout << "Enter Name: ";
    cin >> name;
    cout << "Enter PIN: ";
    cin >> pin;

    Account* current = nullptr;

   
    for (auto& acc : accounts) {
        if (acc.getName() == name && acc.getPin() == pin) {
            current = &acc;
            break;
        }
    }

    if (current == nullptr) {
        cout << "Invalid login!\n";
        return 0;
    }

    cout << "\nLogin successful!\n";

    int choice;
    do {
        cout << "\n=== ATM MENU ===\n";
        cout << "1. Check Balance\n";
        cout << "2. Deposit\n";
        cout << "3. Withdraw\n";
        cout << "4. Change PIN\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            current->checkBalance();
            break;

        case 2: {
            double amount;
            cout << "Enter amount: ";
            cin >> amount;
            current->deposit(amount);
            saveAccounts(accounts);
            break;
        }

        case 3: {
            double amount;
            cout << "Enter amount: ";
            cin >> amount;
            current->withdraw(amount);
            saveAccounts(accounts);
            break;
        }

        case 4: {
            string newPin;
            cout << "Enter new PIN: ";
            cin >> newPin;
            current->changePin(newPin);
            saveAccounts(accounts);
            break;
        }
        
        case 5:
            listAccounts(accounts);
            
            break;

        case 6:
            cout << "Thank you for using ATM!\n";
            break;

        default:
            cout << "Invalid choice!\n";
        }

    } while (choice != 5);

    return 0;
}
