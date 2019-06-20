#include "Page_sign_in.h"


void Page_sign_in::showPage()
{


	isHidden = false;
	group_box = new QGroupBox(this->parent);
	main_lay = new QVBoxLayout(group_box);
	
	group_box->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

	QLabel * title_open = new QLabel("Enter your login and password");

	auto login_lab = new QLabel("Login:");
	auto pass_lab = new QLabel("Password:");
	auto login_field = new QLineEdit;
	auto pass_field = new QLineEdit;

	pass_field->setEchoMode(QLineEdit::Password);
	send_butt = new QPushButton("Sign in");
	send_butt->setShortcut(QKeySequence::InsertParagraphSeparator);

	auto grid_layout = new QGridLayout;

	grid_layout->addWidget(title_open, 0, 0, 1, 2, Qt::AlignCenter);
	grid_layout->addWidget(login_lab, 1, 0, Qt::AlignRight);
	grid_layout->addWidget(login_field, 1, 1);

	grid_layout->addWidget(pass_lab, 2, 0, Qt::AlignRight);
	grid_layout->addWidget(pass_field, 2, 1);

	grid_layout->addWidget(send_butt, 3, 0, 1, 2, Qt::AlignCenter);

	login_field->setFixedWidth(140);
	pass_field->setFixedWidth(140);
	send_butt->setFixedWidth(100);
	title_open->setFixedWidth(250);

	main_lay->addLayout(grid_layout);

	group_box->setLayout(main_lay);

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

	send_butt->disconnect();

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

	//std::this_thread::sleep_for(std::chrono::milliseconds(500));
	
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