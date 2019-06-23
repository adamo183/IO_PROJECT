#pragma once
#include "Page.h"
#include "Credit.h"
#include "Transfer.h"

#include <QTextBrowser>
#include <QCheckBox>

/**
* Strona gui odpowiedzianego za kredyty.
*/
class Page_credit :
	public Page
{
	account *User = Q_NULLPTR;
	DB_Holder * db_holder = nullptr;
	Credit * credit = nullptr;

	double amount = 0, ratio_of_interest = 5.2;
	int duration = 0;

	QGridLayout * lay;

	QLabel * conditions_lbl, * amount_lbl, * duration_lbl, * ans_lbl;
	QTextBrowser * conditions_field;
	QCheckBox * conditions_check;
	QLineEdit * amount_ln, * duration_ln;
	QPushButton * verify_btn, * ans_btn;

	QPushButton * back_btn;

	void verify_ans();
	void take_credit();

public:

	/** Metoda wyświetlająca bieżącą stronę.
	*/
	void showPage() override;

	/** Metoda ukrywająca bieżącą stronę.
	*	@param emitSignal - flaga czy po ukryciu strony wyemitować sygnał ukrycia strony.
	*/
	void setHidden(bool emitSignal = true) override;

	/** Konstruktor inicjalizujący.
	*	@param parent - przodek obiektu.
	*	@param db - obiekt bazy danych.
	*	@param CSS - arkusz styli CSS.
	*	@param user - obiekt użytkownika.
	*/
	Page_credit(QScrollArea * parent = Q_NULLPTR, DB_Holder * db = nullptr, const QString & CSS = "", account *user = Q_NULLPTR) : Page(parent, CSS), db_holder(db), User(user) {};

	/** Destruktor zwalniający dynamicznie zaalokowaną pamięć.
	*/
	~Page_credit();
};

