#include "Transfer.h"
#include "account.h"
#include "DB_Holder.h"

bool Transfer::correctNumber(const QString & number)
{
	int k[9], S = 0;
	/*
		7 6 5 4 2 2 6 5 k1 k2 k3 k4 k5 k6 k7 k8 k9 i1 i2 i3 i4 i5 i6 i7 i8 i9
		First 8 digits const for polibank
		k1, k2, ..., k9 control digits
		i1, i2, ..., i9 user id number

		S = sum(i1, i2, ...m i9)
		k_j = S % (j + 1)
			j = 1, 2, ..., 9
	*/

	if (number.size() != 26)
		return false;

	for (int i = 8; i < 26; ++i) {
		int tmp = number.toStdString()[i] - '0';
		if (i < 17)
			k[i - 8] = tmp;
		else
			S += tmp;
	}

	for (int i = 0; i < 9; ++i) {
		if (k[i] != (S % (i + 2)))
			return false;
	}

	return true;
}

QString Transfer::QuickTransfer(
	DB_Holder * db, 
	account * user, 
	double amount, 
	const QString & number, 
	const QString & title, 
	QString receiver_name, 
	QString receiver_address
) {
	QString ans;

	if (!correctNumber(number))
		ans = "Wrong account number!";
	else if (amount > user->getAccBalance()) {
		ans = "You've got no money to do this transaction...";
	}
	else if (!db->Connect()) {
		ans = db->GetLastError();
	}
	else {

		QSqlQuery query(db->getDB());

		bool download_receiver_data = receiver_name.isEmpty();

		QString columns = (download_receiver_data ? "Id_Uzytkow, Imie, Nazwisko, Adres" : "Id_Uzytkow");
		query.exec("SELECT " + columns + " FROM UZYTKOWNIK WHERE Nr_Rachunku LIKE '" + number + "'");

		if (query.size() != 1) {
			ans = "There is no user with such an account number!";
		}
		else {

			query.first();

			QString receiver_id = query.value(0).toString();
			QString amount_str = QString::number(amount);
			if (download_receiver_data) {
				receiver_name = query.value(1).toString() + " " + query.value(2).toString();
				receiver_address = query.value(3).toString();
			}

			QString req =
				"SET SESSION TRANSACTION ISOLATION LEVEL SERIALIZABLE;\n"
				"INSERT INTO TRANSAKCJE (Nr_Rach_Nad, Nr_Rach_Odb, Kwota, Tytul, Nazw_Odb, Adres_Odb) "
				"VALUES('" + user->getAccNumber() + "', '" + number + "', " + amount_str + ", '" + title + "', '" + receiver_name + "', '" + receiver_adress + "');\n"
				"UPDATE UZYTKOWNIK SET Stan_Konta = Stan_Konta + " + amount_str + " WHERE Id_Uzytkow = " + receiver_id + ";\n"
				"UPDATE UZYTKOWNIK SET Stan_Konta = Stan_Konta - " + amount_str + " WHERE Id_Uzytkow = " + QString::number(user->getUserId()) + ";\n"
				"COMMIT;";

			if (query.exec(req)) {
				ans = "Successfully transferred $" + amount_str + " to " + receiver_name + "!\nThank you!";
			}
			else {
				ans = query.lastError().text();
			}
		}
	}

	//db->close();

	return ans;
}

QString Transfer::TakeCredit(
	DB_Holder * db, 
	account * user, 
	double amount, 
	double interest, 
	int duration
) {
	QString ans;

	if (!db->Connect()) {
		ans = db->GetLastError();
	}
	else {

		auto addMscToDate = [](int msc, QDate date = QDate::currentDate(), QString format = "yyyy.MM.dd")->QString {
			int tmp = date.month() + msc;
			return QDate::fromString(
				(
					QString::number(date.year() + (tmp / 12) - (((tmp % 12) == 0) ? 1 : 0)) + "." +
					QString::number(((tmp % 12) == 0 ? 12 : (tmp % 12))) + "." +
					QString::number(date.day())
					),
				"yyyy.M.d").toString(format);
		};

		QSqlQuery query(db->getDB());

		QString data_beg = QDate::currentDate().toString("yyyy.MM.dd");
		QString data_end = addMscToDate(duration);
		QString a_str = QString::number(amount);
		QString i_str = QString::number(interest);

		QString req =
			"SET SESSION TRANSACTION ISOLATION LEVEL SERIALIZABLE;\n"
			"\n"
			"INSERT INTO KREDYTY (Data_Pocz, Data_Koni, Kwota, Oprocent) VALUES('" + data_beg + "', '" + data_end + "', " + a_str + ", " + i_str + ");\n"
			"UPDATE UZYTKOWNIK SET\n"
			"	Stan_Konta = Stan_Konta + " + a_str + ",\n"
			"	Id_Kredyt = (SELECT Id_Kredyt FROM KREDYTY ORDER BY Id_Kredyt DESC LIMIT 1)\n"
			"WHERE Id_Uzytkow = " + QString::number(user->getUserId()) + ";\n"
			"UPDATE UZYTKOWNIK SET Stan_Konta = Stan_Konta - " + a_str + " WHERE Id_Uzytkow = '76542265111111111000000001';\n"
			"INSERT INTO TRANSAKCJE (Nr_Rach_Nad, Nr_Rach_Odb, Kwota, Tytul, Nazw_Odb, Adres_Odb)\n"
			"VALUES(\n"
			"	'76542265111111111000000001',\n"
			"	'" + user->getAccNumber() + "',\n"
			"	" + a_str + ",\n"
			"	'Credit with " + i_str + "% ratio of interests',\n"
			"	'" + user->getName() + " " + user->getSurrname() + "',\n"
			"	'" + user->getAdress() + "'\n"
			");\n"
			"SELECT Id_Kredyt FROM UZYTKOWNIK WHERE Id_Uzytkow=" + QString::number(user->getUserId()) + ";\n"
			"COMMIT;";

		if (query.exec(req)) {
			ans = "Congratulation!\n You got $ " + a_str + " of credit.";
		}
		else {
			ans = query.lastError().text();
		}
	}

	//db->close();

	return ans;
}
