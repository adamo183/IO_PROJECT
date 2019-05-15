#pragma once
#include "Page.h"

class Page_general_view :
	public Page
{
	DB_Holder * db_holder = nullptr;
	
	QLabel * lbl = Q_NULLPTR;


public:
	void showPage() override;
	void setHidden(bool emitSignal = true) override;

	Page_general_view(QScrollArea * parent = Q_NULLPTR, DB_Holder * db = nullptr, const QString & CSS = "") : Page(parent, CSS), db_holder(db) {};
	~Page_general_view();
};
