#pragma once

#include <QObject>
#include <QMainWindow>
#include "main_win.h"

class Page : public QWidget
{
	Q_OBJECT
public:
	Page(QWidget* parent = 0);
	QLabel* status;

private:
	QWidget* login_window;

protected:
	Thread_synch thread_synch;
	DB_Holder db;
	std::pair<QDateTime, QString> test_record;

public slots:
	void db_connect();
	
};