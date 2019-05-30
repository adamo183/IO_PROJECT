#pragma once

#include <QtWidgets/QMainWindow>
#include <QFile>
#include <QTextStream>
#include <QHBoxLayout>
#include <QIcon>

#include "ui_main_win.h"
#include "Page_sign_in.h"
#include "Page_general_view.h"
#include "DB_Holder.h"
#include "account.h"

class main_win : public QMainWindow
{
	Q_OBJECT

public:
	main_win(QWidget *parent = Q_NULLPTR);
	~main_win();


private:
	Ui::main_winClass ui;

	QString css = "";

	//QHBoxLayout * main_layout;??
	
	Page * page_sign_in = Q_NULLPTR;
	Page * page_general_view = Q_NULLPTR;

	DB_Holder db_holder;
	account *user = Q_NULLPTR;
};
