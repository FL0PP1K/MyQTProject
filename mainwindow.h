#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include "databasemanager.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr, DatabaseManager *dbManager = nullptr);
    ~MainWindow() override;

private slots:

    void on_orderButton_clicked();

    void on_clientsButton_clicked();

    void on_storageButton_clicked();

    void on_employeeButton_clicked();

    void on_pushButtonStorageAdd_clicked();

    void on_pushButtonStorageDelete_clicked();

    void on_pushButtonEmployeeAdd_clicked();

    void on_pushButtonEmployeeDelete_clicked();

    void on_pushButtonClientAdd_clicked();

    void on_pushButtonClientDelete_clicked();

private:
    Ui::MainWindow *ui;
    DatabaseManager *dbManager;

    void setupStorageModel();
    void setupEmployeeModel();
    void setupClientModel();
    void setupOrderModel();

    QSqlTableModel *storageModel; //QSqlTableModel для 1 таблиці
    QSqlTableModel *employeeModel;
    QSqlQueryModel *clientModel; //QSqlQueryModel для обєднання 2 таблиць(join)
    QSqlQueryModel *orderModel;
};
#endif // MAINWINDOW_H
