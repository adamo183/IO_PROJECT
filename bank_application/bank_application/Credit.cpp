#include "Credit.h"

void Credit::setVals(int age, double salary, double amount, int duration)
{
	this->age = age;
	this->salary = salary;
	this->amount = amount;
	this->duration = duration;
}

bool Credit::isAbleToGetCredit()
{
	return true;
}