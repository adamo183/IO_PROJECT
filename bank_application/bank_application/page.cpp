#include "page_h.h"
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include "main_win.h"
#include <QWidget>
#include <QPushButton>

Page::Page(QWidget* parent) :QWidget(parent)
{
	
	
	/*
	QWidget *open_w = new QWidget;
	
	QLabel *title_open = new QLabel("Podaj login oraz haslo");
	auto login_lab = new QLabel("Login:");
	auto pass_lab = new QLabel("Haslo:");
	auto login_field = new QLineEdit;
	auto pass_field = new QLineEdit;

	pass_field->setEchoMode(QLineEdit::Password);

	auto horizont_login = new QHBoxLayout;
	auto horizont_pass = new QHBoxLayout;


	main_lay->addLayout(horizont_login, 2, 1);
	main_lay->addLayout(horizont_pass, 3, 1);

	main_lay->addWidget(title_open, 1, 1, Qt::AlignCenter | Qt::AlignTop);
	horizont_login->addStretch();
	horizont_login->addWidget(login_lab);
	horizont_login->addWidget(login_field);
	horizont_login->addStretch();

	horizont_pass->addStretch();
	horizont_pass->addWidget(pass_lab);
	horizont_pass->addWidget(pass_field);
	horizont_pass->addStretch();

	horizont_login->setAlignment(Qt::AlignTop);
	horizont_pass->setAlignment(Qt::AlignTop);

	main_lay->setAlignment(Qt::AlignTop);
	main_lay->setSpacing(30);


	title_open->setStyleSheet("border:1px solid black;padding:20px 20px 20px");
	open_w->setLayout(main_lay);
	*/

	
	

	auto main_lay = new QVBoxLayout;
	QLabel *title_open = new QLabel("Enter your login and password");
	title_open->setStyleSheet("border:1px solid black;padding:20px 100px 20px;border-radius:10px");
	main_lay->addWidget(title_open);
	
	//creating login field 
	auto login_lab = new QLabel("Login:");
	auto pass_lab = new QLabel("Haslo:");
	auto login_field = new QLineEdit;
	auto pass_field = new QLineEdit;
	auto send_butt = new QPushButton("Sign in");

	
	//creating layout
	auto logo = new QHBoxLayout;
	auto horizont_login = new QHBoxLayout;
	auto horizont_pass = new QHBoxLayout;
	auto horizont_butt = new QHBoxLayout;

	//setings layout
	logo->setAlignment(Qt::AlignCenter);
	horizont_login->setAlignment(Qt::AlignTop);
	horizont_pass->setAlignment(Qt::AlignTop);
	main_lay->setAlignment(Qt::AlignTop);
	
	//adding inside layout to main_lay
	main_lay->addLayout(logo);
	main_lay->addLayout(horizont_login);
	main_lay->addLayout(horizont_pass);
	main_lay->addLayout(horizont_butt);
	//insert thinks into layouts
	logo->addWidget(title_open);

	horizont_login->addStretch();
	horizont_login->addWidget(login_lab);
	horizont_login->addWidget(login_field);
	horizont_login->addStretch();

	horizont_pass->addStretch();
	horizont_pass->addWidget(pass_lab);
	horizont_pass->addWidget(pass_field);
	horizont_pass->addStretch();
	
	horizont_butt->addWidget(send_butt);
	setLayout(main_lay);
	
}

