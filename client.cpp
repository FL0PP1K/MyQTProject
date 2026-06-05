#include "client.h"

Client::Client()
    : Human(0, "", "", "")
{}
Client::Client(int id, QString fName, QString lName, QString phoneNumber)
    : Human(id, fName, lName, phoneNumber)
{}
QString Client::getFullName() const
{
    return getLname() + " " + getFname();
}