#include <iostream>
#include <string>
#include <fstream>
#include "Account.h"
using namespace std;

Account::Account(int id, string name, double bal, bool frozen)
{
    // Constructor to initialize account details
    accountNumber = id;
    accountHolderName = name;
    balance = bal;
    isFrozen = frozen;
}

void Account::printBalance()
{
    // Prints the current balance of the account
    if (isFrozen)
    {
        cout << "Account for " << accountHolderName << " is frozen." << endl;
        return;
    }
    cout << accountHolderName << " has $" << balance << endl;
}

void Account::depositIntoAccount(double depositAmt)
{
    // Deposits amount into the account
    if (isFrozen)
    {
        cout << "Account for " << accountHolderName << " is frozen. Deposit denied." << endl;
        return;
    }
    balance += depositAmt;
    cout << depositAmt << " deposited into account for " << accountHolderName << endl;
}

void Account::withdrawFromAccount(double withDrawAmt)
{
    // Withdraws amount from the account
    if (withDrawAmt > balance)
    {
        cout << "Warning! " << accountHolderName << " doesn't have enough money!" << endl;
    }
    else if (isFrozen)
    {
        cout << "Account for " << accountHolderName << " is frozen. Withdrawal denied." << endl;
    }
    else
    {
        balance -= withDrawAmt;
        cout << withDrawAmt << " withdrawn from " << accountHolderName << endl;
    }
}

void Account::freezeAccount()
{
    // Freezes the account
    isFrozen = true;
    cout << "Account for " << accountHolderName << " is now frozen." << endl;
}

void Account::unFreezeAccount()
{
    // Unfreezes the account
    isFrozen = false;
    cout << "Account for " << accountHolderName << " is now unfrozen." << endl;
}

void Account::saveAccountInfoToFile()
{
    // Saves account information to a file
    ofstream outFile("accounts.txt", ios::app);
    if (outFile.is_open())
    {
        outFile << accountNumber << ","
                << accountHolderName << ","
                << balance << ","
                << isFrozen << endl;
        outFile.close();
        cout << "Account information saved for " << accountHolderName << endl;
    }
}

void Account::printAccountDetails()
{
    // Prints all account details
    cout << "Account Number: " << accountNumber << endl;
    cout << "Account Holder Name: " << accountHolderName << endl;
    cout << "Balance: $" << balance << endl;
    cout << "Account Status: " << (isFrozen ? "Frozen" : "Active") << endl;
}

/* Getters */
int Account::getAccountNumber()
{
    return accountNumber;
}

int Account::getAccountId()
{
    return accountNumber;
}

std::string Account::getAccountHolderName()
{
    return accountHolderName;
}

double Account::getBalance()
{
    return balance;
}

bool Account::getisFrozen()
{
    return isFrozen;
}
