#ifndef CAR_H
#define CAR_H
#include <QString>
class Car
{
private:
    int id;
    int ownerId;
    QString brand;
    QString model;
    QString licensePlate;
    int year;

public:
    Car();
    Car(int id, int ownerId, QString brand, QString model, QString licensePlate, int year);

    int getId() const;
    int getOwnerId() const;
    QString getBrand() const;
    QString getModel() const;
    QString getLicensePlate() const;
    int getYear();
};

#endif // CAR_H