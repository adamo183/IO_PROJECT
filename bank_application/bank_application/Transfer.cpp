#include "Transfer.h"
#include "account.h"
#include "DB_Holder.h"

QString Transfer::QuickTransfer(
	DB_Holder * db, 
	account * user, 
	double amount, 
	const QString & number, 
	const QString & title, 
	QString receiver_name, 
	QString receiver_adress
) {

	if (amount > user->getAccBalance()) {
		return "You've got no money to do this transaction...";
	}

	if (!db->Connect()) {
		return db->GetLastError();
	}

	QSqlQuery query(db->getDB());

	bool download_receiver_data = receiver_name.isEmpty();

	QString columns = (download_receiver_data ? "Id_Uzytkow, Imie, Nazwisko, Adres" : "Id_Uzytkow");
	query.exec("SELECT " + columns + " FROM UZYTKOWNIK WHERE Nr_Rachunku LIKE " + number);

	if (query.size() != 1) {
		return "Wrong account number!";
	}

	query.first();

	QString receiver_id = query.value(0).toString();
	QString amount_str = QString::number(amount);
	if (download_receiver_data) {
		receiver_name = query.value(1).toString() + " " + query.value(2).toString();
		receiver_adress = query.value(3).toString();
	}

	QString req = "INSERT INTO TRANSAKCJE (Nr_Rach_Nad, Nr_Rach_Odb, Kwota, Tytul, Nazw_Odb, Adres_Odb) "
		"VALUES('" + user->getAccNumber() + "', '" + number + "', " + amount_str + ", '" + title + "', '" + receiver_name + "', '" + receiver_adress + "');\n"
		"UPDATE UZYTKOWNIK SET Stan_Konta = Stan_Konta + " + amount_str + " WHERE Id_Uzytkow = " + receiver_id + ";\n"
		"UPDATE UZYTKOWNIK SET Stan_Konta = Stan_Konta - " + amount_str + " WHERE Id_Uzytkow = " + QString::number(user->getUserId()) + ";";

	if (!query.exec(req)) {
		return query.lastError().text();
	}

	return "Successfully transferred $" + amount_str + " to " + receiver_name + "!\nThank you!";
}
