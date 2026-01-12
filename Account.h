#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>

class Account
{
private:
    int accountNumber;
    double balance;
    bool isFrozen;
    std::string accountHolderName;

public:
    Account(int id, std::string name, double bal, bool frozen);

    void printBalance();
    int getAccountNumber();
    void printAccountDetails();
    void depositIntoAccount(double depositAmt);
    void withdrawFromAccount(double withDrawAmt);
    void freezeAccount();
    void unFreezeAccount();
    void saveAccountInfoToFile();

    int getAccountId();
    std::string getAccountHolderName();
    double getBalance();
    bool getisFrozen();
};

#endif