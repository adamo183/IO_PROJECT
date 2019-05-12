#pragma once

#include <QObject>
#include <QMainWindow>

class Page : public QWidget
{
	Q_OBJECT
public:
	Page(QWidget* parent = 0);

private:
	QWidget* login_window;
};