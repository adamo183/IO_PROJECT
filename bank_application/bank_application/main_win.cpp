#include "main_win.h"

main_win::main_win(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	setWindowTitle("My bank");
	setWindowIcon(QIcon("media/icon.ico"));

	// wyglad
	centralWidget()->layout()->setContentsMargins(0, 0, 0, 0);
	statusBar()->hide();
	ui.mainToolBar->hide();

	QFile cssFile("media/styleSheet.css");
	QString css = cssFile.open(QFile::ReadOnly) ? QString(cssFile.readAll()) : "";
	cssFile.close();

	ui.main_scrollArea->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);


	// strony
	page_sign_in = new Page_sign_in(ui.main_scrollArea, &db_holder, css);
	page_general_view = new Page_general_view(ui.main_scrollArea, &db_holder, css);

	page_sign_in->showPage();

	// akcje z podstorn
	connect(page_sign_in, SIGNAL(hide()), page_general_view, SLOT(showPage()));

}

main_win::~main_win() {
	delete main_layout;
	delete page_sign_in;
	delete page_general_view;
};
