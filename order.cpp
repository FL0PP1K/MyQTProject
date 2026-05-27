#include "order.h"

Order::Order()
    : id(0)
    , carId(0)
    , employeeId(0)
    , totalPrice(0)
{}
Order::Order(int id,
             int carId,
             int employeeId,
             QString description,
             QDate orderDate,
             QString status,
             double totalPrice)
    : id(id)
    , carId(carId)
    , employeeId(employeeId)
    , description(description)
    , orderDate(orderDate)
    , status(status)
    , totalPrice(totalPrice)
{}

int Order::getId()
{
    return id;
};
int Order::getCarId()
{
    return carId;
};
int Order::getEmployeeId()
{
    return employeeId;
};
QString Order::getDescription()
{
    return description;
};
QDate Order::getOrderDate()
{
    return orderDate;
};
QString Order::getStatus()
{
    return status;
};
double Order::getTotalPrice()
{
    return totalPrice;
};

void Order::setStatus(QString newStatus)
{
    status = newStatus;
};
void Order::setTotalPrice(double newTotalPrice)
{
    totalPrice = newTotalPrice;
};