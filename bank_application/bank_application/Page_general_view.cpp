#include "Page_general_view.h"


void Page_general_view::showPage()
{
	isHidden = false;

	group_box = new QGroupBox;
	main_lay = new QVBoxLayout(group_box);
	lbl = new QLabel;
	
	parent->setWidget(group_box);
	group_box->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

	auto ansPair = db_holder->GetTest();
	QString ans = ansPair.first.toString("yyyy-MM-dd hh:mm:ss") + "<br/><h1>" + ansPair.second + "</h1>";

	lbl->setText(ans);
	main_lay->addWidget(lbl);

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
