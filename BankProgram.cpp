#include <iostream>
#include "Account.h"
using namespace std;

int main()
{
    Account JohnDoe(1, "John", 1000.0, false);

    JohnDoe.printBalance();
    JohnDoe.depositIntoAccount(500.76);
    JohnDoe.withdrawFromAccount(1500.76);
    JohnDoe.freezeAccount();
    JohnDoe.depositIntoAccount(100.0);
    JohnDoe.unFreezeAccount();
    JohnDoe.withdrawFromAccount(200.0);
    JohnDoe.printBalance();

    return 0;
}