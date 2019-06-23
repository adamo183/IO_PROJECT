#pragma once

#include <QWidget>
#include "DB_Holder.h"

class DB_Holder;

/**
*	Enum płci.
*/
enum Sex {
	/**
	*	Kobieta.
	*/
	FEMALE,
	/**
	*	Mężczyzna.
	*/
	MALE
};

/**
* Klasa reprezentująca użytkownika banku.
*/
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
	/** 
	*	Krotka reprezentująca pojedynczą transakcję. Kolejno: id transakcji, stempel czasowy transakcji, numer konta, kwota, tytuł, nazwa odbiorcy / nadawcy, adres.
	*/
	typedef std::tuple<int, QDateTime, QString, double, QString, QString, QString> SingleTransaction; 

	/**
	*	Krotka reprezentująca rekord z informacjami o pracy. Kolejno: id pracy, nazwa firmy, adres firmy, kwota wypłaty. 
	*/
	typedef std::tuple<int, QString, QString, double> SingleJob;
	
	/**
	*	Enum indeksów pól pojedynczej transakcji.
	*/
	enum Transaction{ 
		/**
		* Id transakcji.
		*/
		ID, 
		/**
		* Stempel czasowy transakcji.
		*/
		DATETIME, 
		/**
		* Numer konta.
		*/
		ACC_NO, 
		/**
		* Kwota trancakcji.
		*/
		AMOUNT, 
		/**
		* Tytuł transakcji.
		*/
		TITLE, 
		/**
		* Nazwa nadawcy / odbiorcy.
		*/
		NAME, 
		/**
		* Adres.
		*/
		ADDRESS 
	};
	
	/** Getter.
	*	@return Id użytkownika.
	*/
	int getUserId() const { return user_id; }

	/** Getter.
	*	@return Imie użytkownika.
	*/
	QString getName() const { return name; }

	/** Getter.
	*	@return Nazwisko użytkownika.
	*/
	QString getSurrname() const { return surrname; }

	/** Getter.
	*	@return Numer konta użytkownika.
	*/
	QString getAccNumber() const { return acc_number; }

	/** Getter.
	*	@return Numer telefonu użytkownika.
	*/
	QString getPhoneNumber() const { return phone_number; }

	/** Getter.
	*	@return Adres zamieszkania użytkownika.
	*/
	QString getAdress() const { return adress; }

	/** Getter.
	*	@return Numer dowodu użytkownika.
	*/
	QString getDocNumber() const { return nr_doc; }

	/** Getter.
	*	@return Id kredytu użytkownika, lub 0 jeżeli użytkownik nie brał kredytu.
	*/
	int getCreditId() const { return credit_id; }

	/** Getter.
	*	@return Stan konta użytkownika.
	*/
	double getAccBalance() const { return acc_balance; }

	/** Getter.
	*	@return Data urodzenia użytkownika.
	*/
	QDate getBornDate() const { return born_date; }

	/** Getter.
	*	@return Ostatni błąd jaki wystąpił.
	*/
	QString getLastError() const { return last_error; }

	/** Getter.
	*	@return Wszystkie transakcje użytkownika.
	*/
	const std::vector<SingleTransaction> & getTransactions() const { return Transactions; }

	/** Getter.
	*	@return Wszytkie prace użytkownika.
	*/
	const std::vector<SingleJob> & getJobs() const { return Jobs; };

	/** Getter.
	* @return Suma transakcji użytkownika.
	*/
	double getSalarySum() const { return salary_sum; };

	/** Getter.
	*	@return Wiek użytkownika.
	*/
	int getAge() const;

	/** Setter.
	* @param uid - Id użytkownika
	*/
	void setUserId(const int uid) { user_id = uid; }

	/** Setter.
	*	@param u_id - Id użytkownika.
		@param nm - Imię użytkownika.
		@param srnm - Nazwisko użytkownika.
		@param acc_n - Numer konta użytkownika.
		@param pn - Numer telefonu użytkownika.
		@param addr - Adres zamieszkania użytkownika.
		@param nr_d - Numer dowodu użytkownika.
		@param cr_id - Numer kredytu użytkownika, domyślnie 0 - brak kredytu.
	*/
	void setAccData(int u_id, QString nm, QString srnm, QString acc_n, QString pn, QString addr, QString nr_d, int cr_id = 0);


	/** Metoda sprawdająca czy użytkownik ma jakąś pracę.
	* @return true - jest zatrudniony, false - nie.
	*/
	bool hasJob() const { return (salary_sum != 0 ? 1 : 0); };

	/** Metoda sprawdzająca czy użytkownik wiął już kredyt.
	* @return true - posiada kredyt, false - nie.
	*/
	bool hasCredit() const { return credit_id; };
	
	/** Metoda pobierająca dane użytkownika z bazy danych.
	* @param base - obiekt bazy danych.
	* @return true - pobieranie zakończone sukcesem, false - wystąpił błąd.
	*/
	bool downloadUserData(DB_Holder *base);

	/** Metoda pobierająca transakcje użytkownika z bazy danych.
	* @param base - obiekt bazy danych.
	* @return true - pobieranie zakończone sukcesem, false - wystąpił błąd.
	*/
	bool downloadUserTransactions(DB_Holder *base);

	/** Metoda pobierająca prace użytkownika z bazy danych.
	* @param base - obiekt bazy danych.
	* @return true - pobieranie zakończone sukcesem, false - wystąpił błąd.
	*/
	bool downloadUserJobs(DB_Holder * base);

};
