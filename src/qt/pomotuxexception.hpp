#ifndef POMOTUXEXCEPTION_H
#define POMOTUXEXCEPTION_H
#include <QString>
#include <iostream>
#include <cstring>
using namespace std;


/**
 * A class for Exceptions thrown by Pomotux Graphical User Interface.
 * It is a simple class made on the specific purpose to save messages to be prompt to the user
 * when something unexpected happens. It automatically converts the string passed to a string
 * compatible with qt (i.e. QString obj type) ready to be used inside a QWidget
 * <br/>
 * e.g. on how to use it:
 * <pre>
 * #include "pomotuxexception.hpp"
 * #include <QMessageBox>
 *
 * int main(void)
 * {
 *    try
 *    {
 *           if(condition_statement) throw PomotuxException("Message");
 *           ...
 *           statements
 *           ...
 *       }catch(PomotuxException e){
 *           QMessageBox msgBox;
 *           msgBox.setText(e.getMessage());
 *           msgBox.exec();
 *       }
 *  }
 * </pre>
 */
class PomotuxException {
    /**
      * QString representing the message of the Exception
      */
    QString Message;
public:
    /**
      * Constructor reads the string type parameter passed, converts it into a QString and assigns it to the internal attribute message
      * @param message a string representing the message of the Exception thrown
      */
    PomotuxException(string message);

    /**
      * Getter for the internal attribute messagge it returns the message in the form of a QString ready to be inserted in a QWidget obj
      * @return a QString containing the message of the Excetpion
      */
    QString getMessage();

    /**
      * Setter for the internal attribute messagge it sets the attribute Message to the newMessage parameter passed as a string
      * @param newMessage a QString containing the message of the Excetpion
      */
    void setMessage(string newMessage);
};

#endif // POMOTUXEXCEPTION_H
