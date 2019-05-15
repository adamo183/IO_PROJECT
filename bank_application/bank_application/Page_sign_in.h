#pragma once
#include "Page.h"

#include <QLineEdit>

class Page_sign_in :
	public Page
{
	DB_Holder * db_holder = nullptr;

	QPushButton * send_butt = Q_NULLPTR;
	QLabel * lbl = Q_NULLPTR;

	std::atomic<bool> download_success = false;

public:
	void showPage() override;
	void setHidden(bool emitSignal = true) override;
	bool work_in_new_thread() override;

	Page_sign_in(QScrollArea * parent = Q_NULLPTR, DB_Holder * db = nullptr, const QString & CSS = "") : Page(parent, CSS), db_holder(db) {};

	~Page_sign_in();
};

