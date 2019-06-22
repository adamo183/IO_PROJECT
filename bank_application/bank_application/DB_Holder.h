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
	DB_Holder();
	~DB_Holder();

	bool Connect();
	bool Login(QString *name, QString *Pass,account *user);
	void close() { db.close(); };

	void SetLastError(QString err) { last_error = err; }
	QString GetLastError() { return last_error; };
	QSqlDatabase & getDB() { return db; }

	bool downloadMlModel();
	bool downloadCreditConditions();
	QString getMlModel() const { return mlModel; }
	QString getCreditCondtions() const { return credit_conditions; };

};

