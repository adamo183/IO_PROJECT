#include "Page_general_view.h"
#include "Transfer.h"



void Page_general_view::showPage()
{
	isHidden = false;

	bool credit = !User->hasCredit() && User->hasJob();

	/*********************************************************************************/

	//QWidget * parent_widget = new QWidget(parent);
	//parent_widget->setObjectName("parent_widget");
	//parent_widget->setStyleSheet("QWidget#parent_widget { background-color: rgba(0, 0, 0, 0); }");
	
	group_box = new QGroupBox(this->parent);
	main_lay = new QVBoxLayout(group_box);
	menu_layout = new QHBoxLayout(group_box);

	group_box->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);


	if(credit) credit_bton = new QPushButton("Get a credit");
	sett_bton = new QPushButton("Settings");
	out_bton = new QPushButton("Logout");


	
	menu_layout->addWidget(sett_bton, Qt::AlignLeft);
	if (credit) menu_layout->addWidget(credit_bton, Qt::AlignLeft);
	menu_layout->addWidget(out_bton, Qt::AlignRight);

	if (credit) credit_bton->setObjectName("menu_bton");
	sett_bton->setObjectName("menu_bton");
	out_bton->setObjectName("out_bton");
	
	main_lay->addLayout(menu_layout);
	main_lay->addStretch();


	//acc frame
	acc_wgt = new QWidget(group_box);
	acc_grid = new QGridLayout(acc_wgt);

	acc_lab = new QLabel("My Account");
	curr_lab = new QLabel(User->getName()+" "+User->getSurrname());
	curr_lab->setFixedWidth(400);
	curr_lab->setObjectName("curr_lab");
	acc_lab->setObjectName("acc_lab");

	money = new QLabel("$" + QString::number(User->getAccBalance(), 'f', 2));
	money->setMinimumWidth(150);

	acc_view = new QPushButton("Account Overview");

	acc_grid->addWidget(acc_lab, 0, 0, 2, 2, Qt::AlignCenter);
	acc_grid->addWidget(curr_lab, 2, 0, Qt::AlignLeft);
	acc_grid->addWidget(money, 3, 0, Qt::AlignLeft);
	acc_grid->addWidget(acc_view, 3, 1, Qt::AlignLeft);

	acc_wgt->setLayout(acc_grid);
	main_lay->addWidget(acc_wgt);

	// end of acc frame

	// quick transfer
	quick_wgt = new QWidget(group_box);
	quick_wgt->setStyleSheet("QWidget { background-color: #00F; }");
	quick_grid = new QGridLayout(quick_wgt);

	quick_lab = new QLabel("Quick Transfer");
	quick_lab->setObjectName("quick_lab");
	iwant_transf = new QLabel("I want to transfer:");
	from = new QLabel("To this account:");
	to = new QLabel("Transaction title:");
	send = new QPushButton("Send");
	showMore = new QPushButton("See more..");

	transf_field = new QLineEdit;
	title_field = new QLineEdit;
	to_field = new QLineEdit("76542265022222222000001001");

	quick_grid->addWidget(quick_lab, 0, 0, 2, 2, Qt::AlignCenter);
	quick_grid->addWidget(iwant_transf, 2, 0, Qt::AlignRight);
	quick_grid->addWidget(transf_field, 2, 1, Qt::AlignLeft);
	quick_grid->addWidget(from, 3, 0, Qt::AlignRight);
	quick_grid->addWidget(to_field, 3, 1, Qt::AlignLeft);
	quick_grid->addWidget(to, 4, 0, Qt::AlignRight);
	quick_grid->addWidget(title_field, 4, 1, Qt::AlignLeft);
	quick_grid->addWidget(showMore, 5, 0, Qt::AlignRight);
	quick_grid->addWidget(send, 5, 1, Qt::AlignLeft);

	quick_wgt->setLayout(quick_grid);

	main_lay->addWidget(quick_wgt);

	// end of quick transfer

	group_box->setLayout(main_lay);
	parent->setWidget(group_box);



	/*********************************************************************************/

	connect(send, &QPushButton::clicked, this, [this]() { send_transfer(); });
	connect(showMore, &QPushButton::clicked, this, [this]() { new_transfer(); });
	connect(out_bton, &QPushButton::clicked, this, [this]() {
		setHidden(false);
		emit logout();
	});

	setProcessDescription("Please wait!");

	if (credit) {
		connect(credit_bton, &QPushButton::clicked, this, [this]() {
			setHidden(false);
			current_work = Thread_signals::CREDIT_PAGE;
			wait_for_the_thread_and_emit_signal(Thread_signals::CREDIT_PAGE);
		});
	}

	connect(acc_view, &QPushButton::clicked, this, [this]() {
		setHidden(false);
		current_work = Thread_signals::TRANS_HIST_PAGE;
		wait_for_the_thread_and_emit_signal(Thread_signals::TRANS_HIST_PAGE);
	});

	connect(sett_bton, &QPushButton::clicked, this, [this]() {
		setHidden(false);
		emit settPage();
	});
	//connect(acc_view,,&QPushButton::clicked,this,);

	setCSS();
	
}


