#include "main_win.h"

main_win::main_win(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	setWindowTitle("IO - project");

	main_layout = new QVBoxLayout;
	button = new QPushButton("Click");
	lbl = new QLabel;

	main_layout->addWidget(lbl);
	main_layout->addWidget(button);

	ui.area->setLayout(main_layout);

	this->setLayout(main_layout);

	connect(button, &QPushButton::clicked, this, [this]() {

		QString color = colors.at(std::rand() % colors.size());
		lbl->setText("<center><h1 style='color: " + color + ";'>Hello World!</h1></center>");
	});
}

main_win::~main_win()
{
	delete lbl;
	delete button;
	delete main_layout;
}