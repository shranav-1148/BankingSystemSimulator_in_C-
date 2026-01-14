#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <ctime>
#include <sstream>
#include "Account.h"
#include "Transaction.h"
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

void loadTransactionFromFile(vector<Transaction> &transactions)
{
    ifstream inFile("transactions.txt");

    if (!inFile)
    {
        cout << "No existing transactions found." << endl;
        return;
    }
    else
    {
        int fromId, toId;
        double amount;
        string timestamp, type;
        string line;
        while (getline(inFile, line))
        {
            stringstream ss(line);
            string fromIdStr, toIdStr, amountStr, timestamp, type;

            getline(ss, fromIdStr, ',');
            getline(ss, toIdStr, ',');
            getline(ss, amountStr, ',');
            getline(ss, timestamp, ',');
            getline(ss, type, ',');

            int fromId = stoi(fromIdStr);
            int toId = stoi(toIdStr);
            double amount = stod(amountStr);

            transactions.emplace_back(fromId, toId, amount, timestamp, type);
        }
        inFile.close();
        cout << "Loaded " << transactions.size() << " transactions from file." << endl;
    }
}

void updateAccountInFile(Account &updated)
{
    // Based on any updates to account updates the accounts file
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
        cout << "4. View Transactions" << endl;
        cout << "5. Exit" << endl;
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
                    cout << "3. Transfer Money" << endl;
                    cout << "4. Freeze Account" << endl;
                    cout << "5. Unfreeze Account" << endl;
                    cout << "6. Print Account Details" << endl;
                    cout << "7. Back to Main Menu" << endl;
                    cout << "Select an option: ";
                    cin >> manageChoice;

                    if (manageChoice == 1)
                    {
                        // Deposit
                        double depositAmt;
                        cout << "Enter deposit amount: ";
                        cin >> depositAmt;
                        account.depositIntoAccount(depositAmt);
                        updateAccountInFile(account);
                        Transaction transaction(0, account.getAccountNumber(), depositAmt, to_string(time(0)), "Deposit");
                        transaction.saveTransactionToFile("transactions.txt");
                    }
                    else if (manageChoice == 2)
                    {
                        // Withdraw
                        double withdrawAmt;
                        cout << "Enter withdrawal amount: ";
                        cin >> withdrawAmt;
                        account.withdrawFromAccount(withdrawAmt);
                        updateAccountInFile(account);

                        Transaction transaction(account.getAccountNumber(), 0, withdrawAmt, to_string(time(0)), "Withdraw");
                        transaction.saveTransactionToFile("transactions.txt");
                    }

                    else if (manageChoice == 3)
                    {
                        // Transfer Money
                    }
                    else if (manageChoice == 4)
                    {
                        // Freeze Account
                        account.freezeAccount();
                        updateAccountInFile(account);
                    }
                    else if (manageChoice == 5)
                    {
                        // Unfreeze Account
                        account.unFreezeAccount();
                        updateAccountInFile(account);
                    }
                    else if (manageChoice == 6)
                    {
                        // Print Account Details
                        account.printAccountDetails();
                    }
                    else if (manageChoice == 7)
                    {
                        // Back to Main Menu
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
            vector<Transaction> transactions;
            loadTransactionFromFile(transactions);
            for (Transaction &trans : transactions)
            {
                cout << "------------------------" << endl;
                trans.printTransactionDetails();
                cout << "------------------------" << endl;
            }
        }

        else if (choice == 5)
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