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

int Human::getId() const
{
    return id;
}
QString Human::getFname() const
{
    return fName;
}
QString Human::getLname() const
{
    return lName;
}
QString Human::getPhoneNumber() const
{
    return phoneNumber;
}