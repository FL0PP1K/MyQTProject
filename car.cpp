#include "car.h"

Car::Car()
    : id(0)
    , ownerId(0)
    , brand("")
    , model("")
    , licensePlate("")
    , year(0)
{}
Car::Car(int id, int ownerId, QString brand, QString model, QString licensePlate, int year)
    : id(id)
    , ownerId(ownerId)
    , brand(brand)
    , model(model)
    , licensePlate(licensePlate)
    , year(year)
{}

int Car::getId() const
{
    return id;
}
int Car::getOwnerId() const
{
    return ownerId;
}
QString Car::getBrand() const
{
    return brand;
}
QString Car::getModel() const
{
    return model;
}
QString Car::getLicensePlate() const
{
    return licensePlate;
}
int Car::getYear()
{
    return year;
}