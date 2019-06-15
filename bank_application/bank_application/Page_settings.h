#pragma once
#include "Page.h"
#include <QTableWidget>
#include <QTableView>

class Page_settings :
	public Page
{
	Q_OBJECT

	account *User = Q_NULLPTR;
	DB_Holder * db_holder = nullptr;

	QLabel * lbl;
	QPushButton * btn;
	QGridLayout * info_lay;
	QWidget * info_widget ;
	QLabel * name_label;
	QLabel * surname_label;
	QLabel * phone_label ;
	QLabel * doc_label ;
	QLabel * addr_label ;
	QLabel * job_label;
	QTableView * job_table;
	QSqlTableModel *sql_tbl;//(this->parent, db_holder->getDB());
	QPushButton * submit ;
	QPushButton * new_job ;
	QHBoxLayout * down_btn ;

	QLineEdit * name_line;
	QLineEdit * surname_line;
	QLineEdit * phone_line;
	QLineEdit * doc_line;
	QLineEdit * addr_line;
public:
	void showPage() override;
	void setHidden(bool emitSignal = true) override;


	Page_settings(QScrollArea * parent = Q_NULLPTR, DB_Holder * db = nullptr, const QString & CSS = "", account *user = Q_NULLPTR) : Page(parent, CSS), db_holder(db), User(user) {};
	~Page_settings();

public slots:
	void setNewData();

};

