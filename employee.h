#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include "human.h"
class Employee : public Human
{
private:
    QString position;
    double salary;

public:
    Employee();
    Employee(
        int id, QString fName, QString lName, QString phoneNumber, QString position, double salary);

    QString getPosition();
    double getSalary();
};

#endif // EMPLOYEE_H
