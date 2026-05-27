#include "car.h"

Car::Car()
    : id(0)
    , ownerId(0)
    , brand("")
    , model("")
{}
Car::Car(int id, int ownerId, QString brand, QString model)
    : id(id)
    , ownerId(ownerId)
    , brand(brand)
    , model(model)
{}

int Car::getId()
{
    return id;
}
int Car::getOwnerId()
{
    return ownerId;
}
QString Car::getBrand()
{
    return brand;
}
QString Car::getModel()
{
    return model;
}