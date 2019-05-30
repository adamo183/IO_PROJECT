#include "Win_transfer.h"



void Win_transfer::closeEvent(QCloseEvent * bar)
{
	emit closed();
	bar->accept();
}

Win_transfer::Win_transfer()
{
	setAttribute(Qt::WA_DeleteOnClose);
	show();
}


