#pragma once

#include <QWidget>
#include "DB_Holder.h"

class DB_Holder;

class account :public QObject
{
	Q_OBJECT

private:
	int user_id;
	QString name;
	QString surrname;
	QString acc_number;
	QString phone_number;
	QString adress;
	QString nr_doc;
	int credit_id;


public:
		account() {}

		account(int u_id, QString nm, QString srnm, QString acc_n, QString pn, QString addr, QString nr_d, int cr_id = 0) : user_id(u_id), name(nm), surrname(srnm), acc_number(acc_n)
		, phone_number(pn), adress(addr), nr_doc(nr_d), credit_id(cr_id) { }

		void setAccData(int u_id, QString nm, QString srnm, QString acc_n, QString pn, QString addr, QString nr_d, int cr_id = 0);

		int getUserId() const { return user_id; }
		QString getName() const { return name; }
		QString gatSurrname() const { return surrname; }
		QString getAccNumber() const { return acc_number; }
		QString getPhoneNumber() const { return phone_number; }
		QString getAdress() const { return adress; }
		QString getDocNumber() const { return nr_doc; }
		int getCreditId() const { return credit_id; }

		void setUserId(const int uid) { user_id = uid; }
		
		bool getUserData(DB_Holder *base);
};
