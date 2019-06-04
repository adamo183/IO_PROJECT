#include "Page_settings.h"



void Page_settings::showPage()
{
	isHidden = false;

	group_box = new QGroupBox(this->parent);
	main_lay = new QVBoxLayout(group_box);

	group_box->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
	/******************************************************************************/




	lbl = new QLabel("Settings");
	main_lay->addWidget(lbl, 0, Qt::AlignCenter);

	btn = new QPushButton("Cancel");
	main_lay->addWidget(btn, 0, Qt::AlignLeft);


	connect(btn, &QPushButton::clicked, this, [this]() {
		setHidden();
	});


	/******************************************************************************/
	parent->setWidget(group_box);

	setCSS();
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
