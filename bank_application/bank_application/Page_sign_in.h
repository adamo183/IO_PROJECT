#pragma once
#include "Page.h"

#include <QLineEdit>

class Page_sign_in :
	public Page
{
	
	account *User = Q_NULLPTR;
	QPushButton * send_butt = Q_NULLPTR;
	QLabel * lbl = Q_NULLPTR;

	std::atomic<bool> download_success = false;

public slots:
	void set_login_data(QString log, QString pas);

public:
	void showPage() override;
	void setHidden(bool emitSignal = true) override;
	bool work_in_new_thread() override;

	Page_sign_in(QScrollArea * parent = Q_NULLPTR, DB_Holder * db = nullptr, const QString & CSS = "" , account *user = Q_NULLPTR) : Page(parent, CSS), db_holder(db) , User(user) {};

	~Page_sign_in();

	

protected:
	DB_Holder * db_holder = nullptr;
	QString *login;
	QString *password;
	
	
};

