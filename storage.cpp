#include "storage.h"

Storage::Storage()
    : id(0)
    , quantity(0)
    , price(0.0)
{}
Storage::Storage(QString name, QString article, int quantity, double price, QString provider)
    : name(name)
    , article(article)
    , quantity(quantity)
    , price(price)
    , provider(provider)
{}

int Storage::getID()
{
    return id;
}
QString Storage::getName()
{
    return name;
}
QString Storage::getArticle()
{
    return article;
}
int Storage::getQuantity()
{
    return quantity;
}
double Storage::getPrice()
{
    return price;
}

QString Storage::getProvider()
{
    return provider;
}
