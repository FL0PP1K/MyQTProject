#ifndef ORDER_H
#define ORDER_H
#include <QDate>
#include <QString>
class Order
{
private:
    int id;
    int carId;
    int employeeId;
    QString description;
    QDate orderDate;
    QString status;
    double totalPrice;

public:
    Order();
    Order(int id,
          int carId,
          int employeeId,
          QString description,
          QDate orderDate,
          QString status,
          double totalPrice);

    int getId();
    int getCarId();
    int getEmployeeId();
    QString getDescription();
    QDate getOrderDate();
    QString getStatus();
    double getTotalPrice();

    void setStatus(QString newStatus);
    void setTotalPrice(double newTotalPrice);
};

#endif // ORDER_H
