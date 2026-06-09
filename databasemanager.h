#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QString>
#include "car.h"
#include "client.h"
#include "employee.h"
#include "order.h"
#include "storage.h"
class DatabaseManager
{
private:
    QSqlDatabase db;

public:
    DatabaseManager();
    ~DatabaseManager();

    bool connectToDatabase(QString dbName);
    bool Login(QString username, QString password);

    bool createUsersTable();
    bool createTable();

    bool addCar(Car &car);
    bool deleteCar(int id);

    bool addPart(Storage &part);
    bool deletePart(int id);

    bool addEmployee(Employee &employee);
    bool deleteEmployee(int id);

    bool addClient(Client &client);
    bool deleteClient(int id);

    bool addOrder(Order &order);
    bool deleteOrder(int id);

    bool updateOrder(
        int id, int carId, int employeeId, QString description, QString status, double price);
    bool updateOrderStatus(int id, QString newStatus);
};

#endif // DATABASEMANAGER_H
