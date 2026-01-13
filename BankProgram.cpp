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

void updateAccountInFile(Account &updated)
{
    vector<Account> accounts = loadAccountsFromFile();

    bool found = false;
    for (Account &acc : accounts)
    {
        if (acc.getAccountNumber() == updated.getAccountNumber())
        {
            acc = updated;
            found = true;
            break;
        }
    }

    if (!found)
    {
        cout << "Account not found." << endl;
        return;
    }

    ofstream outFile("accounts.txt", ios::trunc);
    for (Account acc : accounts)
    {
        outFile << acc.getAccountNumber() << ","
                << acc.getAccountHolderName() << ","
                << acc.getBalance() << ","
                << acc.getisFrozen() << endl;
    }

    cout << "Account updated successfully." << endl;
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
            cout << "Find Account by ID: ";
            int searchId;
            cin >> searchId;
            vector<Account> accounts = loadAccountsFromFile();
            bool found = false;
            for (Account &account : accounts)
            {
                if (account.getAccountNumber() == searchId)
                {
                    found = true;
                    int manageChoice;
                    cout << "1. Deposit" << endl;
                    cout << "2. Withdraw" << endl;
                    cout << "3. Freeze Account" << endl;
                    cout << "4. Unfreeze Account" << endl;
                    cout << "5. Print Account Details" << endl;
                    cout << "6. Back to Main Menu" << endl;
                    cout << "Select an option: ";
                    cin >> manageChoice;

                    if (manageChoice == 1)
                    {
                        double depositAmt;
                        cout << "Enter deposit amount: ";
                        cin >> depositAmt;
                        account.depositIntoAccount(depositAmt);
                        updateAccountInFile(account);
                    }
                    else if (manageChoice == 2)
                    {
                        double withdrawAmt;
                        cout << "Enter withdrawal amount: ";
                        cin >> withdrawAmt;
                        account.withdrawFromAccount(withdrawAmt);
                        updateAccountInFile(account);
                    }
                    else if (manageChoice == 3)
                    {
                        account.freezeAccount();
                        updateAccountInFile(account);
                    }
                    else if (manageChoice == 4)
                    {
                        account.unFreezeAccount();
                        updateAccountInFile(account);
                    }
                    else if (manageChoice == 5)
                    {
                        account.printAccountDetails();
                    }
                    else if (manageChoice == 6)
                    {
                        break;
                    }
                }
            }
            if (!found)
            {
                cout << "Account with ID " << searchId << " not found." << endl;
            }
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