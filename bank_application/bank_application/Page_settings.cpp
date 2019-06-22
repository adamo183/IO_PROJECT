#include "Page_settings.h"
#include <algorithm>

void Page_settings::showPage()
{
	isHidden = false;

	group_box = new QGroupBox(this->parent);
	main_lay = new QVBoxLayout(group_box);

	group_box->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
	/******************************************************************************/
	 info_lay = new QGridLayout;
	info_widget = new QWidget;
	 name_label = new QLabel("Name: ");
	name_line = new QLineEdit;
	 surname_label = new QLabel("Surname: ");
	 surname_line = new QLineEdit;
	 phone_label = new QLabel("Phone number: ");
	 phone_line = new QLineEdit;
	 doc_label = new QLabel("Document number: ");
	 doc_line = new QLineEdit;
	 addr_label = new QLabel("Address: ");
	 addr_line = new QLineEdit;
	 job_label = new QLabel("Job setting");

	lbl = new QLabel("Account Settings");
	main_lay->addWidget(lbl, 0, Qt::AlignCenter);
	main_lay->addWidget(info_widget);

	info_widget->setLayout(info_lay);
	info_lay->addWidget(name_label,0,0);
	info_lay->addWidget(name_line,0,1);
	name_line->setText(User->getName());
	info_lay->addWidget(surname_label,1,0);
	info_lay->addWidget(surname_line,1,1);
	surname_line->setText(User->getSurrname());
	info_lay->addWidget(phone_label, 2, 0);
	info_lay->addWidget(phone_line, 2, 1);
	phone_line->setText(User->getPhoneNumber());
	info_lay->addWidget(doc_label, 3, 0);
	info_lay->addWidget(doc_line, 3, 1);
	doc_line->setText(User->getDocNumber());
	info_lay->addWidget(addr_label, 4, 0);
	info_lay->addWidget(addr_line, 4, 1);
	addr_line->setText(User->getAdress());
	main_lay->addWidget(job_label,0,Qt::AlignCenter);

	info_widget->setObjectName("withBorder");

	jobs_lay = new QVBoxLayout;
	/**********************************************************************/

	std::vector<account::SingleJob> jobs_data = User->getJobs();

	for (auto & ite : jobs_data) {

		jobs.push_back(new JobField(
			std::get<0>(ite),
			std::get<1>(ite),
			std::get<2>(ite),
			QString::number(std::get<3>(ite))
		));
		jobs_lay->addWidget(jobs.back());
	}

	/***********************************************************************/
	main_lay->addLayout(jobs_lay);

	btns_lay = new QGridLayout;// (parent);
	new_job_btn = new QPushButton("New job");
	cancel_btn = new QPushButton("Back");
	save_btn = new QPushButton("Save Changes");
	btns_lay->addWidget(new_job_btn, 0, 0, 1, 2, Qt::AlignCenter);
	btns_lay->setVerticalSpacing(20);
	btns_lay->addWidget(cancel_btn, 1, 0, Qt::AlignRight);
	btns_lay->addWidget(save_btn, 1, 1, Qt::AlignLeft);
	main_lay->addLayout(btns_lay);
		
	connect(cancel_btn, &QPushButton::clicked, this, [this]() {
		setHidden();
	});
	connect(save_btn, &QPushButton::clicked, this, [this]() {  setNewData(); });

	connect(new_job_btn, &QPushButton::clicked, this, [this]() {

		new_job_btn->hide();

		jobs.push_back(new JobField());
		jobs_lay->addWidget(jobs.back());
	});


	/******************************************************************************/

	parent->setWidget(group_box);


	setCSS();
}

