#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
using namespace std;

class Transaction
{
private:
    int fromId;
    int toId;
    double amount;
    string timestamp;
    string type;

public:
    Transaction(int fromId, int toId, double amount, string timestamp, string type);

    void printTransactionDetails();
    int getFromId();
    int getToId();
    double getAmount();
    string getTimestamp();
    string getType();
    void saveTransactionToFile(string filename);
};

#endif