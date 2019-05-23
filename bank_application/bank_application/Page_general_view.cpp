#include "Page_general_view.h"


void Page_general_view::showPage()
{
	isHidden = false;
	/*
	group_box = new QGroupBox;
	main_lay = new QVBoxLayout(group_box);
	lbl = new QLabel;
	
	parent->setWidget(group_box);
	group_box->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

	auto ansPair = db_holder->GetTest();
	QString ans = ansPair.first.toString("yyyy-MM-dd hh:mm:ss") + "<br/><h1>" + ansPair.second + "</h1>";

	lbl->setText(ans);
	main_lay->addWidget(lbl);
	*/
	//top bar 
	group_box = new QGroupBox;
	main_lay = new QVBoxLayout(group_box);

	auto topWigdet = new QWidget;
	auto top_bar = new QHBoxLayout(topWigdet);
	auto menu_bton = new QPushButton("Menu");
	auto out_bton = new QPushButton("Logout");
	
	parent->setLayout(main_lay);
	main_lay->addWidget(topWigdet);

	top_bar->addWidget(menu_bton,1,Qt::AlignLeft);
	top_bar->addWidget(out_bton,3,Qt::AlignRight);
	top_bar->setAlignment(Qt::AlignTop);
	
	menu_bton->setObjectName("menu_bton");
	out_bton->setObjectName("out_bton");
	topWigdet->setFixedHeight(50);
	//acc frame
	auto acc_lab = new QLabel("My Account");
	auto curr_lab = new QLabel("Current Account");
	curr_lab->setObjectName("curr_lab");
	acc_lab->setObjectName("acc_lab");
	auto acc_bar = new QVBoxLayout;

	main_lay->addLayout(acc_bar);
	acc_bar->setAlignment(Qt::AlignTop);
	acc_bar->addWidget(acc_lab, 0, Qt::AlignLeft|Qt::AlignTop);
	

	auto box_layout = new QHBoxLayout;
	auto data_lay = new QGridLayout;
	acc_bar->addLayout(box_layout);
	box_layout->setAlignment(Qt::AlignTop);
	
	auto acc_frame = new QGroupBox;
	box_layout->addWidget(acc_frame);
	acc_frame->setLayout(data_lay);
	auto money = new QLabel("$9999");
	auto trans_name_1 = new QLabel("Transfer_1");
	auto trans_value_1 = new QLabel("$9999");

	auto trans_name_2 = new QLabel("Transfer_2");
	auto trans_value_2 = new QLabel("$9999");

	auto acc_view = new QPushButton("Account Overview");
	acc_frame->setObjectName("acc_frame");
	data_lay->setAlignment(Qt::AlignTop);

	data_lay->addWidget(curr_lab, 0, 0, Qt::AlignTop | Qt::AlignLeft);
	data_lay->addWidget(money, 1, 0,Qt::AlignLeft);
	data_lay->addWidget(trans_name_1,3,0);
	data_lay->addWidget(trans_value_1, 3, 1);
	data_lay->addWidget(trans_name_2, 4, 0);
	data_lay->addWidget(trans_value_2, 4, 1);
	data_lay->addWidget(acc_view, 5, 0,1,2);
	acc_frame->setFixedWidth(200);

	//quick transfer
	auto quick_wid = new QGroupBox;
	auto quick_lab = new QLabel("Quick Transfer");
	quick_lab->setObjectName("quick_lab");
	auto quick_grid = new QGridLayout(quick_wid);
	main_lay->addWidget(quick_lab);
	main_lay->addWidget(quick_wid);
	quick_lab->setFixedSize(200,30);
	quick_wid->setObjectName("quick_wid");
	auto iwant_transf = new QLabel("I want to transfer..");
	auto from = new QLabel("From this account..");
	auto to = new QLabel("To this account..");

	auto transf_field = new QLineEdit;
	auto from_field = new QLineEdit;
	auto to_field = new QLineEdit;

	quick_grid->addWidget(iwant_transf, 0, 0);
	quick_grid->addWidget(from, 0, 1);
	quick_grid->addWidget(to, 0, 2);

	quick_grid->addWidget(transf_field, 1, 0);
	quick_grid->addWidget(from_field,1,1);
	quick_grid->addWidget(to_field, 1, 2);
	

	setCSS();
}
void Page_general_view::setHidden(bool emitSignal) {
	isHidden = true;

	delete lbl;
	delete main_lay;
	delete group_box;

	if (emitSignal) {
		emit hide();
	}

};

Page_general_view::~Page_general_view()
{
	if (!isHidden) {
		setHidden(false);
	}
}
