#include "account.h"
#include <QString>

void account::setAccData(int u_id, QString nm, QString srnm, QString acc_n, QString pn, QString addr, QString nr_d, int cr_id)
{
	user_id = u_id;
	name = nm;
	surrname = srnm;
	acc_number = acc_n;
	phone_number = pn;
	adress = addr;
	nr_doc = nr_d;
	credit_id = cr_id;

}

int account::getAge() const {

	int age = QDate::currentDate().year() - born_date.year();

	return (born_date.month() > QDate::currentDate().month() ? age - 1 : age);
}

bool account::getUserData(DB_Holder *base)
{
	bool success = false;
	if(base->Connect())		
	{

		QSqlQuery query(base->getDB());
		int u_id = getUserId();
		query.prepare("SELECT * FROM `UZYTKOWNIK` WHERE Id_Uzytkow = :uid");
		query.bindValue(":uid", user_id);

		query.exec(); 

		if (query.size() == 1) {
			query.first();

			name = query.value(1).toString();
			surrname = query.value(2).toString();
			born_date = query.value(3).toDate();
			sex = (query.value(4).toString().toUpper() == "M" ? MALE : FEMALE);
			acc_number = query.value(5).toString();
			acc_balance = query.value(6).toDouble();
			phone_number = query.value(7).toString();
			adress = query.value(8).toString();
			nr_doc = query.value(9).toString();
			credit_id = query.value(10).toInt();

			query.exec("SELECT SUM(KWOTA) FROM DOCHOD WHERE Id_Uzytkow=" + QString::number(u_id) + " GROUP BY Id_Uzytkow");
			if (query.size() == 0) {
				salary_sum = 0;
			}
			else {
				query.first();
				salary_sum = query.value(0).toInt();
			}

			success = true;
		}
		else {
			last_error = query.lastError().text();
		}
	}
	else {
		last_error = base->GetLastError();
	}
	 
	
	base->close();

	return success;
}

bool account::DownloadUserTransactions(DB_Holder * base)
{
	bool success = false;
	if (!base->Connect()) {
		last_error = base->GetLastError();
	}
	else {

		QSqlQuery query(base->getDB());

		QString req =
			"( 	SELECT \n"
			"		t.Id_Trans, \n"
			"		t.DataCzas, \n"
			"		t.Nr_Rach_Nad as Nr_Rach, \n"
			"		t.Kwota, \n"
			"		t.Tytul, \n"
			"		CONCAT(u.Imie, ' ', u.Nazwisko) as Nazwa, \n"
			"		u.Adres as Adres \n"
			"		FROM \n"
			"	TRANSAKCJE t join UZYTKOWNIK u \n"
			"	on t.Nr_Rach_Nad = u.Nr_Rachunku \n"
			"	WHERE t.Nr_Rach_Odb = '" + this->acc_number + "' \n"
			") \n"
			"UNION ALL \n"
			"(	SELECT \n"
			"		t.Id_Trans, \n"
			"		t.DataCzas, \n"
			"		t.Nr_Rach_Odb as Nr_Rach, \n"
			"		t.Kwota * -1 as Kwota, \n"
			"		t.Tytul, \n"
			"		t.Nazw_Odb as Nazwa, \n"
			"		t.Adres_Odb as Adres \n"
			"	FROM TRANSAKCJE t \n"
			"	WHERE t.Nr_Rach_Nad = '" + this->acc_number + "' \n"
			") \n"
			"ORDER BY Id_Trans DESC;";

		query.exec(req);

		if (query.size() == 0) {
			last_error = query.lastError().text();
			if (last_error == ' ')
				last_error = "There is no transactions to be shown!";
		}
		else {
			Transactions.clear();

			while (query.next()) {

				SingleTransaction tmp;
				std::get<Transaction::ID>(tmp) = query.value(Transaction::ID).toInt();
				std::get<Transaction::DATETIME>(tmp) = query.value(Transaction::DATETIME).toDateTime();
				std::get<Transaction::ACC_NO>(tmp) = query.value(Transaction::ACC_NO).toString();
				std::get<Transaction::AMOUNT>(tmp) = query.value(Transaction::AMOUNT).toDouble();
				std::get<Transaction::TITLE>(tmp) = query.value(Transaction::TITLE).toString();
				std::get<Transaction::NAME>(tmp) = query.value(Transaction::NAME).toString();
				std::get<Transaction::ADDRESS>(tmp) = query.value(Transaction::ADDRESS).toString();

				Transactions.push_back(std::move(tmp));
			}

			success = true;
		}
	}
	base->close();

	return success;
}

bool account::DownloadUserJobs(DB_Holder * base)
{
	bool success = false;
	if (!base->Connect()) {
		last_error = base->GetLastError();
	}
	else {

		QSqlQuery query(base->getDB());

		QString req =
			"SELECT \n"
			"	Id_Doch, \n"
			"	Nazwa_Firmy, \n"
			"	Adres_Firmy, \n"
			"	Kwota \n"
			"FROM \n"
			"	DOCHOD \n"
			"WHERE "
			"	 Id_Uzytkow = " + QString::number(this->user_id) + ";\n";

		query.exec(req);

		if (query.size() == 0) {
			last_error = query.lastError().text();
			if (last_error == ' ')
				success = true;
		}
		else {
			Jobs.clear();

			while (query.next()) {

				SingleJob tmp;
				std::get<0>(tmp) = query.value(0).toInt();
				std::get<1>(tmp) = query.value(1).toString();
				std::get<2>(tmp) = query.value(2).toString();
				std::get<3>(tmp) = query.value(3).toDouble();

				Jobs.push_back(std::move(tmp));
			}

			success = true;
		}
	}
	base->close();

	return success;
}
