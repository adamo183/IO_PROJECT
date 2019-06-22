#include "JobField.h"

JobField::~JobField()
{
	for (int i = 0; i < 3; ++i) {
		delete lbls[i];
		delete lines[i];
	}
	delete delete_job_btn;
	delete lay;
}

JobField::JobField(int job_id, const QString & name, const QString & address, const QString & salary) : 
	Job_id(job_id), 
	Name(name), 
	Address(address), 
	Salary(salary),
	isNew(job_id == INT_MIN ? true : false)
{
	lbls.resize(3);
	lines.resize(3);

	lay = new QGridLayout(this);
	delete_job_btn = new QPushButton((isNew ? "Cancel" : "Delete this job"), this);

	lbls[NAME] = new QLabel("Company:");
	lines[NAME] = new QLineEdit(name, this);
	lbls[ADDRESS] = new QLabel("Address:");
	lines[ADDRESS] = new QLineEdit(address, this);
	lbls[SALARY] = new QLabel("Salary:");
	lines[SALARY] = new QLineEdit(salary, this);

	for (int i = 0; i < 3; ++i) {
		lay->addWidget(lbls[i], i, 0, Qt::AlignRight);
		lay->addWidget(lines[i], i, 1, Qt::AlignLeft);
	}
	lay->addWidget(delete_job_btn, 3, 0, 1, 2, Qt::AlignCenter);
	this->setLayout(lay);
	this->setObjectName("withBorder");

	connect(delete_job_btn, &QPushButton::clicked, this, [this]() {
		deleteJob = !deleteJob;
		for (auto & ite : lines) {
			ite->setEnabled(!deleteJob);
		}
		if (deleteJob) {
			delete_job_btn->setText(isNew ? "New job" : "Restore this job");
		}
		else {
			delete_job_btn->setText(isNew ? "Cancel" : "Delete this job");
		}
	});
}