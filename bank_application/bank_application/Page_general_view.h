#pragma once
#include "Page.h"
#include "Win_transfer.h"

/**
* Strona główna programu.
*/
class Page_general_view :
	public Page
{
	void send_transfer();
	void new_transfer(bool);

	Thread_signals current_work;

	DB_Holder * db_holder = nullptr;
	account* User = Q_NULLPTR;

	Win_transfer * win_transfer = Q_NULLPTR;

	QPushButton * new_transf = Q_NULLPTR;
	QPushButton* credit_bton = Q_NULLPTR;
	QPushButton * sett_bton = Q_NULLPTR;
	QPushButton* out_bton = Q_NULLPTR;
	QLabel * acc_lab = Q_NULLPTR;
	QLabel* curr_lab = Q_NULLPTR;
	QLabel* money = Q_NULLPTR;
	QPushButton*  acc_view = Q_NULLPTR;
	QLabel* quick_lab = Q_NULLPTR;
	QLabel* iwant_transf = Q_NULLPTR;
	QLabel* from = Q_NULLPTR;
	QLabel* to = Q_NULLPTR;
	QPushButton* showMore = Q_NULLPTR;
	QPushButton* send = Q_NULLPTR;
	QLineEdit* transf_field = Q_NULLPTR;
	QLineEdit* title_field = Q_NULLPTR;
	QLineEdit* to_field = Q_NULLPTR;

	QHBoxLayout * menu_layout = Q_NULLPTR;
	QGridLayout * quick_grid = Q_NULLPTR;
	QGridLayout * acc_grid = Q_NULLPTR;

	QWidget * quick_wgt = Q_NULLPTR;
	QWidget * acc_wgt = Q_NULLPTR;

public:

	/** Metoda wyświetlająca bieżącą stronę.
	*/
	void showPage() override;

	/** Metoda ukrywająca bieżącą stronę.
	*	@param emitSignal - flaga czy po ukryciu strony wyemitować sygnał ukrycia strony.
	*/
	void setHidden(bool emitSignal = true) override;

	/** Metoda implementująca pracę do wykonania w wątku pracującym.
	*/
	bool work_in_new_thread() override;


	/** Konstruktor inicjalizujący.
	*	@param parent - przodek obiektu.
	*	@param db - obiekt bazy danych.
	*	@param CSS - arkusz styli CSS.
	*	@param user - obiekt użytkownika.
	*/
	Page_general_view(QScrollArea * parent = Q_NULLPTR, DB_Holder * db = nullptr, const QString & CSS = "", account *user = Q_NULLPTR) : Page(parent, CSS), db_holder(db), User(user) {};

	/** Destruktor zwalniający dynamicznie zaalokowaną pamięć.
	*/
	~Page_general_view();
};
