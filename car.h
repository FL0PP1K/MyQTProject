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

public:
    Car();
    Car(int id, int ownerId, QString brand, QString model);

    int getId();
    int getOwnerId();
    QString getBrand();
    QString getModel();
};

#endif // CAR_H