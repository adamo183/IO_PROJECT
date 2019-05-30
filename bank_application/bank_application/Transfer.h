#pragma once
#include <QString>

class account;
class DB_Holder;

class Transfer
{
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

};

