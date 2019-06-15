#include "Page_settings.h"

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

	btn = new QPushButton("Cancel");
	auto setBtn = new QPushButton("Save Changes");
	info_lay->addWidget(btn,6,0);
	
	info_lay->addWidget(setBtn, 6, 1);

	 job_table = new QTableView;
	 sql_tbl = new QSqlTableModel;//(this->parent, db_holder->getDB());
	sql_tbl->setTable("DOCHOD");
	sql_tbl->setEditStrategy(QSqlTableModel::OnManualSubmit);
	

	QString filt = "Id_uzytkow = "+ QString::number(User->getUserId());
	sql_tbl->setFilter(filt);
	sql_tbl->select();
	//sql_tbl->setHeaderData(0, Qt::Horizontal, tr("Id_doch"));
	//sql_tbl->setHeaderData(1, Qt::Horizontal, tr("Company name"));
//	sql_tbl->setHeaderData(2, Qt::Horizontal, tr("Company address"));
//	sql_tbl->setHeaderData(0, Qt::Horizontal, tr("Salary"));
	
	main_lay->addWidget(job_table);
	job_table->setModel(sql_tbl);
	job_table->resizeColumnsToContents();

	 submit = new QPushButton("Submit");
	 new_job = new QPushButton("New job");
	 down_btn = new QHBoxLayout;
	main_lay->addLayout(down_btn);
	down_btn->addWidget(submit);
	down_btn->addWidget(new_job);
		
	connect(btn, &QPushButton::clicked, this, [this]() {
		setHidden();
	});
	connect(setBtn, &QPushButton::clicked, this, [this]() {  setNewData(); });


	/******************************************************************************/

	parent->setWidget(group_box);


	setCSS();
}

void Page_settings::setNewData()
{
	if (db_holder->Connect()) {
		QSqlQuery query = QSqlQuery(db_holder->getDB());

		if (name_line->text() != User->getName())
		{
			query.exec("UPDATE `UZYTKOWNIK` SET `Imie` = '"+ name_line->text() + "'  WHERE `Id_Uzytkow` = "+QString::number(User->getUserId()));
			db_holder->SetLastError(query.lastError().text());
		}
		if (surname_line->text() != User->getSurrname())
		{
			query.exec("UPDATE `UZYTKOWNIK` SET `Nazwisko` = '" + surname_line->text() + "'  WHERE `Id_Uzytkow` = " + QString::number(User->getUserId()));
			db_holder->SetLastError(query.lastError().text());
		}
		if (phone_line->text() != User->getPhoneNumber())
		{
			query.exec("UPDATE `UZYTKOWNIK` SET `Nr_Tel` = '" + phone_line->text() + "'  WHERE `Id_Uzytkow` = " + QString::number(User->getUserId()));
			db_holder->SetLastError(query.lastError().text());
		}
		if (doc_line->text() != User->getDocNumber())
		{
			query.exec("UPDATE `UZYTKOWNIK` SET `Nr_Dokumentu` = '" + doc_line->text() + "'  WHERE `Id_Uzytkow` = " + QString::number(User->getUserId()));
			db_holder->SetLastError(query.lastError().text());
		}
		if (addr_line->text() != User->getAdress())
		{
			query.exec("UPDATE `UZYTKOWNIK` SET `Adres` = '" + addr_line->text() + "'  WHERE `Id_Uzytkow` = " + QString::number(User->getUserId()));
			db_holder->SetLastError(query.lastError().text());
		}
	}
}

void Page_settings::setHidden(bool emitSignal)
{
	isHidden = true;


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
