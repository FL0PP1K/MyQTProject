#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H
#include <QDialog>
#include "databasemanager.h"
namespace Ui {
class LoginWindow;
}

class LoginWindow : public QDialog
{
    Q_OBJECT

public:
    explicit LoginWindow(QDialog *parent = nullptr, DatabaseManager *dbManager = nullptr);
    ~LoginWindow();

private slots:
    void on_loginButton_clicked();

private:
    Ui::LoginWindow *ui;
    DatabaseManager *dbManager;
};

#endif // LOGINWINDOW_H
