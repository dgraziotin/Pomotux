#include "pomotuxexception.hpp"

PomotuxException::PomotuxException(string message)
{
    this->Message= QString(message.c_str());

}

QString PomotuxException::getMessage()
{
    return this->Message;
}

void PomotuxException::setMessage(string newMessage)
{
    this->Message= QString(newMessage.c_str());
}
