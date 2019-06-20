#include "Page_credit.h"


void Page_credit::showPage()
{
	isHidden = false;

	group_box = new QGroupBox(this->parent);
	main_lay = new QVBoxLayout(group_box);

	group_box->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
	/******************************************************************************/

	credit = new Credit(db_holder->getMlModel());

	lay = new QGridLayout;

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
	
	conditions_field->setText(db_holder->getCreditCondtions());
	conditions_field->setFixedWidth(500);
	ans_lbl->setFixedWidth(500);

	back_btn = new QPushButton("Back", parent);
	//lay->addWidget(back_btn, 0, 0, Qt::AlignLeft);
	lay->addWidget(conditions_lbl, 1, 0, 1, 2, Qt::AlignCenter);
	lay->addWidget(conditions_field, 2, 0, 1, 2, Qt::AlignLeft);
	lay->addWidget(conditions_check, 3, 0, Qt::AlignLeft);
	lay->addWidget(amount_lbl, 4, 0, Qt::AlignRight);
	lay->addWidget(amount_ln, 4, 1, Qt::AlignLeft);
	lay->addWidget(duration_lbl, 5,	0, Qt::AlignRight);
	lay->addWidget(duration_ln, 5, 1, Qt::AlignLeft);
	lay->addWidget(back_btn, 6, 0, Qt::AlignRight);
	lay->addWidget(verify_btn, 6, 1, Qt::AlignCenter);
	lay->addWidget(ans_lbl, 7, 0, 1, 2, Qt::AlignLeft);
	lay->addWidget(ans_btn, 8, 0, 1, 2, Qt::AlignCenter);

	main_lay->addLayout(lay);

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

	int decision = credit->isAbleToGetCredit();
	bool able2get = (decision == -1 ? false : true);
	
	QString ans_str;

	if (!able2get) {
		ans_str = "Unfortunately, we cannot give you any credit.";
	}
	else if (decision == 0) {
		ans_str = "Congratulations! You are able to get this credit!\nThe ratio of interest is " + QString::number(ratio_of_interest) + "% so the total cost is $" + QString::number(amount * (1 + ratio_of_interest / 100.0)) + ".\n\nWould you like to take this?";
	}
	else {
		ans_str = "Unfortunately, we cannot give you as much as you would like to\nget. However, we can offer you $" + QString::number(decision) + ", the ratio of interest is\n" + QString::number(ratio_of_interest) + "% so the total cost of it would be $" + QString::number(decision * (1 + ratio_of_interest / 100.0)) + ".\n\nWould you like to take this?";
		amount = decision;
	}

	ans_lbl->setText(ans_str);

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
