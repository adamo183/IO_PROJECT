#pragma once
#include <QString>

class account;
class DB_Holder;


/**
* Klasa realizująca operacje przelewów, oraz brania kredytu.
*/
class Transfer
{
	static bool correctNumber(const QString & number);
public:

	/** Statyczna metoda wykonująca przelew.
	*	@param db - obiekt bazy danych.
	*	@param user - obiekt użytkownika.
	*	@param amount - kwota przelewu.
	*	@param number - numer odbiory przelewu.
	*	@param title - tytuł przelewu.
	*	@param receiver_name - nazwa odbiorcy.
	*	@param receiver_address - adres odbiorcy.
	*	@return Informacja o przebiegu realizacji transakcji.
	*/
	static QString QuickTransfer(
		DB_Holder * db, 
		account * user, 
		double amount, 
		const QString & number, 
		const QString & title, 
		QString receiver_name = "", 
		QString receiver_address = ""
	);

	/** Statyczna matoda dodająca kredyt użytkownikowi.
	*	@param db - obiekt bazy danych.
	*	@param user - obiekt użytkownika.
	*	@param amount - kwota kredytu.
	*	@param interest - oprocentowanie.
	*	@param duration - okres kredytowania w miesiącach.
	*	@return Informacja o przebigu zaciągania kredytu.
	*/
	static QString TakeCredit(
		DB_Holder * db,
		account * user,
		double amount,
		double interest,
		int duration
	);

};

