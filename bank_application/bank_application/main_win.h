#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_main_win.h"

class main_win : public QMainWindow
{
	Q_OBJECT

public:
	main_win(QWidget *parent = Q_NULLPTR);

private:
	Ui::main_winClass ui;
};
