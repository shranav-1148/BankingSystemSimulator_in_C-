#include <iostream>
#include <string>
#include <fstream>
#include "Account.h"
using namespace std;

Account::Account(int id, string name, double bal, bool frozen)
{
    accountNumber = id;
    accountHolderName = name;
    balance = bal;
    isFrozen = frozen;
}

void Account::printBalance()
{
    if (isFrozen)
    {
        cout << "Account for " << accountHolderName << " is frozen." << endl;
        return;
    }
    cout << accountHolderName << " has $" << balance << endl;
}

void Account::depositIntoAccount(double depositAmt)
{
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
    isFrozen = true;
    cout << "Account for " << accountHolderName << " is now frozen." << endl;
}

void Account::unFreezeAccount()
{
    isFrozen = false;
    cout << "Account for " << accountHolderName << " is now unfrozen." << endl;
}