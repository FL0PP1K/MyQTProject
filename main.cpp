#include <QApplication>
#include <QDialog>
#include "loginwindow.h"
#include "mainwindow.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DatabaseManager db;
    if (!db.connectToDatabase("ARM_manager_CTO.db")) {
        return -1;
    }
    LoginWindow lw(nullptr, &db);
    if (lw.exec() == QDialog::Accepted) {
        MainWindow w(nullptr, &db);
        w.show();
        return a.exec();
    }
    return 0;
}
