#pragma once
#include <QString>

class account;
class DB_Holder;

class Transfer
{
	static bool correctNumber(const QString & number);
public:
	static QString QuickTransfer(
		DB_Holder * db, 
		account * user, 
		double amount, 
		const QString & number, 
		const QString & title, 
		QString receiver_name = "", 
		QString receiver_adress = ""
	);
	static QString TakeCredit(
		DB_Holder * db,
		account * user,
		double amount,
		double interest,
		int duration
	);

};

