#ifndef POMOTUXEXCEPTION_H
#define POMOTUXEXCEPTION_H
#include <QString>
#include <iostream>
#include <cstring>
using namespace std;

class PomotuxException
{
    QString Message;
public:
    PomotuxException(string message);
    QString getMessage();
    void setMessage(string newMessage);
};

#endif // POMOTUXEXCEPTION_H
