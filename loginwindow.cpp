#include "loginwindow.h"
#include <QMessageBox>
#include <QSqlQuery>
#include "ui_loginwindow.h"

LoginWindow::LoginWindow(QDialog *parent, DatabaseManager *dbManager)
    : QDialog(parent)
    , ui(new Ui::LoginWindow)
    , dbManager(dbManager)
{
    ui->setupUi(this);
    dbManager->createUsersTable();
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_loginButton_clicked()
{
    QString username = ui->usernameLine->text();
    QString password = ui->passwordLine->text();
    if (dbManager->Login(username, password)) {
        accept();
    } else {
        QMessageBox::warning(this, "Помилка", "Невірний логін або пароль");
    }
}
