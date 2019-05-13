#pragma once

#include <thread>

#include <QtWidgets/QMainWindow>
#include <QMessageBox>
#include <QLabel>
#include <QTimer>
#include <QStackedWidget>

#include "ui_main_win.h"
#include "DB_Holder.h"
#include "Thread_synch.h"
#include "page_h.h"

class main_win : public QMainWindow
{
	Q_OBJECT

public:
	main_win(QWidget *parent = Q_NULLPTR);
	~main_win() {
		delete output;
		delete timer;
	}


private:
	Ui::main_winClass ui;

	
	QLabel * output;
	QTimer * timer;
	QStackedWidget* window;


};