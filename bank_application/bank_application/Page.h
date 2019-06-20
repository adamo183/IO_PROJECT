#pragma once


#include "Thread_synch.h"
#include "account.h"

#include <chrono>
#include <thread>

#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QLabel>
#include <QMovie>
#include <QGroupBox>
#include <QScrollArea>
#include <QTextEdit>
#include <QLineEdit>

enum class Thread_signals { HIDE, LOGOUT, CREDIT_PAGE, TRANS_HIST_PAGE, SETT_PAGE };

class Page : public QObject
{
	Q_OBJECT

signals:
	void hide();
	void logout();
	void creditPage();
	void transHistPage();
	void settPage();
	void setCloseAble(bool par);

public slots:

	virtual void showPage() = 0;
	virtual void setHidden(bool emitSignal = true) { emit hide(); };

public:
	Page(QScrollArea *parent, const QString & css) : parent(parent), CSS(css) {};
	virtual ~Page() {};
	bool isVisible() { return !isHidden; };


protected slots:
	void wait_for_the_thread_and_emit_signal(Thread_signals signal2emit = Thread_signals::HIDE);

protected:

	Thread_signals current_signal;

	virtual bool work_in_new_thread() { return true; };
	void setCSS() { parent->setStyleSheet(CSS); };
	void setProcessDescription(const QString & desc) { process_descript = desc; };

	QScrollArea * parent = Q_NULLPTR;
	QGroupBox * group_box = Q_NULLPTR;
	QVBoxLayout * main_lay = Q_NULLPTR;
	QLabel * lbl_mv = Q_NULLPTR;
	QLabel * lbl_txt = Q_NULLPTR;
	QMovie * mv = Q_NULLPTR;
	QString process_descript;
	QString last_error;

	Thread_synch thread_synch;
	std::atomic<bool> finished_succeed = false;
	bool isHidden = true;
	const QString CSS;
};