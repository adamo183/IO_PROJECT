#pragma once
#include "Page.h"
#include <QTableWidget>
#include <QTableView>

struct JobField
{
	int Job_id;
	bool isNew = false;
	bool deleteJob = false;
	QWidget * wgt;
	QGridLayout * lay;
	std::vector<QLabel *> lbls;
	QString Name, Address, Salary;
	enum { NAME, ADDRESS, SALARY };
	std::vector<QLineEdit *> lines;
	QPushButton * delete_job;

	JobField(int job_id = INT_MIN, const QString & name = "", const QString & address = "", const QString & salary = "") {
		lbls.resize(3);
		lines.resize(3);

		if (job_id == INT_MIN) isNew = true;
		Job_id = job_id;
		Name = name;
		Address = address;
		Salary = salary;

		wgt = new QWidget;
		lay = new QGridLayout(wgt);
		delete_job = new QPushButton((isNew ? "Cancel" : "Delete this job"), wgt);

		lbls[NAME] = new QLabel("Company:");
		lines[NAME] = new QLineEdit(name, wgt);
		lbls[ADDRESS] = new QLabel("Address:");
		lines[ADDRESS] = new QLineEdit(address, wgt);
		lbls[SALARY] = new QLabel("Salary:");
		lines[SALARY] = new QLineEdit(salary, wgt);

		for (int i = 0; i < 3; ++i) {
			lay->addWidget(lbls[i], i, 0, Qt::AlignRight);
			lay->addWidget(lines[i], i, 1, Qt::AlignLeft);
		}
		lay->addWidget(delete_job, 3, 0, 1, 2, Qt::AlignCenter);
		wgt->setLayout(lay);
		wgt->setObjectName("withBorder");

		QObject::connect(delete_job, &QPushButton::clicked, wgt, [this]() {
			deleteJob = !deleteJob;
			for (auto & ite : lines) {
				ite->setEnabled(!deleteJob);
			}
			if (deleteJob) {
				delete_job->setText(isNew ? "New job" : "Restore this job");
			}
			else {
				delete_job->setText(isNew ? "Cancel" : "Delete this job");
			}
		});
	}
	~JobField() {
		for (int i = 0; i < 3; ++i) {
			delete lbls[i];
			delete lines[i];
		}
		delete delete_job;
		delete lay;
		delete wgt;
	}
};

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
	//QTableView * job_table;
	//QSqlTableModel *sql_tbl;//(this->parent, db_holder->getDB());

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

