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
	auto top_bar = new QHBoxLayout;
	auto menu_bton = new QPushButton;
	auto out_bton = new QPushButton;
	
	parent->setLayout(main_lay);
	main_lay->addLayout(top_bar);

	top_bar->addWidget(menu_bton,1,Qt::AlignLeft);
	top_bar->addWidget(out_bton,3,Qt::AlignRight);
	top_bar->setAlignment(Qt::AlignTop);
	
	menu_bton->setObjectName("menu_bton");
	out_bton->setObjectName("out_bton");
	
	//acc frame
	auto acc_lab = new QLabel("My Account");
	auto curr_lab = new QLabel("Current Account");
	acc_lab->setObjectName("acc_lab");
	auto acc_bar = new QVBoxLayout;

	main_lay->addLayout(acc_bar);
	acc_bar->setAlignment(Qt::AlignTop);
	acc_bar->addWidget(acc_lab, 0, Qt::AlignLeft|Qt::AlignTop);
	
	auto data_lay = new QVBoxLayout;
	auto acc_frame = new QGroupBox;

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
