#include "Page.h"

void Page::wait_for_the_thread_and_hide() {
	setHidden(false);

	connect(&thread_synch, &Thread_synch::changed, this, [&]() {

		if (this->thread_synch.started()) {

			group_box = new QGroupBox;
			main_lay = new QVBoxLayout(group_box);
			lbl_mv = new QLabel;
			lbl_txt = new QLabel(process_descript);
			mv = new QMovie("media/load.gif");

			int width = 100;

			mv->setScaledSize(QSize(width, 100));
			lbl_txt->setFixedWidth(width);
			lbl_mv->setStyleSheet("");
			lbl_mv->setObjectName("movie");
			mv->start();
			lbl_mv->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
			lbl_txt->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
			main_lay->setAlignment(Qt::AlignHCenter);

			lbl_mv->setMovie(mv);

			parent->setWidget(group_box);
			group_box->setLayout(main_lay);
			main_lay->addWidget(lbl_mv);
			main_lay->addWidget(lbl_txt);
			group_box->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
			lbl_mv->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
			lbl_txt->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

			setCSS();

		}

		if (this->thread_synch.finished()) {

			delete lbl_mv;
			delete lbl_txt;
			delete mv;
			delete main_lay;
			delete group_box;

			thread_synch.disconnect();
			
			if (finished_succeed)
				emit hide();
			else {
				showPage();
				QMessageBox::information(nullptr, "ERROR", last_error);
			}
		}

	});

	std::thread T1([this]() {
		finished_succeed = work_in_new_thread();
	});
	T1.detach();
}