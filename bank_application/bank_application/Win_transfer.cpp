#include "Win_transfer.h"



void Win_transfer::closeEvent(QCloseEvent * bar)
{
	emit closed();
	bar->accept();
}

Win_transfer::Win_transfer(DB_Holder * db, account * user, const QString & css) :
	db(db),
	user(user),
	css(css),
	main_lay(&group_box)
{
	setAttribute(Qt::WA_DeleteOnClose);
	
	this->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	this->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
	this->setMinimumSize(500, 600);


	setWindowTitle("New Transfer");
	setWindowIcon(QIcon("media/icon.ico"));

	int n = names.size();
	
	lbl.resize(n);
	ln.resize(n - 2);

	auto ln_ite = ln.begin();

	for (int i = 0; i < n; ++i) {

		lbl[i] = new QLabel(names[i]);
		lbl[i]->setFixedHeight(25);
		main_lay.addWidget(lbl[i]);

		if (i == Title) {
			Title_pte = new QPlainTextEdit;
			Title_pte->setMaximumHeight(60);
			main_lay.addWidget(Title_pte);

		}
		else if (i == Rec_Address) {
			Address_pte = new QPlainTextEdit;
			Address_pte->setMaximumHeight(60);
			main_lay.addWidget(Address_pte);
		}
		else {
			*(ln_ite) = new QLineEdit;
			main_lay.addWidget(*(ln_ite++));
		}

	}

	send.setText("Send");
	cancel.setText("Cancel");
	bottom_lay.addWidget(&cancel);
	bottom_lay.addWidget(&send);

	main_lay.addLayout(&bottom_lay);

	group_box.setLayout(&main_lay);
	group_box.setFixedSize(400, 500);
	group_box.setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

	setWidget(&group_box);
	
	setStyleSheet(css);
	show();

	connect(&send, SIGNAL(clicked()), this, SLOT(send_slot()));
	connect(&cancel, &QPushButton::clicked, this, [this]() {
		this->close();
	});



}

void Win_transfer::send_slot() {
	
	QString accNo = ln[Rec_Acc_No]->text(),
			amount_str = ln[Amount]->text(),
			title = Title_pte->toPlainText(), 
			name = ln[Rec_Name - 1]->text(), 
			address = Address_pte->toPlainText();

	if (accNo.isEmpty() || amount_str.isEmpty() || title.isEmpty() || name.isEmpty() || address.isEmpty()) {
		QMessageBox::information(nullptr, "Empyt fields", "Fill empty fields!");
		return;
	}

	double amount = amount_str.replace(",", ".").toDouble();

	if (amount <= 0) {
		QMessageBox::information(nullptr, " ", "Only positive transfers allowed!");
		return;
	}

	if (accNo.size() != 26) {
		QMessageBox::information(nullptr, "Wrong number", "Too short account number!");
		return;
	}

	QString ans = Transfer::QuickTransfer(db, user, amount, accNo, title, name, address);

	QMessageBox::information(nullptr, " ", ans);

	this->close();
}


Win_transfer::~Win_transfer()
{
	for (auto & ite : lbl)
		delete ite;
	for (auto & ite : ln)
		delete ite;
	delete Address_pte;
	delete Title_pte;
}


