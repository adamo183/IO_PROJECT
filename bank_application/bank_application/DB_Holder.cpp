#include "DB_Holder.h"

#include <chrono>
#include <thread>
#include <QDebug>


bool DB_Holder::Connect()
{
	if (db.isOpen())
		return true;
	db.close();
	db.setHostName("mn16.webd.pl");
	db.setPort(3306);
	db.setUserName("slavek_io_proj");
	db.setPassword("io_proj@2019");
	db.setDatabaseName("slavek_io");
	db.open();

	if (db.isOpen()) {
		query = QSqlQuery(db);
		last_error = db.lastError().text();
	}
	else {
		last_error = db.lastError().text();
		return false;
	}

	return true;
}

/* true - ok, false - error */
bool DB_Holder::DownloadTest()
{
	if (!db.isOpen())
		if (Connect()) {

			query.exec("SELECT date_time, str from `test` WHERE id = 1");
			//query.exec("")

			last_error = query.lastError().text();

			query.first();

			if (!query.isValid()) {
				last_error = query.lastError().text();
				return false;
			}

		//	test = std::pair<QDateTime, QString>(query.value(0).toDateTime(), query.value(1).toString());

			return true;
		}
	return false;
}

bool DB_Holder::Login(QString *name,QString *pass)
{
	
	
	QString pass_f = QString::fromStdString(md5(pass->toStdString()));
	
	if (!db.isOpen())
	{
		if (Connect())
		{
			query.exec("SELECT id_uzytkow FROM `LOGIN` WHERE Nazwa_uz = "+*name+" AND Haslo = "+pass);
		}

		if (query.size() != 1)
			return false;
	}
	//to be continued....
	
	
	
	
	return true;
}

std::pair<QDateTime, QString> DB_Holder::GetTest()
{
	return test;
}


DB_Holder::~DB_Holder()
{
	db.close();
}
