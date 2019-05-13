#include "page_h.h"
#include "main_win.h"

#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QWidget>
#include <QPushButton>
#include <QMessageBox>
#include <thread>

Page::Page(QWidget* parent) :QWidget(parent)
{

	auto main_lay = new QVBoxLayout;
	QLabel *title_open = new QLabel("Enter your login and password");
	title_open->setStyleSheet("border:1px solid black;border-radius:10px;padding:10px 120px 10px;text-align:center");
	

	//creating login field 
	auto login_lab = new QLabel("Login:");
	auto pass_lab = new QLabel("Haslo:");
	auto login_field = new QLineEdit;
	auto pass_field = new QLineEdit;
	auto send_butt = new QPushButton("Sign in");
	status = new QLabel;


	//creating layout
	auto logo = new QHBoxLayout;
	auto horizont_login = new QHBoxLayout;
	auto horizont_pass = new QHBoxLayout;
	auto horizont_butt = new QHBoxLayout;
	auto status_login = new QHBoxLayout;
	//setings layout
	
	horizont_login->setAlignment(Qt::AlignTop);
	horizont_pass->setAlignment(Qt::AlignTop);
	main_lay->setAlignment(Qt::AlignTop);

	//adding inside layout to main_lay
	main_lay->addLayout(logo);
	main_lay->addLayout(horizont_login);
	main_lay->addLayout(horizont_pass);
	main_lay->addLayout(horizont_butt);
	main_lay->addLayout(status_login);
	//insert thinks into layouts
	
	logo->addWidget(title_open);

	logo->setAlignment(Qt::AlignCenter);
	title_open->setFixedWidth(400);
	
	horizont_login->addStretch();
	horizont_login->addWidget(login_lab);
	horizont_login->addWidget(login_field);
	horizont_login->addStretch();

	horizont_pass->addStretch();
	horizont_pass->addWidget(pass_lab);
	horizont_pass->addWidget(pass_field);
	horizont_pass->addStretch();

	horizont_butt->addWidget(send_butt);
	send_butt->setFixedWidth(100);
	title_open->setFixedWidth(400);
	status_login->addWidget(status);
	status_login->setAlignment(Qt::AlignCenter);
	status->setMargin(100);
	setLayout(main_lay);
	
	connect(send_butt, SIGNAL(clicked()), this, SLOT(db_connect()));
	
}

void Page::db_connect()
{
	
	connect(&thread_synch, &Thread_synch::changed, this, [&](bool val) {

		if (val == thread_synch.started) {
			status->setText("Pobieram");
			
		}

		if (val == thread_synch.ended) {
			status->setText(test_record.first.toString("yyyy-MM-dd hh:mm:ss") + "<br/><h1>" + test_record.second + "</h1>");
			
		}

	});
	
	
	std::thread T1([this]() {

		thread_synch.start();
		test_record = db.GetTest();
		
		
		thread_synch.stop();

	});
	T1.detach();
}

