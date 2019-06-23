#pragma once
#include <QWidget>
#include <QCloseEvent>
#include <QScrollArea>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QPlainTextEdit>
#include <QIcon>
#include <QMessageBox>

#include <vector>

#include "Transfer.h"
#include "account.h"
#include "DB_Holder.h"

class Win_transfer :
	public QScrollArea
{
	
	Q_OBJECT
	
signals:
	void closed();

private slots:
	void send_slot();
	
private:
	void closeEvent(QCloseEvent *bar);

	const QString & css;

	DB_Holder * db;
	account * user;

	QGroupBox group_box;
	QVBoxLayout main_lay;
	QHBoxLayout bottom_lay;

	enum {Rec_Acc_No, Amount, Title, Rec_Name, Rec_Address};
	
	std::vector<QString> names = {"Receiver account number", "How much?", "Title", "Receiver name", "Receiver address"};
	std::vector<QLabel *> lbl;
	std::vector<QLineEdit *> ln;
	QPlainTextEdit * Title_pte;
	QPlainTextEdit * Address_pte;

	QPushButton send, cancel;

public:
	Win_transfer(DB_Holder * db, account * user, const QString & css = "");
	~Win_transfer();


	void setTitle(const QString & title) { Title_pte->setPlainText(title); };
	void setReceiverName(const QString & name) { ln[Rec_Name - 1]->setText(name); };
	void setReceiverAddress(const QString & address) { Address_pte->setPlainText(address); };
	void setReceiverAccNumber(const QString & accNo) { ln[Rec_Acc_No]->setText(accNo); };
	void setTransferAmount(double amount) { ln[Amount]->setText(QString::number(amount)); };
	void setTransferAmount(const QString & amount) { ln[Amount]->setText(amount); };
};