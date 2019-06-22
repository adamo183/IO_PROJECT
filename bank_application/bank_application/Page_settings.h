#pragma once
#include "Page.h"
#include <QTableWidget>
#include <QTableView>
#include "JobField.h"

class Page_settings :
	public Page
{
	Q_OBJECT

	account *User = Q_NULLPTR;
	DB_Holder * db_holder = nullptr;

	QLabel * lbl;
	QPushButton * cancel_btn;
	QPushButton * save_btn;
	QPushButton * new_job_btn;
	QGridLayout * info_lay;
	QGridLayout * btns_lay;
	QWidget * info_widget ;
	QLabel * name_label;
	QLabel * surname_label;
	QLabel * phone_label ;
	QLabel * doc_label ;
	QLabel * addr_label ;
	QLabel * job_label;

	QLineEdit * name_line;
	QLineEdit * surname_line;
	QLineEdit * phone_line;
	QLineEdit * doc_line;
	QLineEdit * addr_line;

	QVBoxLayout * jobs_lay;
	std::vector<JobField *> jobs;



public:
	void showPage() override;
	void setHidden(bool emitSignal = true) override;


	Page_settings(QScrollArea * parent = Q_NULLPTR, DB_Holder * db = nullptr, const QString & CSS = "", account *user = Q_NULLPTR) : Page(parent, CSS), db_holder(db), User(user) {};
	~Page_settings();

public slots:
	void setNewData();

};

