#include "human.h"

Human::Human()
    : id(0)
    , fName("")
    , lName("")
    , phoneNumber("")
{}
Human::Human(int id, QString fName, QString lName, QString phoneNumber)
    : id(id)
    , fName(fName)
    , lName(lName)
    , phoneNumber(phoneNumber)
{}

int Human::getId()
{
    return id;
}
QString Human::getFname()
{
    return fName;
}
QString Human::getLname()
{
    return lName;
}
QString Human::getPhoneNumber()
{
    return phoneNumber;
}