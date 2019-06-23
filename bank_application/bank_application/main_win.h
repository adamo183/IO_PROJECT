#pragma once

#include <QtWidgets/QMainWindow>
#include <QFile>
#include <QTextStream>
#include <QHBoxLayout>
#include <QIcon>
#include <QCloseEvent>
#include <QTimer>
#include <qdebug.h>

#include "ui_main_win.h"
#include "Page_sign_in.h"
#include "Page_general_view.h"
#include "Page_credit.h"
#include "Page_Trans_Hist.h"
#include "Page_settings.h"

#include "DB_Holder.h"
#include "account.h"


/**
* Klasa odpowiedzialna za gui.
*/
class main_win : public QMainWindow
{
	Q_OBJECT
		
public:
	/** Konstruktor inicjalizujący aplikację.
	*	@param parent - przodek, domyślnie brak przodka.
	*/
	main_win(QWidget *parent = Q_NULLPTR);

	/** Destruktor zwalniający dynamicznie zaalokowaną pamięć.
	*/
	~main_win();

private:
	bool closeAble = true;
	void closeEvent(QCloseEvent *bar);
	bool eventFilter(QObject *watched, QEvent *event);

	int cc = 0;

	Ui::main_winClass ui;

	QString css = "";
	QTimer * timer;

	enum {SING_IN, GEN_VIEW, CREDIT, TRANS_HIST, SETT};
	std::vector<Page *> pages;

	DB_Holder db_holder;
	account *user = Q_NULLPTR;
};
