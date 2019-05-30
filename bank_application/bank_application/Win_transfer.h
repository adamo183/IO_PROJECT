#pragma once
#include <QWidget>
#include <QCloseEvent>

class Win_transfer :
	public QWidget
{
	
	Q_OBJECT
	
signals:
	void closed();
	
private:
	void closeEvent(QCloseEvent *bar);

public:
	Win_transfer();
	~Win_transfer() {}
};

