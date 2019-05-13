#include "DB_Holder.h"

#include <chrono>
#include <thread>
#include <QDebug>


DB_Holder::DB_Holder()
{
	//std::this_thread::sleep_for(std::chrono::milliseconds(10000));
}

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

std::pair<QDateTime, QString> DB_Holder::GetTest()
{
	if (!db.isOpen()) 
		if (Connect()) {

			query.exec("SELECT date_time, str from `test` WHERE id = 1");

			last_error = query.lastError().text();

			query.first();

			return std::pair<QDateTime, QString>(query.value(0).toDateTime(), query.value(1).toString());
		}
	return std::pair<QDateTime, QString>(QDateTime::currentDateTime(), "error database connection");
}


DB_Holder::~DB_Holder()
{
	db.close();
}
