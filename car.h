#ifndef CAR_H
#define CAR_H
#include <QString>
class Car
{
protected:
    int id;
    int ownerId;
    QString brand;
    QString model;
    QString licensePlate;
    int year;

public:
    Car();
    Car(int id, int ownerId, QString brand, QString model, QString licensePlate, int year);

    int getId();
    int getOwnerId();
    QString getBrand();
    QString getModel();
    QString getLicensePlate();
    int getYear();
};

#endif // CAR_H