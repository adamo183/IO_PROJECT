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