void Page_general_view::new_transfer() {

	auto setEnable = [this](bool enable) {
		for (auto & ite : parent->children()) {
			QWidget * tmp = dynamic_cast<QWidget *>(ite);
			if (tmp != nullptr)
				tmp->setEnabled(enable);
		}
	};

	setEnable(false);

	win_transfer = new Win_transfer(db_holder, User, CSS);
	win_transfer->setTransferAmount(transf_field->text());
	win_transfer->setReceiverAccNumber(to_field->text());
	win_transfer->setTitle(title_field->text());

	emit setCloseAble(false);

	connect(win_transfer, &Win_transfer::closed, this, [this, setEnable]() {
	
		setEnable(true);
		emit setCloseAble(true);

		transf_field->setText(""); to_field->setText(""); title_field->setText("");

		win_transfer = Q_NULLPTR;
	});
}

void Page_general_view::send_transfer() {

	if (transf_field->text().isEmpty() || title_field->text().isEmpty() || to_field->text().isEmpty()) {
		QMessageBox::information(parent, "Empyt fields", "Fill empty fields!");
		return;
	}

	double amount = transf_field->text().replace(",", ".").toDouble();
	QString to_acc_number = to_field->text();
	QString title = title_field->text();

	if (amount <= 0) {
		QMessageBox::information(parent, " ", "Only positive transfers allowed!");
		return;
	}

	if (to_acc_number.size() != 26) {
		QMessageBox::information(parent, "Wrong number", "Too short account number!");
		return;
	}

	if (to_acc_number == User->getAccNumber()) {
		QMessageBox::information(parent, "Wrong number", "This is yours number!");
		return;
	}

	QString ans = Transfer::QuickTransfer(db_holder, User, amount, to_acc_number, title);

	QMessageBox::information(parent, " ", ans);

	transf_field->setText(""); to_field->setText(""); title_field->setText("");
}

void Page_general_view::setHidden(bool emitSignal) {
	isHidden = true;

	for (auto & ite : parent->widget()->children()) {
		delete ite;
	}

	if (emitSignal) {
		emit hide();
	}

}
bool Page_general_view::work_in_new_thread()
{
	bool download_succeed = false;

	if (current_work == Thread_signals::TRANS_HIST_PAGE) {

		download_succeed = User->DownloadUserTransactions(db_holder);
		if (!download_succeed) last_error = User->getLastError();
	}
	if (current_work == Thread_signals::CREDIT_PAGE) {

		download_succeed = db_holder->downloadMlModel();
		if (!download_succeed) last_error = db_holder->GetLastError();
	}

	std::this_thread::sleep_for(std::chrono::milliseconds(500));

	return download_succeed;
}
;

Page_general_view::~Page_general_view()
{
	if (!isHidden) {
		setHidden(false);
	}
}
