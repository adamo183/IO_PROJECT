#pragma once

#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QString>
#include <QDateTime>
#include "md5.h"

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
	bool Login(QString *name, QString *Pass);

	QString GetLastError() { return last_error; };

	

	// test table
	bool DownloadTest();
	std::pair<QDateTime, QString> GetTest();
};

