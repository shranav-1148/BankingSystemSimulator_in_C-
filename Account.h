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
    void depositIntoAccount(double depositAmt);
    void withdrawFromAccount(double withDrawAmt);
    void freezeAccount();
    void unFreezeAccount();
};

#endif