#pragma once

#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QString>
#include <QDateTime>
#include "md5.h"
#include "account.h"
class account;

class DB_Holder
{
	QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
	QSqlQuery query;

	QString last_error = "";
	std::pair<QDateTime, QString> test;

public:
	DB_Holder() {};
	~DB_Holder();

	bool Connect();
	bool Login(QString *name, QString *Pass,account *user);

	QString GetLastError() { return last_error; };
	QSqlDatabase getDB() { return db; }
	void SetLastError(QString lastErr) { last_error = lastErr; }

	// test table
	bool DownloadTest();
	std::pair<QDateTime, QString> GetTest();
};

