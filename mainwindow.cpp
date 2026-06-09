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
        dbManager->createTable();

        setupStorageModel();
        setupEmployeeModel();
        setupClientModel();
        setupCarModel();
        setupOrderModel();

        updateOwnerList();
        updateOrderList();

        ui->comboBoxOrderStatus->clear();
        ui->comboBoxOrderStatus->addItem("Очікує");
        ui->comboBoxOrderStatus->addItem("В роботі");
        ui->comboBoxOrderStatus->addItem("Виконано");
        ui->comboBoxOrderStatus->addItem("Скасовано");
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
    storageModel->setTable("Storage");
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

    Storage newPart(0, name, article, qty, price, provider);
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

void MainWindow::on_pushButtonStorageSearch_clicked()
{
    QString searchTerm = ui->lineEditStorageSearch->text();
    if (searchTerm.isEmpty()) {
        storageModel->setFilter("");
    } else {
        QString filter = QString("name LIKE '%%1%' OR article LIKE '%%1%' OR provider LIKE '%%1%'")
                             .arg(searchTerm);
        storageModel->setFilter(filter);
    }
    storageModel->select();
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
    clientModel->setTable("Client");
    clientModel->select();
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

    if (fName.isEmpty() || phone.isEmpty()) {
        QMessageBox::warning(this, "Помилка", "Ім'я та телефон обов'язкові!");
        return;
    }

    Client newClient(0, fName, lName, phone);
    if (dbManager->addClient(newClient)) {
        clientModel->select();
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
    auto result = QMessageBox::question(
        this,
        "Підтвердження видалення",
        "Видалення клієнта призведе до видалення всіх його автомобілів та замовлень! Продовжити?",
        QMessageBox::Yes | QMessageBox::No);
    if (result == QMessageBox::No)
        return;
    if (dbManager->deleteClient(id)) {
        clientModel->select();
        setupCarModel();
        setupOrderModel();
        updateOwnerList();
        updateOrderList();
    } else {
        QMessageBox::critical(this,
                              "Помилка",
                              "Не вдалося видалити клієнта через обмеження бази даних.");
    }
}

void MainWindow::on_pushButtonClientSearch_clicked()
{
    QString searchTerm = ui->lineEditClientSearch->text();
    if (searchTerm.isEmpty()) {
        clientModel->setFilter("");
    } else {
        QString filter
            = QString("first_name LIKE '%%1%' OR last_name LIKE '%%1%' OR phoneNumber LIKE '%%1%'")
                  .arg(searchTerm);
        clientModel->setFilter(filter);
    }
    clientModel->select();
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
                       "LEFT JOIN Client ON Car.owner_id = Client.id "
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
    ui->tableViewOrders->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    disconnect(ui->tableViewOrders, &QTableView::clicked, nullptr, nullptr);
    connect(ui->tableViewOrders, &QTableView::clicked, this, [this](const QModelIndex &index) {
        int row = index.row();
        int orderId = orderModel->data(orderModel->index(row, 0)).toInt();

        QSqlQuery query;
        query.prepare("SELECT car_id, employee_id, description, status, total_price FROM Orders "
                      "WHERE id = :id");
        query.bindValue(":id", orderId);

        if (query.exec() && query.next()) {
            int carId = query.value(0).toInt();
            int empId = query.value(1).toInt();
            QString desc = query.value(2).toString();
            QString status = query.value(3).toString();
            double price = query.value(4).toDouble();
            int carIdx = ui->comboBoxOrderCar->findData(carId);
            if (carIdx >= 0)
                ui->comboBoxOrderCar->setCurrentIndex(carIdx);

            QSqlQuery clientQuery;
            clientQuery.prepare("SELECT owner_id FROM Car WHERE id = :car_id");
            clientQuery.bindValue(":car_id", carId);
            if (clientQuery.exec() && clientQuery.next()) {
                int clientId = clientQuery.value(0).toInt();
                int clientIdx = ui->comboBoxOrderClient->findData(clientId);
                if (clientIdx >= 0)
                    ui->comboBoxOrderClient->setCurrentIndex(clientIdx);
            }

            int empIdx = ui->comboBoxOrderEmployee->findData(empId);
            if (empIdx >= 0)
                ui->comboBoxOrderEmployee->setCurrentIndex(empIdx);
            ui->lineEditOrderDescription->setText(desc);
            ui->doubleSpinBoxOrderSum->setValue(price);

            int statusIdx = ui->comboBoxOrderStatus->findText(status);
            if (statusIdx >= 0)
                ui->comboBoxOrderStatus->setCurrentIndex(statusIdx);
        }
    });
}
void MainWindow::updateOrderList()
{
    ui->comboBoxOrderEmployee->clear();
    QSqlQuery empQuery("SELECT id, last_name || ' ' || first_name FROM Employee");
    while (empQuery.next()) {
        ui->comboBoxOrderEmployee->addItem(empQuery.value(1).toString(), empQuery.value(0).toInt());
    }

    ui->comboBoxOrderClient->blockSignals(true);
    ui->comboBoxOrderClient->clear();
    QSqlQuery clientQuery("SELECT id, last_name || ' ' || first_name FROM Client");
    while (clientQuery.next()) {
        ui->comboBoxOrderClient->addItem(clientQuery.value(1).toString(),
                                         clientQuery.value(0).toInt());
    }
    ui->comboBoxOrderClient->blockSignals(false);

    disconnect(ui->comboBoxOrderClient,
               qOverload<int>(&QComboBox::currentIndexChanged),
               nullptr,
               nullptr);
    connect(ui->comboBoxOrderClient,
            qOverload<int>(&QComboBox::currentIndexChanged),
            this,
            [this](int index) {
                ui->comboBoxOrderCar->clear();

                int clientId = ui->comboBoxOrderClient->itemData(index).toInt();
                if (clientId <= 0)
                    return;

                QSqlQuery carQuery;
                carQuery.prepare("SELECT id, brand || ' ' || model || ' (' || license_plate || ')' "
                                 "FROM Car WHERE owner_id = :client_id");
                carQuery.bindValue(":client_id", clientId);

                if (carQuery.exec()) {
                    while (carQuery.next()) {
                        ui->comboBoxOrderCar->addItem(carQuery.value(1).toString(),
                                                      carQuery.value(0).toInt());
                    }
                }
            });

    if (ui->comboBoxOrderClient->count() > 0) {
        ui->comboBoxOrderClient->currentIndexChanged(ui->comboBoxOrderClient->currentIndex());
    }
}
void MainWindow::on_pushButtonOrderAdd_clicked()
{
    int carId = ui->comboBoxOrderCar->currentData().toInt();
    int employeeId = ui->comboBoxOrderEmployee->currentData().toInt();

    if (carId <= 0 || employeeId <= 0) {
        QMessageBox::warning(this, "Помилка", "Оберіть автомобіль та майстра!");
        return;
    }

    QString description = ui->lineEditOrderDescription->text();
    double price = ui->doubleSpinBoxOrderSum->value();

    QString status = ui->comboBoxOrderStatus->currentText();
    QString date = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");

    if (description.isEmpty()) {
        QMessageBox::warning(this, "Помилка", "Заповніть опис робіт!");
        return;
    }

    Order newOrder(0, carId, employeeId, description, date, status, price);
    if (dbManager->addOrder(newOrder)) {
        setupOrderModel();
        ui->lineEditOrderDescription->clear();
        ui->doubleSpinBoxOrderSum->setValue(0.0);
    } else {
        QMessageBox::warning(this, "Помилка", "Не вдалось створити замовлення!");
    }
}
void MainWindow::on_pushButtonOrderUpdate_clicked()
{
    int row = ui->tableViewOrders->currentIndex().row();
    if (row < 0) {
        QMessageBox::information(this, "Увага", "Виберіть замовлення в таблиці для модифікації!");
        return;
    }

    int orderId = orderModel->data(orderModel->index(row, 0)).toInt();
    int carId = ui->comboBoxOrderCar->currentData().toInt();
    int employeeId = ui->comboBoxOrderEmployee->currentData().toInt();
    QString description = ui->lineEditOrderDescription->text();
    QString status = ui->comboBoxOrderStatus->currentText();
    double price = ui->doubleSpinBoxOrderSum->value();

    if (description.isEmpty()) {
        QMessageBox::warning(this, "Помилка", "Опис робіт не може бути порожнім!");
        return;
    }
    if (dbManager->updateOrder(orderId, carId, employeeId, description, status, price)) {
        setupOrderModel();
        QMessageBox::information(this, "Успіх", "Замовлення успішно відредаговано!");
    } else {
        QMessageBox::warning(this, "Помилка", "Не вдалося оновити дані в базі!");
    }
}
void MainWindow::on_pushButtonOrderDelete_clicked()
{
    int row = ui->tableViewOrders->currentIndex().row();
    if (row < 0) {
        QMessageBox::information(this, "Увага", "Виберіть замовлення, яке бажаєте видалити!");
        return;
    }

    int id = orderModel->data(orderModel->index(row, 0)).toInt();
    auto result = QMessageBox::question(this,
                                        "Підтвердження",
                                        "Ви дійсно хочете видалити це замовлення з історії?",
                                        QMessageBox::Yes | QMessageBox::No);

    if (result == QMessageBox::Yes) {
        if (dbManager->deleteOrder(id)) {
            setupOrderModel();
        } else {
            QMessageBox::warning(this, "Помилка", "Не вдалося видалити замовлення!");
        }
    }
}
//ТАБЛИЦЯ CAR
void MainWindow::setupCarModel()
{
    carModel = new QSqlQueryModel(this);
    QString queryStr = "SELECT "
                       "Car.id, "
                       "Client.last_name || ' ' || Client.first_name AS Owner, "
                       "Car.brand, "
                       "Car.model, "
                       "Car.license_plate, "
                       "Car.year "
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
void MainWindow::on_pushButtonCarAdd_clicked()
{
    QString brand = ui->lineEditCarBrand->text();
    QString model = ui->lineEditCarModel->text();
    QString plate = ui->lineEditCarLicencePlate->text();
    int year = ui->spinBoxCarYear->value();
    int ownerId = ui->comboBoxCar->currentData().toInt();

    if (brand.isEmpty() || model.isEmpty() || plate.isEmpty()) {
        QMessageBox::warning(this, "Помилка", "Марка, модель та номерний знак обов'язкові!");
        return;
    }

    Car newCar(0, ownerId, brand, model, plate, year);
    if (dbManager->addCar(newCar)) {
        setupCarModel();
        updateOrderList();
        ui->lineEditCarBrand->clear();
        ui->lineEditCarModel->clear();
        ui->lineEditCarLicencePlate->clear();
        ui->spinBoxCarYear->setValue(2000);
        ui->comboBoxCar->setCurrentIndex(0);
    } else {
        QMessageBox::warning(this, "Помилка", "Не вдалось додати автомобіль!");
    }
}
void MainWindow::on_pushButtonCarDelete_clicked()
{
    int row = ui->tableViewCar->currentIndex().row();
    if (row < 0) {
        QMessageBox::information(this, "Увага", "Виберіть рядок для видалення");
        return;
    }

    int id = carModel->data(carModel->index(row, 0)).toInt();
    if (dbManager->deleteCar(id)) {
        setupCarModel();
        setupOrderModel();
        updateOrderList();
    }
}
void MainWindow::updateOwnerList()
{
    ui->comboBoxCar->clear();
    QSqlQuery query("SELECT id, last_name || ' ' || first_name FROM Client");

    while (query.next()) {
        ui->comboBoxCar->addItem(query.value(1).toString(), query.value(0).toInt());
    }
}
