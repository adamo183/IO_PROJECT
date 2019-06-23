#pragma once

#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QString>
#include <QDateTime>
#include <QDebug>
#include <chrono>
#include "md5.h"
#include "account.h"

class account;

class DB_Holder
{
	QSqlDatabase db;

	QString last_error = "";
	QString mlModel, credit_conditions;

	std::chrono::high_resolution_clock timer;
	decltype(timer.now()) last_connection_timestamp;
	
public:
	/** Konstruktor ustawiający parametry połączenia z bazą danych.
	*/
	DB_Holder();
	/** Destruktor zamykający połączenie z bazą danych.
	*/
	~DB_Holder();

	/** Metoda nawiązująca połączenie z bazą danych.
	*	@return true - połączenie zostało nawiązane poprawnie, false - wystąpił błąd.
	*/
	bool Connect();

	/** Metoda walidująca logi i hasło użytkownika.
	*	@param name - Login użytkownika.
	*	@param Pass - Hasło użytkownika.
	*	@param user - obiekt reprezentujący użytkownika.
	*	@return true - użytkownik podał prawidłowy login oraz hasło, false - dane są błędne
	*/
	bool Login(QString *name, QString *Pass,account *user);

	/** Metoda zamykająca połączenie z bazą danych.
	*/
	void close() { db.close(); };

	/** Getter.
	*	@return Ostatni błąd jaki wystąpił.
	*/
	QString GetLastError() { return last_error; };

	/** Getter.
	*	@return Obiekt bazy danych.
	*/
	QSqlDatabase & getDB() { return db; }

	/** Metoda pobierająca model uczenia maszynowago z bazy danych.
	*	@return true - pobierania zakończone sukcesem, false - wystąpłi błąd.
	*/
	bool downloadMlModel();

	/** Matode pobierająca regulamin kredytu.
	*	@return true - pobierania zakończone sukcesem, false - wystąpłi błąd.
	*/
	bool downloadCreditConditions();

	/** Getter.
	*	@return Model uczenia maszynowego.
	*/
	QString getMlModel() const { return mlModel; }

	/** Getter.
	*	@return Regulamin kredytu.
	*/
	QString getCreditCondtions() const { return credit_conditions; };
};

