#ifndef STORAGE_H
#define STORAGE_H
#include <QString>
class Storage
{
private:
    int id;
    QString name;
    QString article;
    int quantity;
    double price;
    QString provider;

public:
    Storage();
    Storage(QString name, QString article, int quantity, double price, QString provider);

    int getID();
    QString getName();
    QString getArticle();
    int getQuantity();
    double getPrice();
    QString getProvider();
};

#endif // STORAGE_H
