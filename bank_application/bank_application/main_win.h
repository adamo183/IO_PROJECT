#pragma once

#include <thread>

#include <QtWidgets/QMainWindow>
#include <QMessageBox>
#include <QLabel>
#include <QTimer>

#include "ui_main_win.h"
#include "DB_Holder.h"
#include "Thread_synch.h"

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

	std::pair<QDateTime, QString> test_record;
	QLabel * output;
	QTimer * timer;

	Thread_synch thread_synch;
	DB_Holder db;
};
