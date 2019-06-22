#pragma once
#include "Page.h"

/**
* Klasa widget edycji pojedynczego pola pracy.
*/
class JobField : public QWidget
{

	QGridLayout * lay;
	std::vector<QLabel *> lbls;

public:

	/**
	* Id pracy
	*/
	int Job_id;

	/**
	* Flaga czy ta praca jest nową świeżo dodaną.
	*/
	bool isNew = false;

	/**
	* Flaga zaznaczjąca czy bieżąca praca została oznaczona jako do usunięcia.
	*/
	bool deleteJob = false;

	/**
	* Wektor pól edyji.
	*/
	std::vector<QLineEdit *> lines;

	/**
	* Przycisk usuwania pracy.
	*/
	QPushButton * delete_job_btn;

	/**
	* Nazwa firmy.
	*/
	QString Name; 

	/**
	* Adres firmy.
	*/
	QString Address; 

	/**
	* Kwota wypłaty.
	*/
	QString Salary;

	/**
	* Indeksy pól w wektorze.
	*/
	enum { 
		/**
		* Nazwa firmy.
		*/
		NAME, 

		/**
		* Adres firmy.
		*/
		ADDRESS, 

		/**
		* Kwota wypłaty.
		*/
		SALARY 
	};

	/** Konstruktor inicjalizujący pola.
	* @param job_id - Id pracy, domyślnie INT_MIN oznacza nową pracę.
	* @param name - Nazwa firmy, domyślnie pusty string.
	* @param address - Adres firmy, domyślnie pusty string.
	* @param salary - Kwota wypłaty, domyślnie pusty string.
	*/
	JobField(int job_id = INT_MIN, const QString & name = "", const QString & address = "", const QString & salary = "");

	/** Destruktor zwalaniający dynamicznie zaalokowaną pamięć.
	*/
	~JobField();
};

