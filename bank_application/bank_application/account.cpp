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

bool account::getUserData(DB_Holder *hold)
{

	QSqlQuery query(hold->getDB());
	int u_id = getUserId();
	query.prepare("SELECT * FROM `UZYTKOWNIK` WHERE Id_Uzytkow = :uid");
	query.bindValue(":uid", user_id);

	if(hold->Connect())		
	{
		query.exec(); 
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

		// todo: pobieranie dalszych danych , last error i jakieœ zabezpieczenia ..
	}
	 

	return false;
}
