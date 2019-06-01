#include "Page_sign_in.h"


void Page_sign_in::showPage()
{


	isHidden = false;
	group_box = new QGroupBox(this->parent);
	main_lay = new QVBoxLayout(group_box);
	
	group_box->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

	// adamo

	QLabel * title_open = new QLabel("Enter your login and password");
	
	//title_open->setStyleSheet("border:1px solid black;border-radius:10px;padding:10px 120px 10px;text-align:center");

	//creating login field
	auto login_lab = new QLabel("Login:");
	auto pass_lab = new QLabel("Haslo:");
	auto login_field = new QLineEdit;// ("Kowalski");
	auto pass_field = new QLineEdit;// ("1234");

	pass_field->setEchoMode(QLineEdit::Password);
	send_butt = new QPushButton("Sign in");


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
	//status_login->addWidget(status);
	status_login->setAlignment(Qt::AlignCenter);
	//status->setMargin(100);
	group_box->setLayout(main_lay);





	// end of adamo

	main_lay->addWidget(send_butt);

	parent->setWidget(group_box);

	setCSS();

	setProcessDescription("Verifying...");

	connect(send_butt, &QPushButton::clicked, this, [this,login_field,pass_field]() {
		set_login_data(login_field->text(), pass_field->text() );
		wait_for_the_thread_and_emit_signal();
	});

}

void Page_sign_in::setHidden(bool emitSignal)
{
	isHidden = true;


	for (auto & ite : parent->widget()->children()) {
		delete ite;
	}
	delete group_box;

	if (emitSignal) { 
		emit hide(); 
	}

}

bool Page_sign_in::work_in_new_thread()
{
	bool downloaded_success = false;

	downloaded_success = db_holder->Login(login,password,User) && User->getUserData(db_holder);

	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	
	last_error = db_holder->GetLastError();

	return downloaded_success;
}


Page_sign_in::~Page_sign_in()
{
	if(!isHidden)
		setHidden(false);
}

void Page_sign_in::set_login_data(QString log,QString pas)
{
	login = new QString(log);
	password = new QString(pas);

}