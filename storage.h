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
    Storage(int id, QString name, QString article, int quantity, double price, QString provider);

    int getId() const;
    QString getName() const;
    QString getArticle() const;
    int getQuantity() const;
    double getPrice() const;
    QString getProvider() const;
};

#endif // STORAGE_H