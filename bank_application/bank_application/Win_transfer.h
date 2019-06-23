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

/**
* Klasa odpowiedzialna za okno do wykonywania przelewów.
*/
class Win_transfer :
	public QScrollArea
{
	
	Q_OBJECT
	
signals:
	/** Sygnał emitowany przy zamykaniu okna.
	*/
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

	/** Konstruktor inicjalizujący.
	*	@param db - obiekt bazy danych.
	*	@param user - obiekt użytkownika.
	*	@param css - arkusz stylów CSS.
	*/
	Win_transfer(DB_Holder * db, account * user, const QString & css = "");

	/** Destruktor zwalniający dynamicznie zaalokowaną pamięć.
	*/
	~Win_transfer();


	/** Setter ustawiający tytuł przelewu.
	* @param title - tytuł przelewu.
	*/
	void setTitle(const QString & title) { Title_pte->setPlainText(title); };

	/** Setter ustawiający nazwę odbiorcy przelewu.
	* @param name - nazwa odbiorcy.
	*/
	void setReceiverName(const QString & name) { ln[Rec_Name - 1]->setText(name); };

	/** Setter ustawiający adres odbiorcy przelewu.
	* @param address - adres odbiorcy.
	*/
	void setReceiverAddress(const QString & address) { Address_pte->setPlainText(address); };

	/** Setter ustawiający numer konta odbiorcy przelewu.
	* @param accNo - numer konta.
	*/
	void setReceiverAccNumber(const QString & accNo) { ln[Rec_Acc_No]->setText(accNo); };

	/** Setter ustawiający kwotę przelewu.
	* @param amount - kwota.
	*/
	void setTransferAmount(double amount) { ln[Amount]->setText(QString::number(amount)); };

	/** Setter ustawiający kwotę przelewu.
	* @param amount - kwota.
	*/
	void setTransferAmount(const QString & amount) { ln[Amount]->setText(amount); };
};