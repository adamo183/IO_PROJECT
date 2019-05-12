#include "main_win.h"
#include "page_h.h"

main_win::main_win(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	/*
	timer = new QTimer;
	timer->setInterval(300);

	output = new QLabel;
	output->setAlignment(Qt::AlignCenter);
	ui.main_scrollArea->setWidget(output);

	connect(&thread_synch, &Thread_synch::changed, this, [&](bool val) {
	
		if (val == thread_synch.started) {
			output->setText("Pobieram");
			timer->start();
		}

		if (val == thread_synch.ended) {
			output->setText(test_record.first.toString("yyyy-MM-dd hh:mm:ss") + "<br/><h1>" + test_record.second+ "</h1>");
			timer->stop();
		}
	
	});

	connect(timer, &QTimer::timeout, this, [this]() {
	
		output->setText(output->text() + ".");

	});


	std::thread T1([this]() {

		thread_synch.start();
		test_record = db.GetTest();
		std::this_thread::sleep_for(std::chrono::milliseconds(4000));
		thread_synch.stop();

	});
	T1.detach();
	
	
	*/
	Page *login_site = new Page(this);

	window = new QStackedWidget(this);
	window->addWidget(login_site);

	setCentralWidget(window);
	
}
