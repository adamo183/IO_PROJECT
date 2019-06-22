#pragma once
#include "Page.h"
#include "Win_transfer.h"

#include <QToolBox>
#include <QButtonGroup>

class Page_Trans_Hist :
	public Page
{
	void send_btn(int i);

	account *User = Q_NULLPTR;
	DB_Holder * db_holder = nullptr;

	QLabel * lbl;
	QPushButton * btn;

	QButtonGroup * btn_gr;

	QToolBox * trans_tool_box;

	Win_transfer * win_transfer = Q_NULLPTR;

	std::vector<account::SingleTransaction> transactions;
	std::vector<std::pair<QWidget *, QGridLayout *>> trans_wgt_lay;
	std::vector<std::pair<QLabel *, QPushButton *>> lbl_btn;

public:
	void showPage() override;
	void setHidden(bool emitSignal = true) override;


	Page_Trans_Hist(QScrollArea * parent = Q_NULLPTR, DB_Holder * db = nullptr, const QString & CSS = "", account *user = Q_NULLPTR) : Page(parent, CSS), db_holder(db), User(user) {};
	~Page_Trans_Hist();
};

