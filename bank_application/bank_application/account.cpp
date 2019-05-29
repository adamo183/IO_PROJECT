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

bool account::getUserData(DB_Holder *hold)
{

	QSqlQuery query(hold->getDB());
	int u_id = getUserId();
	query.prepare("SELECT * FROM `UZYTKOWNIK` WHERE Id_Uzytkow = :uid");
	query.bindValue(":uid", user_id);

	if(hold->Connect())		
	{
		query.exec(); 
		query.next();
		name = query.value(1).toString();
		surrname = query.value(2).toString();
		// todo: pobieranie dalszych danych , last error i jakie� zabezpieczenia ..
	}
	 

	return false;
}
