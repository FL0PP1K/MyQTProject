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
        setupCarModel();
        setupOrderModel();
        updateOwnerList();
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

void MainWindow::on_carButton_clicked()
{
    ui->tabWidget->setCurrentIndex(2);
}

void MainWindow::on_storageButton_clicked()
{
    ui->tabWidget->setCurrentIndex(3);
}

void MainWindow::on_employeeButton_clicked()
{
    ui->tabWidget->setCurrentIndex(4);
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
    ui->tableViewStorage->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
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
    ui->tableViewEmployee->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
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
    clientModel = new QSqlTableModel(this);
    QString queryStr = "SELECT id, first_name, last_name, phoneNumber FROM Client";

    clientModel->setQuery(queryStr);
    clientModel->setHeaderData(0, Qt::Horizontal, "ID");
    clientModel->setHeaderData(1, Qt::Horizontal, "Ім'я");
    clientModel->setHeaderData(2, Qt::Horizontal, "Прізвище");
    clientModel->setHeaderData(3, Qt::Horizontal, "Телефон");

    ui->tableViewClient->setModel(clientModel);
    ui->tableViewClient->hideColumn(0);
    ui->tableViewClient->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void MainWindow::on_pushButtonClientAdd_clicked()
{
    QString fName = ui->lineEditClientFirstName->text();
    QString lName = ui->lineEditClientLastName->text();
    QString phone = ui->lineEditClientPhone->text();

    // Перевірка тільки особистих даних
    if (fName.isEmpty() || phone.isEmpty()) {
        QMessageBox::warning(this, "Помилка", "Ім'я та телефон обов'язкові!");
        return;
    }

    Client newClient(0, fName, lName, phone);

    if (dbManager->addClient(newClient)) {
        setupClientModel();
        updateOwnerList();
        ui->lineEditClientFirstName->clear();
        ui->lineEditClientLastName->clear();
        ui->lineEditClientPhone->clear();
    } else {
        QMessageBox::warning(this, "Помилка", "Не вдалось додати клієнта!");
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
    orderModel = new QSqlQueryModel(this);

    QString queryStr = "SELECT "
                       "Orders.id, "
                       "Client.first_name || ' ' || Client.last_name as Owner, "
                       "Car.brand || ' ' || Car.model as CarInfo, "
                       "Employee.first_name || ' ' || Employee.last_name as Master, "
                       "Orders.description, "
                       "Orders.order_date, "
                       "Orders.status, "
                       "Orders.total_price "
                       "FROM Orders "
                       "LEFT JOIN Car ON Orders.car_id = Car.id "
                       "LEFT JOIN Client ON Car.owner_id = Client.id " // Ось цей зв'язок!
                       "LEFT JOIN Employee ON Orders.employee_id = Employee.id";

    orderModel->setQuery(queryStr);
    orderModel->setHeaderData(0, Qt::Horizontal, "ID");
    orderModel->setHeaderData(1, Qt::Horizontal, "Власник");
    orderModel->setHeaderData(2, Qt::Horizontal, "Автомобіль");
    orderModel->setHeaderData(3, Qt::Horizontal, "Майстер");
    orderModel->setHeaderData(4, Qt::Horizontal, "Опис робіт");
    orderModel->setHeaderData(5, Qt::Horizontal, "Дата");
    orderModel->setHeaderData(6, Qt::Horizontal, "Статус");
    orderModel->setHeaderData(7, Qt::Horizontal, "Сума (грн)");

    ui->tableViewOrders->setModel(orderModel);
    ui->tableViewOrders->hideColumn(0);
    ui->tableViewOrders->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch);
}
//ТАБЛИЦЯ CAR
void MainWindow::setupCarModel()
{
    carModel = new QSqlQueryModel(this);

    QString queryStr = "SELECT "
                       "Car.id, "
                       "Client.last_name || ' ' || Client.first_name AS Owner, "
                       "Car.brand, "
                       "Car.model "
                       "FROM Car "
                       "LEFT JOIN Client ON Car.owner_id = Client.id";

    carModel->setQuery(queryStr);
    carModel->setHeaderData(0, Qt::Horizontal, "ID");
    carModel->setHeaderData(1, Qt::Horizontal, "Власник (Клієнт)");
    carModel->setHeaderData(2, Qt::Horizontal, "Марка авто");
    carModel->setHeaderData(3, Qt::Horizontal, "Модель");
    carModel->setHeaderData(4, Qt::Horizontal, "Номерний знак");
    carModel->setHeaderData(5, Qt::Horizontal, "Рік випуску");

    ui->tableViewCar->setModel(carModel);
    ui->tableViewCar->hideColumn(0);
    ui->tableViewCar->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}
void MainWindow::updateOwnerList()
{
    ui->comboBoxCar->clear();
    QSqlQuery query("SELECT id, last_name || ' ' || first_name FROM Client");

    while (query.next()) {
        ui->comboBoxCar->addItem(query.value(1).toString(), query.value(0).toInt());
    }
}
