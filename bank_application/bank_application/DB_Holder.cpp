#include "DB_Holder.h"
#include "account.h"


DB_Holder::DB_Holder()
{
	db = QSqlDatabase::addDatabase("QMYSQL");
	db.setHostName("mn16.webd.pl");
	db.setPort(3306);
	db.setUserName("slavek_io_proj");
	db.setPassword("io_proj@2019");
	db.setDatabaseName("slavek_io");

	last_connection_timestamp = timer.now();
}

DB_Holder::~DB_Holder()
{
	db.close();
}

bool DB_Holder::Connect()
{
	auto period_ms = std::chrono::duration_cast<std::chrono::milliseconds>(timer.now() - last_connection_timestamp).count();

	if (period_ms > 60000)
		db.close();

	bool success = (db.isOpen()? true : db.open());
	if (success) last_connection_timestamp = timer.now();

	last_error = db.lastError().text();
	return success;
}

bool DB_Holder::Login(QString *name,QString *pass,account* user)
{
	bool success = false;
	
	QString pass_f = QString::fromStdString(md5(pass->toStdString()));
	
	int u_id;
	
	if (Connect())
	{
		QSqlQuery query(db);

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
		last_error = db.lastError().text();
	}		


	return success;
}

bool DB_Holder::downloadMlModel()
{
	bool success = false;

	if (Connect()) {
		QSqlQuery query(db);

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

	return success;
}

bool DB_Holder::downloadCreditConditions()
{
	bool success = false;

	if (Connect()) {
		QSqlQuery query(db);

		query.exec("SELECT `Regula` FROM `REG_KREDYT` ORDER BY `Id` DESC LIMIT 1");

		if (query.size() == 1) {
			query.first();
			credit_conditions = query.value(0).toString();

			success = true;
		}
		else {
			last_error = query.lastError().text();
		}

	}
	else {
		last_error = db.lastError().text();
	}

	return success;
}

