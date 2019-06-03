#include "DB_Holder.h"
#include "account.h"


DB_Holder::DB_Holder()
{
	db.setHostName("mn16.webd.pl");
	db.setPort(3306);
	db.setUserName("slavek_io_proj");
	db.setPassword("io_proj@2019");
	db.setDatabaseName("slavek_io");
	query = QSqlQuery(db);
}

DB_Holder::~DB_Holder()
{
	db.close();
}

bool DB_Holder::Connect()
{
	bool success = false;

	if (!db.isOpen())
		db.open();

	if (db.isOpen()) {
		last_error = db.lastError().text();
		success = true;
	}
	else {
		last_error = db.lastError().text();
	}

	return success;
}



bool DB_Holder::Login(QString *name,QString *pass,account* user)
{
	bool success = false;
	
	QString pass_f = QString::fromStdString(md5(pass->toStdString()));
	
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
			
			success = true;
		}
		else {
			last_error = query.lastError().text();
			if(last_error == ' ')
				last_error = "Invalid username or password!";
		}
	}
	else {
		last_error = query.lastError().text();
	}		
	db.close();

	return success;
}

bool DB_Holder::downloadMlModel()
{
	bool success = false;

	if (Connect()) {

		query.exec("SELECT `Model` FROM `ML_MODEL` ORDER BY `Id` DESC LIMIT 1");

		if (query.size() == 1) {
			query.first();
			mlModel = query.value(0).toString();

			success = true;
		}
		else {
			last_error = query.lastError().text();
		}

	}
	else {
		last_error = db.lastError().text();
	}

	db.close();
	return success;
}

