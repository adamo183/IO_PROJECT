#pragma once

#include <QWidget>
#include "DB_Holder.h"

class DB_Holder;

enum Sex{ FEMALE, MALE };

class account :public QObject
{
	Q_OBJECT

private:
	int user_id;
	QString name;
	QString surrname;
	QDate born_date;
	Sex sex;
	QString acc_number;
	double acc_balance;
	QString phone_number;
	QString adress;
	QString nr_doc;
	int credit_id;

	double salary_sum;

	std::vector<std::tuple<int, QDateTime, QString, double, QString, QString, QString>> Transactions;
	std::vector<std::tuple<int, QString, QString, double>> Jobs;

	QString last_error;

public:
	typedef std::tuple<int, QDateTime, QString, double, QString, QString, QString> SingleTransaction;
	typedef std::tuple<int, QString, QString, double> SingleJob;
	enum Transaction{ ID, DATETIME, ACC_NO, AMOUNT, TITLE, NAME, ADDRESS };


		account() {}

		account(int u_id, QString nm, QString srnm, QString acc_n, QString pn, QString addr, QString nr_d, int cr_id = 0) : user_id(u_id), name(nm), surrname(srnm), acc_number(acc_n)
		, phone_number(pn), adress(addr), nr_doc(nr_d), credit_id(cr_id) { }

		void setAccData(int u_id, QString nm, QString srnm, QString acc_n, QString pn, QString addr, QString nr_d, int cr_id = 0);

		int getUserId() const { return user_id; }
		QString getName() const { return name; }
		QString getSurrname() const { return surrname; }
		QString getAccNumber() const { return acc_number; }
		QString getPhoneNumber() const { return phone_number; }
		QString getAdress() const { return adress; }
		QString getDocNumber() const { return nr_doc; }
		int getCreditId() const { return credit_id; }
		double getAccBalance() const { return acc_balance; }
		QDate getBornDate() const { return born_date; }
		int getAge() const;
		QString getLastError() { return last_error; }
		const std::vector<SingleTransaction> & getTransactions() { return Transactions; }
		const std::vector<SingleJob> & getJobs() { return Jobs; };


		void setUserId(const int uid) { user_id = uid; }
		
		bool getUserData(DB_Holder *base);
		bool DownloadUserTransactions(DB_Holder *base);
		bool DownloadUserJobs(DB_Holder * base);

		bool hasJob() const { return (salary_sum != 0 ? 1 : 0); };
		double getSalarySum() const { return salary_sum; };

		bool hasCredit() const { return credit_id; };

};
