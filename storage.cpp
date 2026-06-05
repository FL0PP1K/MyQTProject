#include "storage.h"

Storage::Storage()
    : id(0)
    , name("")
    , article("")
    , quantity(0)
    , price(0.0)
    , provider("")
{}
Storage::Storage(int id,
                 const QString &name,
                 const QString &article,
                 int quantity,
                 double price,
                 const QString &provider)
    : id(id)
    , name(name)
    , article(article)
    , quantity(quantity)
    , price(price)
    , provider(provider)
{}

int Storage::getId() const
{
    return id;
}
QString Storage::getName() const
{
    return name;
}
QString Storage::getArticle() const
{
    return article;
}
int Storage::getQuantity() const
{
    return quantity;
}
double Storage::getPrice() const
{
    return price;
}
QString Storage::getProvider() const
{
    return provider;
}
