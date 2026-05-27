#include "databasemanager.h"
DatabaseManager::DatabaseManager()
{
    if (!QSqlDatabase::contains("qt_sql_default_connection")) {
        QSqlDatabase::addDatabase("QSQLITE");
    }
}

DatabaseManager::~DatabaseManager()
{
    if (db.isOpen()) {
        db.close();
    }
}

bool DatabaseManager::connectToDatabase(QString dbName)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbName);

    if (!db.open()) {
        qDebug() << "Помилка підключення до БД:" << db.lastError().text();
        return false;
    }
    return true;
}

bool DatabaseManager::Login(QString username, QString password)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM users WHERE username = :username AND password = :password");
    query.bindValue(":username", username);
    query.bindValue(":password", password);
    if (query.exec()) {
        return query.next();
    }
    return false;
}

//USERS
bool DatabaseManager::createUsersTable()
{
    QSqlQuery query;
    QString createStr = "CREATE TABLE IF NOT EXISTS Users ("
                        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                        "username TEXT NOT NULL,"
                        "password TEXT NOT NULL)";
    if (!query.exec(createStr)) {
        qDebug() << "Помилка створення таблиці:" << query.lastError().text();
        return false;
    }
    query.exec("SELECT COUNT(*) FROM Users");
    if (query.next() && query.value(0).toInt() == 0) {
        query.prepare("INSERT INTO Users (username, password) VALUES (:username, :password)");
        query.bindValue(":username", "admin");
        query.bindValue(":password", "1234");
        if (!query.exec()) {
            qDebug() << "Помилка додавання користувача:" << query.lastError().text();
            return false;
        }
    }
    return true;
}

//STORAGE
bool DatabaseManager::createStorageTable()
{
    QSqlQuery query;
    QString createStr = "CREATE TABLE IF NOT EXISTS Storage ("
                        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                        "name TEXT NOT NULL,"
                        "article TEXT UNIQUE NOT NULL,"
                        "quantity INTEGER NOT NULL,"
                        "price REAL NOT NULL,"
                        "provider TEXT)";
    if (!query.exec(createStr)) {
        qDebug() << "Помилка створення таблиці:" << query.lastError().text();
        return false;
    }
    return true;
}
bool DatabaseManager::addPart(Storage &part)
{
    QSqlQuery query;
    query.prepare("INSERT INTO storage (name,article,quantity,price,provider)"
                  "VALUES (:name, :article, :quantity, :price, :provider)");
    query.bindValue(":name", part.getName());
    query.bindValue(":article", part.getArticle());
    query.bindValue(":quantity", part.getQuantity());
    query.bindValue(":price", part.getPrice());
    query.bindValue(":provider", part.getProvider());
    if (!query.exec()) {
        qDebug() << "Помилка створення таблиці:" << query.lastError().text();
        return false;
    }
    return true;
}
bool DatabaseManager::deletePart(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM storage WHERE id= :id");
    query.bindValue(":id", id);
    return query.exec();
}

//CLIENT
bool DatabaseManager::createClientTable()
{
    QSqlQuery query;
    QString createStr = "CREATE TABLE IF NOT EXISTS Client ("
                        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                        "first_name TEXT NOT NULL,"
                        "last_name TEXT NOT NULL,"
                        "phoneNumber TEXT UNIQUE NOT NULL)";
    if (!query.exec(createStr)) {
        qDebug() << "Помилка створення таблиці:" << query.lastError().text();
        return false;
    }
    return true;
}
bool DatabaseManager::addClientWithCar(Client &client, Car &car)
{
    QSqlQuery query;
    query.prepare("INSERT INTO Client (first_name, last_name, phoneNumber) "
                  "VALUES (:first_name, :last_name, :phoneNumber)");
    query.bindValue(":first_name", client.getFname());
    query.bindValue(":last_name", client.getLname());
    query.bindValue(":phoneNumber", client.getPhoneNumber());
    if (!query.exec()) {
        qDebug() << "Помилка Клієнт:" << query.lastError().text();
        return false;
    }
    int newOwnerId = query.lastInsertId().toInt();
    query.prepare("INSERT INTO Car (brand, model, owner_id) "
                  "VALUES (:brand, :model, :owner_id)");
    query.bindValue(":brand", car.getBrand());
    query.bindValue(":model", car.getModel());
    query.bindValue(":owner_id", newOwnerId);

    if (!query.exec()) {
        qDebug() << "Помилка Машина:" << query.lastError().text();
        return false;
    }
    return true;
}
bool DatabaseManager::deleteClient(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM Car WHERE owner_id = :id");
    query.bindValue(":id", id);
    if (!query.exec()) {
        qDebug() << "Помилка видалення авто:" << query.lastError().text();
        return false;
    }
    query.prepare("DELETE FROM Client WHERE id = :id");
    query.bindValue(":id", id);
    if (!query.exec()) {
        qDebug() << "Помилка видалення клієнта:" << query.lastError().text();
        return false;
    }
    return true;
}

//CAR
bool DatabaseManager::createCarTable()
{
    QSqlQuery query;
    QString createStr = "CREATE TABLE IF NOT EXISTS Car ("
                        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                        "brand TEXT NOT NULL, "
                        "model TEXT NOT NULL, "
                        "owner_id INTEGER NOT NULL, "
                        "FOREIGN KEY(owner_id) REFERENCES Client(id))";

    if (!query.exec(createStr)) {
        qDebug() << "Помилка створення таблиці Car:" << query.lastError().text();
        return false;
    }
    return true;
}

//EMPLOYEE
bool DatabaseManager::createEmployeeTable()
{
    QSqlQuery query;
    QString createStr = "CREATE TABLE IF NOT EXISTS Employee ("
                        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                        "first_name TEXT NOT NULL,"
                        "last_name TEXT NOT NULL,"
                        "phoneNumber TEXT UNIQUE NOT NULL,"
                        "position TEXT NOT NULL,"
                        "salary REAL NOT NULL)";
    if (!query.exec(createStr)) {
        qDebug() << "Помилка створення таблиці:" << query.lastError().text();
        return false;
    }
    return true;
}

bool DatabaseManager::addEmployee(Employee &emp)
{
    QSqlQuery query;
    query.prepare("INSERT INTO Employee (first_name, last_name, phoneNumber, position, salary) "
                  "VALUES (:first_name,:last_name,:phoneNumber,:position,:salary)");
    query.bindValue(":first_name", emp.getFname());
    query.bindValue(":last_name", emp.getLname());
    query.bindValue(":phoneNumber", emp.getPhoneNumber());
    query.bindValue(":position", emp.getPosition());
    query.bindValue(":salary", emp.getSalary());

    return query.exec();
}
bool DatabaseManager::deleteEmployee(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM Employee WHERE id= :id");
    query.bindValue(":id", id);
    return query.exec();
}
//ORDER
bool DatabaseManager::createOrderTable()
{
    QSqlQuery query;
    QString createStr = "CREATE TABLE IF NOT EXISTS Orders ("
                        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                        "car_id INTEGER,"
                        "employee_id INTEGER,"
                        "description TEXT NOT NULL,"
                        "order_date TEXT,"
                        "status TEXT,"
                        "total_price REAL,"
                        "FOREIGN KEY(car_id) REFERENCES Car(id),"
                        "FOREIGN KEY(employee_id) REFERENCES Employee(id))";
    if (!query.exec(createStr)) {
        qDebug() << "Помилка створення таблиці:" << query.lastError().text();
        return false;
    }
    return true;
}