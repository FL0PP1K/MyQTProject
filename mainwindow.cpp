#include "mainwindow.h"
#include <QInputDialog>
#include <QMessageBox>
#include <QTabWidget>
#include "./ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent, DatabaseManager *dbManager)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , dbManager(dbManager)
{
    ui->setupUi(this);
    ui->tabWidget->tabBar()->hide();
    if (dbManager) {
        dbManager->createStorageTable();
        dbManager->createClientTable();
        dbManager->createEmployeeTable();
        dbManager->createCarTable();
        dbManager->createOrderTable();
        setupStorageModel();
        setupEmployeeModel();
        setupClientModel();
        setupOrderModel();
    } else {
        QMessageBox::critical(this, "Помилка", "Не вдалось підключитись до бази даних!");
    }
};
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_orderButton_clicked()
{
    ui->tabWidget->setCurrentIndex(0);
}

void MainWindow::on_clientsButton_clicked()
{
    ui->tabWidget->setCurrentIndex(1);
}

void MainWindow::on_storageButton_clicked()
{
    ui->tabWidget->setCurrentIndex(2);
}
void MainWindow::on_employeeButton_clicked()
{
    ui->tabWidget->setCurrentIndex(3);
}

//ТАБЛИЦЯ STORAGE
void MainWindow::setupStorageModel()
{
    storageModel = new QSqlTableModel(this);
    storageModel->setTable("storage");
    storageModel->setEditStrategy(QSqlTableModel::OnFieldChange);
    storageModel->select();

    storageModel->setHeaderData(0, Qt::Horizontal, "ID");
    storageModel->setHeaderData(1, Qt::Horizontal, "Назва");
    storageModel->setHeaderData(2, Qt::Horizontal, "Артикул");
    storageModel->setHeaderData(3, Qt::Horizontal, "Кількість");
    storageModel->setHeaderData(4, Qt::Horizontal, "Ціна");
    storageModel->setHeaderData(5, Qt::Horizontal, "Постачальник");

    ui->tableViewStorage->setModel(storageModel);
    ui->tableViewStorage->hideColumn(0);
}

void MainWindow::on_pushButtonStorageAdd_clicked() //ДОДАВАННЯ ЗАПИСУ
{
    QString name = ui->lineEditName->text();
    QString article = ui->lineEditArticle->text();
    int qty = ui->spinBoxQty->value();
    double price = ui->doubleSpinBoxPrice->value();
    QString provider = ui->lineEditProvider->text();

    if (name.isEmpty() || article.isEmpty()) {
        QMessageBox::warning(this, "Помилка", "Назва та артикул неправильні!");
        return;
    }

    Storage newPart(name, article, qty, price, provider);

    if (dbManager->addPart(newPart)) {
        storageModel->select();

        ui->lineEditName->clear();
        ui->lineEditArticle->clear();
        ui->spinBoxQty->setValue(0);
        ui->doubleSpinBoxPrice->setValue(0.0);
        ui->lineEditProvider->clear();

    } else {
        QMessageBox::warning(this, "Помилка", "Не вдалось додати запис!");
    }
}

void MainWindow::on_pushButtonStorageDelete_clicked() //ВИДАЛЕННЯ ЗАПИСУ
{
    int row = ui->tableViewStorage->currentIndex().row();
    if (row < 0) {
        QMessageBox::information(this, "Увага", "Виберіть рядок для видалення");
        return;
    }

    int id = storageModel->data(storageModel->index(row, 0)).toInt();
    if (dbManager->deletePart(id)) {
        storageModel->select();
    }
}

//ТАБЛИЦЯ EMPLOYEE
void MainWindow::setupEmployeeModel()
{
    employeeModel = new QSqlTableModel(this);
    employeeModel->setTable("Employee");
    employeeModel->setEditStrategy(QSqlTableModel::OnFieldChange);
    employeeModel->select();

    employeeModel->setHeaderData(0, Qt::Horizontal, "ID");
    employeeModel->setHeaderData(1, Qt::Horizontal, "Ім'я");
    employeeModel->setHeaderData(2, Qt::Horizontal, "Прізвище");
    employeeModel->setHeaderData(3, Qt::Horizontal, "Телефон");
    employeeModel->setHeaderData(4, Qt::Horizontal, "Посада");
    employeeModel->setHeaderData(5, Qt::Horizontal, "Зарплата");

    ui->tableViewEmployee->setModel(employeeModel);
    ui->tableViewEmployee->hideColumn(0);
}