void Page_settings::setNewData()
{
	bool success = false;
	if (db_holder->Connect()) {
		QSqlQuery query(db_holder->getDB());

		bool noChanges = true;

		if (name_line->text() != User->getName() && !name_line->text().isEmpty())
		{
			success = query.exec("UPDATE `UZYTKOWNIK` SET `Imie` = '" + name_line->text() + "'  WHERE `Id_Uzytkow` = " + QString::number(User->getUserId()));
			noChanges = false;
		}
		if (surname_line->text() != User->getSurrname() && !surname_line->text().isEmpty())
		{
			success = query.exec("UPDATE `UZYTKOWNIK` SET `Nazwisko` = '" + surname_line->text() + "'  WHERE `Id_Uzytkow` = " + QString::number(User->getUserId()));
			noChanges = false;
		}
		if (phone_line->text() != User->getPhoneNumber() && !phone_line->text().isEmpty())
		{
			success = query.exec("UPDATE `UZYTKOWNIK` SET `Nr_Tel` = '" + phone_line->text() + "'  WHERE `Id_Uzytkow` = " + QString::number(User->getUserId()));
			noChanges = false;
		}
		if (doc_line->text() != User->getDocNumber() && !doc_line->text().isEmpty())
		{
			success = query.exec("UPDATE `UZYTKOWNIK` SET `Nr_Dokumentu` = '" + doc_line->text() + "'  WHERE `Id_Uzytkow` = " + QString::number(User->getUserId()));
			noChanges = false;
		}
		if (addr_line->text() != User->getAdress() && !addr_line->text().isEmpty())
		{
			success = query.exec("UPDATE `UZYTKOWNIK` SET `Adres` = '" + addr_line->text() + "'  WHERE `Id_Uzytkow` = " + QString::number(User->getUserId()));
			noChanges = false;
		}

		for (auto & ite : jobs) {

			if (ite->isNew) {
				if (ite->deleteJob) continue;

				if (ite->lines[JobField::NAME]->text().isEmpty() ||
					ite->lines[JobField::ADDRESS]->text().isEmpty() ||
					ite->lines[JobField::SALARY]->text().isEmpty()) 
				{
					QMessageBox::information(parent, "Error", "Fill empty fields!");
					//db_holder->close();
					return;
				}
				success = query.exec("INSERT INTO DOCHOD(Id_Uzytkow, Nazwa_Firmy, Adres_Firmy, Kwota) VALUES("
						+ QString::number(User->getUserId()) + ", "
						"'" + ite->lines[JobField::NAME]->text() + "', " +
						"'" + ite->lines[JobField::ADDRESS]->text() + "', " +
						ite->lines[JobField::SALARY]->text().replace(",", ".") + ");");

				if (success) {
					ite->isNew = false;
					success = query.exec("SELECT Id_Doch FROM DOCHOD WHERE Id_Uzytkow = " + QString::number(User->getUserId()) + " ORDER BY Id_Doch DESC LIMIT 1;");
					query.next();

					ite->Job_id = query.value(0).toInt();
					ite->delete_job_btn->setText("Delete this job");
				}

				noChanges = false;
			}
			else {
				if (ite->deleteJob) {
					success = query.exec("DELETE FROM DOCHOD WHERE Id_Doch = " + QString::number(ite->Job_id) + ";");
				
					noChanges = false;
				}
				else {
					if (ite->lines[JobField::NAME]->text() != ite->Name && !ite->lines[JobField::NAME]->text().isEmpty())
					{
						success = query.exec("UPDATE `DOCHOD` SET `Nazwa_Firmy` = '" + ite->lines[JobField::NAME]->text() + "'  WHERE `Id_Doch` = " + QString::number(ite->Job_id));
						noChanges = false;
					}
					if (ite->lines[JobField::ADDRESS]->text() != ite->Address && !ite->lines[JobField::ADDRESS]->text().isEmpty())
					{
						success = query.exec("UPDATE `DOCHOD` SET `Adres_Firmy` = '" + ite->lines[JobField::ADDRESS]->text() + "'  WHERE `Id_Doch` = " + QString::number(ite->Job_id));
						noChanges = false;
					}
					if (ite->lines[JobField::SALARY]->text() != ite->Salary && !ite->lines[JobField::SALARY]->text().isEmpty())
					{
						success = query.exec("UPDATE `DOCHOD` SET `Kwota` = '" + ite->lines[JobField::SALARY]->text() + "'  WHERE `Id_Doch` = " + QString::number(ite->Job_id));
						noChanges = false;
					}
				}
			}

		}
		//db_holder->close();
		if (noChanges) return;

		auto new_end = std::remove_if(jobs.begin(), jobs.end(), [](JobField * j) {
			bool ans = j->deleteJob;
			if(ans) delete j;
			return ans;
		});
		jobs.erase(new_end, jobs.end());

		db_holder->SetLastError(query.lastError().text());
	}

	if (success) {
		QMessageBox::information(parent, "Success", "Your changes are saved!");
		User->downloadUserData(db_holder);
		new_job_btn->show();
	}
	else {
		QMessageBox::information(parent, "Error", db_holder->GetLastError());
	}
}

void Page_settings::setHidden(bool emitSignal)
{
	isHidden = true;


	for (auto & i : jobs)
		delete i;
	jobs.clear();

	for (auto & ite : parent->widget()->children()) {
		delete ite;
	}
	delete group_box;

	if (emitSignal) {
		emit hide();
	}

}

Page_settings::~Page_settings()
{
	if (!isHidden)
		setHidden(false);
}
