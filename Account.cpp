#include <iostream>
#include <string>
using namespace std;

class Account
{
private:
    int accountNumber;
    double balance;
    bool isFrozen;
    string accountHolderName;

public:
    Account(int accNum, double bal, string accName)
    {

        accountNumber = accNum;
        balance = bal;
        accountHolderName = accName;
    }

    void printBalance()
    {
        cout << accountHolderName << " has $" << balance << endl;
    }

    void depositIntoAccount(double depositAmt)
    {
        balance += depositAmt;
        cout << depositAmt << " deposited into account with holder name " << accountHolderName << endl;
    }

    void withdrawFromAccount(double withDrawAmt)
    {
        if (withDrawAmt >= balance)
        {
            cout << "Warning! Account Holder " << accountHolderName << " doesn't have enough money to withdraw!" << endl;
        }
        else
        {
            balance -= withDrawAmt;
            cout << withDrawAmt << " withdrawn from account with holder name " << accountHolderName << endl;
        }
    }
};

int main()
{
    Account JohnDoe(1, 1000.0, "John");

    JohnDoe.printBalance();
    JohnDoe.depositIntoAccount(500.76);
    JohnDoe.withdrawFromAccount(1500.76);

    return 0;
};
