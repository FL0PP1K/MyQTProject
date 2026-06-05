#ifndef HUMAN_H
#define HUMAN_H
#include <QString>
class Human
{
private:
    int id;
    QString fName;
    QString lName;
    QString phoneNumber;

public:
    Human();
    Human(int id, QString fName, QString lName, QString phoneNumber);
    virtual ~Human()= default; //virtual для видалення обєктів похідних класів через вказівник на базовий клас

    int getId() const;
    QString getFname() const;
    QString getLname() const;
    QString getPhoneNumber() const;
};

#endif // HUMAN_H
