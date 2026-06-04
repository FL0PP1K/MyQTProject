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

    bool createCarTable();
    bool addCar(Car &car);
    bool deleteCar(int id);

    bool createStorageTable();
    bool addPart(Storage &part);
    bool deletePart(int id);

    bool createEmployeeTable();
    bool addEmployee(Employee &employee);
    bool deleteEmployee(int id);

    bool createClientTable();
    bool addClient(Client &client);
    bool deleteClient(int id);

    bool createOrderTable();
};

#endif // DATABASEMANAGER_H
