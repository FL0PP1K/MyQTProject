#include "employee.h"

Employee::Employee()
    : Human(0, "", "", "")
    , position("")
    , salary(0.0)
{}
Employee::Employee(
    int id, QString fName, QString lName, QString phoneNumber, QString position, double salary)
    : Human(id, fName, lName, phoneNumber)
    , position(position)
    , salary(salary)
{}
QString Employee::getPosition()
{
    return position;
}
double Employee::getSalary()
{
    return salary;
}