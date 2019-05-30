#pragma once
#include "Page.h"
class Page_settings :
	public Page
{
	account *User = Q_NULLPTR;
	DB_Holder * db_holder = nullptr;

	QLabel * lbl;
	QPushButton * btn;

public:
	void showPage() override;
	void setHidden(bool emitSignal = true) override;


	Page_settings(QScrollArea * parent = Q_NULLPTR, DB_Holder * db = nullptr, const QString & CSS = "", account *user = Q_NULLPTR) : Page(parent, CSS), db_holder(db), User(user) {};
	~Page_settings();
};

