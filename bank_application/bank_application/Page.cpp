#include "Page.h"

void Page::wait_for_the_thread_and_emit_signal(Thread_signals signal2emit) {
	setHidden(false);
	current_signal = signal2emit;

	connect(&thread_synch, &Thread_synch::changed, this, [&]() {

		if (this->thread_synch.started()) {

			group_box = new QGroupBox(parent);
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

			
			main_lay->addWidget(lbl_mv);
			main_lay->addWidget(lbl_txt);
			group_box->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
			lbl_mv->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
			lbl_txt->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

			group_box->setLayout(main_lay);
			parent->setWidget(group_box);

			setCSS();

		}

		if (this->thread_synch.finished()) {

			delete lbl_mv;
			delete lbl_txt;
			delete mv;
			delete main_lay;
			delete group_box;
			
			thread_synch.disconnect();
			
			if (finished_succeed) {
				if (this->current_signal == Thread_signals::HIDE) emit hide();
				if (this->current_signal == Thread_signals::LOGOUT) emit logout();
				if (this->current_signal == Thread_signals::CREDIT_PAGE) emit creditPage();
				if (this->current_signal == Thread_signals::TRANS_HIST_PAGE) emit transHistPage();
				if (this->current_signal == Thread_signals::SETT_PAGE) emit settPage();
			}
			else {
				showPage();
				QMessageBox::information(parent, "ERROR", last_error);
			}
		}

	});

	std::thread T1([this]() {
		thread_synch.start();

		finished_succeed = work_in_new_thread();

		thread_synch.stop();
	});
	T1.detach();
}