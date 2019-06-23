#include "main_win.h"

main_win::main_win(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	setWindowTitle("My bank");
	setWindowIcon(QIcon("media/icon.ico"));

	// wyglad
	//this->setFixedSize(800, 600);
	centralWidget()->layout()->setContentsMargins(0, 0, 0, 0);
	statusBar()->hide();
	ui.mainToolBar->hide();

	QFile cssFile("media/styleSheet.css");
	QString css = cssFile.open(QFile::ReadOnly) ? QString(cssFile.readAll()) : "";
	cssFile.close();

	ui.main_scrollArea->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

	user = new account;

	// strony
	pages.resize(5);
	pages[SING_IN] = new Page_sign_in(ui.main_scrollArea, &db_holder, css, user);
	pages[GEN_VIEW] = new Page_general_view(ui.main_scrollArea, &db_holder, css, user);
	pages[CREDIT] = new Page_credit(ui.main_scrollArea, &db_holder, css, user);
	pages[TRANS_HIST] = new Page_Trans_Hist(ui.main_scrollArea, &db_holder, css, user);
	pages[SETT] = new Page_settings(ui.main_scrollArea, &db_holder, css, user);
	
	pages[SING_IN]->showPage();

	// akcje z podstorn
	connect(pages[SING_IN], SIGNAL(hide()), pages[GEN_VIEW], SLOT(showPage()));
	connect(pages[GEN_VIEW], SIGNAL(logout()), pages[SING_IN], SLOT(showPage()));

	connect(pages[GEN_VIEW], SIGNAL(creditPage()), pages[CREDIT], SLOT(showPage()));
	connect(pages[CREDIT], SIGNAL(hide()), pages[GEN_VIEW], SLOT(showPage()));
	
	connect(pages[GEN_VIEW], SIGNAL(transHistPage()), pages[TRANS_HIST], SLOT(showPage()));
	connect(pages[TRANS_HIST], SIGNAL(hide()), pages[GEN_VIEW], SLOT(showPage()));

	connect(pages[GEN_VIEW], SIGNAL(settPage()), pages[SETT], SLOT(showPage()));
	connect(pages[SETT], SIGNAL(hide()), pages[GEN_VIEW], SLOT(showPage()));
	connect(pages[SETT], SIGNAL(logout()), pages[SING_IN], SLOT(showPage()));

	connect(pages[GEN_VIEW], &Page::setCloseAble, this, [this](bool var) { closeAble = var; });
	connect(pages[TRANS_HIST], &Page::setCloseAble, this, [this](bool var) { closeAble = var; });


	QCoreApplication::instance()->installEventFilter(this);

	timer = new QTimer(this);

	connect(timer, &QTimer::timeout, this, [this]() {
		
		for (auto & ite : pages) {
			if (ite->isVisible() && dynamic_cast<Page_sign_in *>(ite) == nullptr) {
				ite->setHidden();
				pages[SING_IN]->showPage();
			}
		}

		timer->stop();
	});

	this->showMaximized();
}

main_win::~main_win() {
	
	for (auto & ite : pages)
		delete ite;
}
void main_win::closeEvent(QCloseEvent * bar) {

	if (closeAble) {
		bar->accept();
	}
	else {
		bar->ignore();
	}
};


bool main_win::eventFilter(QObject *watched, QEvent *event) {
	if (event->type() == QEvent::KeyPress || event->type() == QEvent::MouseButtonPress) {

		timer->start(300000);
	}
	return false;
}