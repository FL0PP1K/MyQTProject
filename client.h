#ifndef CLIENT_H
#define CLIENT_H
#include <QList>
#include "car.h"
#include "human.h"
class Client : public Human
{
private:
    QList<Car> ownerCar; //Динамічний масив QT

public:
    Client();
    Client(int id, QString fName, QString lName, QString phoneNumber);

    void addCar(Car &newCar);
    QList<Car> getCars();
};

#endif // CLIENT_H