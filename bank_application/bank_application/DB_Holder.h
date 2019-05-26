#pragma once

#include "account.h"
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QString>
#include <QDateTime>

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

	QString GetLastError() { return last_error; };

	

	// test table
	bool DownloadTest();
	std::pair<QDateTime, QString> GetTest();
};

