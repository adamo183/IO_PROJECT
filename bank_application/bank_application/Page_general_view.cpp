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
	
	User->getUserData(db_holder);
	group_box = new QGroupBox;
	main_lay = new QVBoxLayout(group_box);

	topWigdet = new QWidget;
	top_bar = new QHBoxLayout(topWigdet);
	menu_bton = new QPushButton("Menu");
	out_bton = new QPushButton("Logout");
	
	parent->setLayout(main_lay);
	main_lay->addWidget(topWigdet);

	top_bar->addWidget(menu_bton,1,Qt::AlignLeft);
	top_bar->addWidget(out_bton,3,Qt::AlignRight);
	top_bar->setAlignment(Qt::AlignTop);
	
	menu_bton->setObjectName("menu_bton");
	out_bton->setObjectName("out_bton");
	topWigdet->setFixedHeight(50);
	//acc frame
	 acc_lab = new QLabel("My Account");
	 curr_lab = new QLabel(User->getName()+" "+User->gatSurrname());
	 curr_lab->setFixedWidth(200);
	curr_lab->setObjectName("curr_lab");
	acc_lab->setObjectName("acc_lab");
	 acc_bar = new QVBoxLayout;

	main_lay->addLayout(acc_bar);
	acc_bar->setAlignment(Qt::AlignTop);
	acc_bar->addWidget(acc_lab, 0, Qt::AlignLeft|Qt::AlignTop);
	

	 box_layout = new QHBoxLayout;
	 data_lay = new QGridLayout;
	acc_bar->addLayout(box_layout);
	box_layout->setAlignment(Qt::AlignTop);
	
	 acc_frame = new QGroupBox;
	box_layout->addWidget(acc_frame);
	acc_frame->setLayout(data_lay);
	 money = new QLabel("$9999");
	 trans_name_1 = new QLabel("Transfer_1");
	 trans_value_1 = new QLabel("$9999");

	 trans_name_2 = new QLabel("Transfer_2");
	 trans_value_2 = new QLabel("$9999");

	 acc_view = new QPushButton("Account Overview");
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
	 quick_wid = new QGroupBox;
	quick_wid->setFixedHeight(150);
	 quick_lab = new QLabel("Quick Transfer");
	quick_lab->setObjectName("quick_lab");
	 quick_grid = new QGridLayout(quick_wid);
	main_lay->addWidget(quick_lab);
	main_lay->addWidget(quick_wid);
	quick_lab->setFixedSize(200,30);
	quick_wid->setObjectName("quick_wid");
	 iwant_transf = new QLabel("I want to transfer..");
	 from = new QLabel("From this account..");
	 to = new QLabel("To this account..");
	 send = new QPushButton("Send");
	 showMore = new QPushButton("See more..");

	 transf_field = new QLineEdit;
	 from_field = new QLineEdit;
	 to_field = new QLineEdit;

	quick_grid->addWidget(iwant_transf, 0, 0);
	quick_grid->addWidget(from, 0, 1);
	quick_grid->addWidget(to, 0, 2);

	quick_grid->addWidget(transf_field, 1, 0);
	quick_grid->addWidget(from_field,1,1);
	quick_grid->addWidget(to_field, 1, 2);
	quick_grid->addWidget(send, 3, 0);
	quick_grid->addWidget(showMore, 3, 2);

	
	connect(out_bton, &QPushButton::clicked, this, [this]() {
		
		setHidden();
		emit logout();
	});

	setCSS();
	
}
void Page_general_view::setHidden(bool emitSignal) {
	isHidden = true;

	delete lbl;
	delete main_lay;
	delete group_box;
	delete topWigdet;
	delete top_bar;
	delete menu_bton;
	delete out_bton;
	delete acc_lab;
	delete curr_lab;
	delete acc_bar;
	delete box_layout;
	delete data_lay;
	delete acc_frame;
	delete money;
	delete trans_name_1;
	delete trans_value_1;
	delete trans_name_2;
	delete trans_value_2;
	delete acc_view;
	delete quick_wid;
	delete quick_lab;
	delete quick_grid;
	delete iwant_transf;
	delete from;
	delete to;
	delete showMore;
	delete send;
	delete transf_field;
	delete from_field;
	delete to_field;



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
