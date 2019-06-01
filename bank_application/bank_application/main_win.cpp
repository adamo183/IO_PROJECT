#include "main_win.h"

main_win::main_win(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	setWindowTitle("My bank");
	setWindowIcon(QIcon("media/icon.ico"));

	// wyglad
	this->setFixedSize(800, 600);
	centralWidget()->layout()->setContentsMargins(0, 0, 0, 0);
	statusBar()->hide();
	ui.mainToolBar->hide();

	QFile cssFile("media/styleSheet.css");
	QString css = cssFile.open(QFile::ReadOnly) ? QString(cssFile.readAll()) : "";
	cssFile.close();

	ui.main_scrollArea->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

	user = new account;

	// strony
	page_sign_in = new Page_sign_in(ui.main_scrollArea, &db_holder, css, user);
	page_general_view = new Page_general_view(ui.main_scrollArea, &db_holder, css, user);
	page_credit = new Page_credit(ui.main_scrollArea, &db_holder, css, user);
	page_trans_hist = new Page_Trans_Hist(ui.main_scrollArea, &db_holder, css, user);
	page_settings = new Page_settings(ui.main_scrollArea, &db_holder, css, user);

	page_sign_in->showPage();

	// akcje z podstorn
	connect(page_sign_in, SIGNAL(hide()), page_general_view, SLOT(showPage()));
	connect(page_general_view, SIGNAL(logout()), page_sign_in, SLOT(showPage()));

	connect(page_general_view, SIGNAL(creditPage()), page_credit, SLOT(showPage()));
	connect(page_credit, SIGNAL(hide()), page_general_view, SLOT(showPage()));
	
	connect(page_general_view, SIGNAL(transHistPage()), page_trans_hist, SLOT(showPage()));
	connect(page_trans_hist, SIGNAL(hide()), page_general_view, SLOT(showPage()));

	connect(page_general_view, SIGNAL(settPage()), page_settings, SLOT(showPage()));
	connect(page_settings, SIGNAL(hide()), page_general_view, SLOT(showPage()));

	connect(page_general_view, &Page::setCloseAble, this, [this](bool var) { closeAble = var; });
	connect(page_trans_hist, &Page::setCloseAble, this, [this](bool var) { closeAble = var; });
}

main_win::~main_win() {
	//delete main_layout;??
	delete page_sign_in;
	delete page_general_view;
}
void main_win::closeEvent(QCloseEvent * bar) {

	if (closeAble) {
		bar->accept();
	}
	else {
		bar->ignore();
	}
};
