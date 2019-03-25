#pragma once

#include <QtWidgets/QMainWindow>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <vector>
#include "ui_main_win.h"

class main_win : public QMainWindow
{
	Q_OBJECT

public:
	main_win(QWidget *parent = Q_NULLPTR);
	~main_win();

private:
	Ui::main_winClass ui;

	QVBoxLayout * main_layout;
	QPushButton * button;
	QLabel * lbl;

	std::vector<QString> colors = { "yellow", "green", "red", "blue", "brown", "orange", "black" };
};