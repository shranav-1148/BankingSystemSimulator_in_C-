#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include "Account.h"
using namespace std;

vector<Account> loadAccountsFromFile()
{
    vector<Account> accounts;
    ifstream inFile("accounts.txt");
    if (!inFile)
    {
        cout << "No existing accounts found." << endl;
        return accounts;
    }
    else
    {
        int id;
        string name;
        double bal;
        bool frozen;
        string line;
        while (getline(inFile, line))
        {
            stringstream ss(line);
            string idStr, name, balStr, frozenStr;

            getline(ss, idStr, ',');
            getline(ss, name, ',');
            getline(ss, balStr, ',');
            getline(ss, frozenStr, ',');

            int id = stoi(idStr);
            double bal = stod(balStr);
            bool frozen = stoi(frozenStr);

            accounts.emplace_back(id, name, bal, frozen);
        }
        inFile.close();
        cout << "Loaded " << accounts.size() << " accounts from file." << endl;
        return accounts;
    }
}

int main()
{
    bool endProgram = false;

    while (true)
    {
        cout << "\tWelcome to the Bank Program!" << endl;
        cout << "\t==========================" << endl;
        cout << "1. Create Account" << endl;
        cout << "2. View Accounts" << endl;
        cout << "3. Manage Account" << endl;
        cout << "4. Exit" << endl;
        cout << "Please select an option: ";

        int choice;
        cin >> choice;

        if (choice == 1)
        {
            int accountId;
            string accountHolderName;
            double initialBalance;
            bool isFrozen;

            cout << "Enter Account ID: ";
            cin >> accountId;
            cout << "Enter Account Holder Name: ";
            cin >> accountHolderName;
            cout << "Enter Initial Balance: ";
            cin >> initialBalance;
            cout << "Is the account frozen? (1 for Yes, 0 for No): ";
            cin >> isFrozen;
            Account newAccount(accountId, accountHolderName, initialBalance, isFrozen);
            cout << "Account created successfully!" << endl;

            newAccount.saveAccountInfoToFile();
        }
        else if (choice == 2)
        {
            vector<Account> accounts = loadAccountsFromFile();
            for (Account account : accounts)
            {
                cout << "------------------------" << endl;
                account.printAccountDetails();
                cout << "------------------------" << endl;
            }
        }
        else if (choice == 3)
        {
            // Account management logic can be implemented here
            cout << "Account management feature is under development." << endl;
        }
        else if (choice == 4)
        {
            cout << "Exiting the program. Goodbye!" << endl;
            break;
        }
        else
        {
            cout << "Invalid option. Please try again." << endl;
        }
    }

    return 0;
}