void MainWindow::on_pushButtonEmployeeAdd_clicked() //ДОДАВАННЯ ЗАПИСУ
{
    QString fName = ui->lineEditFirstName->text();
    QString lName = ui->lineEditLastName->text();
    QString phone = ui->lineEditPhone->text();
    QString pos = ui->lineEditPosition->text();
    double salary = ui->spinBoxSalary->value();
    if (fName.isEmpty() || lName.isEmpty()) {
        QMessageBox::warning(this, "Помилка", "Ім'я та прізвище обов'язкові!");
        return;
    }
    Employee newEmp(0, fName, lName, phone, pos, salary);
    if (dbManager->addEmployee(newEmp)) {
        employeeModel->select();
        ui->lineEditFirstName->clear();
        ui->lineEditLastName->clear();
        ui->lineEditPhone->clear();
        ui->lineEditPosition->clear();
        ui->spinBoxSalary->setValue(0);
    } else {
        QMessageBox::warning(this, "Помилка", "Не вдалось додати запис!");
    }
}
void MainWindow::on_pushButtonEmployeeDelete_clicked() //ВИДАЛЕННЯ ЗАПИСУ
{
    int row = ui->tableViewEmployee->currentIndex().row();
    if (row < 0) {
        QMessageBox::information(this, "Увага", "Виберіть рядок для видалення");
        return;
    }

    int id = employeeModel->data(employeeModel->index(row, 0)).toInt();
    if (dbManager->deleteEmployee(id)) {
        employeeModel->select();
    }
}

//ТАБЛИЦЯ CLIENT
void MainWindow::setupClientModel()
{
    clientModel = new QSqlQueryModel(this);
    QString queryStr = "SELECT Client.id, Client.first_name, Client.last_name, Client.phoneNumber, "
                       "Car.brand, Car.model "
                       "FROM Client "
                       "LEFT JOIN Car ON Client.id = Car.owner_id";

    clientModel->setQuery(queryStr);
    clientModel->setHeaderData(0, Qt::Horizontal, "ID");
    clientModel->setHeaderData(1, Qt::Horizontal, "Ім'я");
    clientModel->setHeaderData(2, Qt::Horizontal, "Прізвище");
    clientModel->setHeaderData(3, Qt::Horizontal, "Телефон");
    clientModel->setHeaderData(4, Qt::Horizontal, "Марка авто");
    clientModel->setHeaderData(5, Qt::Horizontal, "Модель");

    ui->tableViewClient->setModel(clientModel);
    ui->tableViewClient->hideColumn(0);
}

void MainWindow::on_pushButtonClientAdd_clicked() //ДОДАВАННЯ ЗАПИСУ
{
    QString fName = ui->lineEditClientFirstName->text();
    QString lName = ui->lineEditClientLastName->text();
    QString phone = ui->lineEditClientPhone->text();
    QString brand = ui->lineEditClientBrand->text();
    QString model = ui->lineEditClientModel->text();

    Client newClient(0, fName, lName, phone);
    Car newCar(0, 0, brand, model);

    if (dbManager->addClientWithCar(newClient, newCar)) {
        setupClientModel();

        ui->lineEditClientFirstName->clear();
        ui->lineEditClientLastName->clear();
        ui->lineEditClientPhone->clear();
        ui->lineEditClientBrand->clear();
        ui->lineEditClientModel->clear();
    } else {
        QMessageBox::warning(this, "Помилка", "Не вдалось додати запис!");
    }
}
void MainWindow::on_pushButtonClientDelete_clicked() //ВИДАЛЕННЯ ЗАПИСУ
{
    int row = ui->tableViewClient->currentIndex().row();
    if (row < 0) {
        QMessageBox::information(this, "Увага", "Виберіть рядок для видалення");
        return;
    }

    int id = clientModel->data(clientModel->index(row, 0)).toInt();
    if (dbManager->deleteClient(id)) {
        setupClientModel();
    }
}
//ТАБЛИЦЯ ORDER
void MainWindow::setupOrderModel()
{
    if (!orderModel) {
        orderModel = new QSqlQueryModel(this);
    }

    QString queryStr = "SELECT "
                       "Orders.id, "
                       "Car.brand || ' ' || Car.model as CarInfo, "
                       "Employee.first_name || ' ' || Employee.last_name as Master, "
                       "Orders.description, "
                       "Orders.order_date, "
                       "Orders.status, "
                       "Orders.total_price "
                       "FROM Orders "
                       "LEFT JOIN Car ON Orders.car_id = Car.id "
                       "LEFT JOIN Employee ON Orders.employee_id = Employee.id";

    orderModel->setQuery(queryStr);
    orderModel->setHeaderData(0, Qt::Horizontal, "ID");
    orderModel->setHeaderData(1, Qt::Horizontal, "Автомобіль");
    orderModel->setHeaderData(2, Qt::Horizontal, "Майстер");
    orderModel->setHeaderData(3, Qt::Horizontal, "Опис робіт");
    orderModel->setHeaderData(4, Qt::Horizontal, "Дата");
    orderModel->setHeaderData(5, Qt::Horizontal, "Статус");
    orderModel->setHeaderData(6, Qt::Horizontal, "Сума (грн)");

    ui->tableViewOrders->setModel(orderModel);
    ui->tableViewOrders->hideColumn(0);
    ui->tableViewOrders->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}