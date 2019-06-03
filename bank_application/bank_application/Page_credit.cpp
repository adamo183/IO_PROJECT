#include "Page_credit.h"


void Page_credit::showPage()
{
	isHidden = false;

	group_box = new QGroupBox(this->parent);
	main_lay = new QVBoxLayout(group_box);

	group_box->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
	/******************************************************************************/

	credit = new Credit(db_holder->getMlModel());

	conditions_lbl = new QLabel("Read conditions!", parent);
	conditions_field = new QTextBrowser(parent);
	conditions_check = new QCheckBox("Akcept conditions", parent);

	amount_lbl = new QLabel("How much?", parent);
	amount_ln = new QLineEdit(parent);
	duration_lbl = new QLabel("Set duration (in months)", parent);
	duration_ln = new QLineEdit(parent);

	verify_btn = new QPushButton("Verify possibility", parent);

	ans_lbl = new QLabel(parent);
	ans_btn = new QPushButton("Take this", parent);

	duration_ln->setEnabled(false);
	amount_ln->setEnabled(false);
	verify_btn->setEnabled(false);
	
	conditions_field->setText(db_holder->getMlModel());

	back_btn = new QPushButton("Back", parent);
	main_lay->addWidget(back_btn, 0, Qt::AlignLeft);
	main_lay->addWidget(conditions_lbl, 0, Qt::AlignCenter);
	main_lay->addWidget(conditions_field, 0, Qt::AlignLeft);
	main_lay->addWidget(conditions_check, 0, Qt::AlignLeft);
	main_lay->addWidget(amount_lbl, 0, Qt::AlignLeft);
	main_lay->addWidget(amount_ln, 0, Qt::AlignLeft);
	main_lay->addWidget(duration_lbl, 0, Qt::AlignLeft);
	main_lay->addWidget(duration_ln, 0, Qt::AlignLeft);
	main_lay->addWidget(verify_btn, 0, Qt::AlignCenter);
	main_lay->addWidget(ans_lbl, 0, Qt::AlignLeft);
	main_lay->addWidget(ans_btn, 0, Qt::AlignCenter);

	ans_lbl->hide();
	ans_btn->hide();

	connect(conditions_check, &QCheckBox::stateChanged, this, [this](bool chceked) {
	
		if (chceked) {
			duration_ln->setEnabled(true);
			amount_ln->setEnabled(true);
			verify_btn->setEnabled(true);
		}
		else {
			duration_ln->setEnabled(false);
			amount_ln->setEnabled(false);
			verify_btn->setEnabled(false);
			ans_lbl->hide();
			ans_btn->hide();
		}
	});

	connect(back_btn, &QPushButton::clicked, this, [this]() {
		setHidden();
	});

	connect(verify_btn, &QPushButton::clicked, this, [this]() { verify_ans(); });
	connect(ans_btn, &QPushButton::clicked, this, [this]() { take_credit(); });



	/******************************************************************************/
	parent->setWidget(group_box);

	setCSS();
}

void Page_credit::verify_ans() {

	if (amount_ln->text().isEmpty() || duration_ln->text().isEmpty()) {
		QMessageBox::information(parent, "Empty fields", "Fill empty fields!");
		return;
	}

	amount = amount_ln->text().replace(",", ".").toDouble();
	duration = duration_ln->text().toInt();

	credit->setVals(User->getAge(), User->getSalarySum(), amount, duration);

	bool able2get = credit->isAbleToGetCredit();

	if (ans_lbl->isHidden())
		ans_lbl->show();
	if (ans_btn->isHidden() && able2get)
		ans_btn->show();
	if (!ans_btn->isHidden() && !able2get)
		ans_btn->hide();
}

void Page_credit::take_credit() {

	QString ans = Transfer::TakeCredit(db_holder, User, amount, ratio_of_interest, duration);

	QMessageBox::information(parent, "Answer", ans);

	User->getUserData(db_holder);

	setHidden();
}

void Page_credit::setHidden(bool emitSignal)
{
	isHidden = true;


	for (auto & ite : parent->widget()->children()) {
		delete ite;
	}
	delete group_box;
	delete credit;

	if (emitSignal) {
		emit hide();
	}

}

Page_credit::~Page_credit()
{
	if (!isHidden)
		setHidden(false);
}
