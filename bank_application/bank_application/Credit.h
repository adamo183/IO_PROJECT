#pragma once

#include <QString>

class Credit
{
	const QString ml_model;
	double amount, salary;
	int age, duration;

public:
	Credit(const QString & ml_model) : ml_model(ml_model) {};
	void setVals(int age, double salary, double amount, int duration);
	bool isAbleToGetCredit();
};

