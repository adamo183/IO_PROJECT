#pragma once

#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QString>
#include <QDateTime>
#include <QTimer>
#include "md5.h"
#include "account.h"

class account;

class DB_Holder
{
	QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");

	QString last_error = "";
	QString mlModel;
	
public:
	DB_Holder();
	~DB_Holder();

	bool Connect();
	bool Login(QString *name, QString *Pass,account *user);
	void close() { db.close(); };

	QString GetLastError() { return last_error; };
	QSqlDatabase & getDB() { return db; }

	bool downloadMlModel();
	QString getMlModel() const { return mlModel; }

};

