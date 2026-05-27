#include "client.h"

Client::Client()
    : Human(0, "", "", "")
{}
Client::Client(int id, QString fName, QString lName, QString phoneNumber)
    : Human(id, fName, lName, phoneNumber)
{}
void Client::addCar(Car &newCar)
{
    ownerCar.append(newCar); //append додає елемент в кінець списку QList
}
QList<Car> Client::getCars()
{
    return ownerCar;
}