#pragma once

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

public:
	DB_Holder();
	~DB_Holder();

	bool Connect();
	QString GetLastError() { return last_error; };
	std::pair<QDateTime, QString> GetTest();
};
