#include "Page_Trans_Hist.h"
#include <cmath>

void Page_Trans_Hist::showPage()
{
	isHidden = false;

	group_box = new QGroupBox(this->parent);
	main_lay = new QVBoxLayout(group_box);

	group_box->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
	/******************************************************************************/

	transactions = User->getTransactions();
	
	trans_tool_box = new QToolBox(parent);
	btn_gr = new QButtonGroup(parent);

	int n = transactions.size();

	trans_wgt_lay.resize(n);
	lbl_btn.resize(n);

	using Tr = account::Transaction;

	for (int i = 0; i < n; ++i) {

		auto & current_trans = transactions[i];

		auto & wgt = trans_wgt_lay[i].first;
		auto & lay = trans_wgt_lay[i].second;
		auto & lbl = lbl_btn[i].first;
		auto & btn = lbl_btn[i].second;

		wgt = new QWidget(trans_tool_box);
		lay = new QGridLayout(wgt);
		btn = new QPushButton("Send" ,wgt);

		QString cont =
			"<div>\n"
			"	<b>Transaction date : </b><br/>\n"
			"	" + std::get<Tr::DATETIME>(current_trans).toString("dd-MM-yyyy hh:mm") + "<br/><br/>\n"
			"	<b>Transaction number : </b> < br/>\n"
			"	" + QString::number(std::get<Tr::ID>(current_trans)) + "<br/> <br/>\n"
			"	<b>Transaction title : </b><br/>\n"
			"	" + std::get<Tr::TITLE>(current_trans) + "<br/><br/>\n"
			"	<b>Transaction amount : </b> <br/>\n"
			"	$ " + QString::number(std::get<Tr::AMOUNT>(current_trans)) + "<br/><br/>\n"
			"	<b>Account number : </b><br/>\n"
			"	" + std::get<Tr::ACC_NO>(current_trans) + " <br/><br/>\n"
			"	<b>Name and address : </b><br/>\n"
			"	" + std::get<Tr::NAME>(current_trans) + " <br/>"
			"	" + std::get<Tr::ADDRESS>(current_trans) + ""
			"</div>";
		lbl = new QLabel(cont, wgt);

		wgt->setObjectName("tool_box_wgt");
		lbl->setObjectName("tool_box_lbl");
		btn->setFixedWidth(80);
		btn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Maximum);
		
		btn_gr->addButton(btn, i);

		lay->addWidget(lbl, 0, 0);
		lay->addWidget(btn, 0, 1);
		
		wgt->setLayout(lay);

		QString item_title = std::get<Tr::DATETIME>(current_trans).toString("ddd dd.MM.yyyy") + "\n" +
							std::get<Tr::NAME>(current_trans) + "\n\t   $ " +
							QString::number(std::get<Tr::AMOUNT>(current_trans));

		trans_tool_box->addItem(wgt, item_title);
		
	}

	trans_tool_box->setMinimumHeight(300 + n*50);
	trans_tool_box->setFixedWidth(400);


	lbl = new QLabel("Transaction History");
	main_lay->addWidget(lbl, 0, Qt::AlignCenter);
	
	btn = new QPushButton("Back");
	main_lay->addWidget(btn, 0, Qt::AlignLeft);


	main_lay->addWidget(trans_tool_box);


	connect(btn, &QPushButton::clicked, this, [this]() {
		setHidden();
	});

	connect(btn_gr, static_cast<void(QButtonGroup::*)(int)>(&QButtonGroup::buttonClicked),
		[=](int id) { 
		send_btn(id);
	});


	/******************************************************************************/
	parent->setWidget(group_box);

	setCSS();
}

void Page_Trans_Hist::send_btn(int i) {

	auto setEnable = [this](bool enable) {
		for (auto & ite : parent->children()) {
			QWidget * tmp = dynamic_cast<QWidget *>(ite);
			if (tmp != nullptr)
				tmp->setEnabled(enable);
		}
	};

	setEnable(false);

	win_transfer = new Win_transfer(db_holder, User, CSS);

	auto current_trans = transactions[i];
	using Tr = account::Transaction;

	win_transfer->setReceiverAccNumber(std::get<Tr::ACC_NO>(current_trans));
	win_transfer->setReceiverName(std::get<Tr::NAME>(current_trans));
	win_transfer->setReceiverAddress(std::get<Tr::ADDRESS>(current_trans));
	win_transfer->setTitle("Re: " + std::get<Tr::TITLE>(current_trans));
	win_transfer->setTransferAmount(abs(std::get<Tr::AMOUNT>(current_trans)));

	emit setCloseAble(false);

	connect(win_transfer, &Win_transfer::closed, this, [this, setEnable]() {

		setEnable(true);
		emit setCloseAble(true);

		win_transfer = Q_NULLPTR;
	});

}

void Page_Trans_Hist::setHidden(bool emitSignal)
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

Page_Trans_Hist::~Page_Trans_Hist()
{
	if (!isHidden)
		setHidden(false);
}
