#include <iostream>
#include "Transaction.h"
#include <fstream>
using namespace std;

Transaction::Transaction(int fromId, int toId, double amount, string timestamp, string type)
{
    this->fromId = fromId;
    this->toId = toId;
    this->amount = amount;
    this->timestamp = timestamp;
    this->type = type;
}

void Transaction::printTransactionDetails()
{
    cout << "Transaction Details:" << endl;
    cout << "From Account ID: " << fromId << endl;
    cout << "To Account ID: " << toId << endl;
    cout << "Amount: $" << amount << endl;
    cout << "Timestamp: " << timestamp << endl;
    cout << "Type: " << type << endl;
}

int Transaction::getFromId()
{
    return fromId;
}

int Transaction::getToId()
{
    return toId;
}

double Transaction::getAmount()
{
    return amount;
}
string Transaction::getTimestamp()
{
    return timestamp;
}

string Transaction::getType()
{
    return type;
}

void Transaction::saveTransactionToFile(string filename)
{
    ofstream outFile(filename, ios::app);
    if (outFile.is_open())
    {
        outFile << fromId << "," << toId << "," << amount << "," << timestamp << "," << type << endl;
        outFile.close();
    }
}
