#ifndef CLIENT_H
#define CLIENT_H
#include <QList>
#include "human.h"
class Client : public Human
{
public:
    Client();
    Client(int id, QString fName, QString lName, QString phoneNumber);

    QString getFullName() const;
};

#endif // CLIENT_H