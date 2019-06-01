#include "DB_Holder.h"
#include "account.h"
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
		//query = QSqlQuery(db);
		last_error = db.lastError().text();
	}
	else {
		last_error = db.lastError().text();
		return false;
	}

	return true;
}



bool DB_Holder::Login(QString *name,QString *pass,account* user)
{
	
	
	QString pass_f = QString::fromStdString(md5(pass->toStdString()));
	//QSqlQuery query(db);

	
	int u_id;
	
		if (Connect())
		{
			query.exec(("SELECT * FROM `LOGIN` WHERE Nazwa_uz = '"+*name+"' AND Haslo = '"+pass_f+"'"));
			
			if (query.size() == 1)
			{
				query.next();
				u_id = query.value(0).toInt();
				last_error = query.lastError().text();
				user->setUserId(u_id);
				return true;
			}
			else
			{
				last_error = "Invalid username or password!";
				return false;
			}
		}
	

		last_error = query.lastError().text();
		return false;
	
	
	
	
}

bool DB_Holder::downloadMlModel()
{
	if (Connect()) {

		query.exec("SELECT `Model` FROM `ML_MODEL` ORDER BY `Id` DESC LIMIT 1");

		if (query.size() == 1) {
			query.first();
			mlModel = query.value(0).toString();
			return true;
		}
		last_error = query.lastError().text();
		return false;

	}
	last_error = db.lastError().text();
	return false;
}

DB_Holder::~DB_Holder()
{
	db.close();
}
