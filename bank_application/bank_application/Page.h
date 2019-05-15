#pragma once

#include "DB_Holder.h"
#include "Thread_synch.h"

#include <chrono>
#include <thread>

#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QLabel>
#include <QMovie>
#include <QGroupBox>
#include <QScrollArea>

class Page : public QObject
{
	Q_OBJECT

signals:
	void hide();

public slots:
	virtual void showPage() = 0;
	virtual void setHidden(bool emitSignal = true) { emit hide(); };

protected slots:
	void wait_for_the_thread_and_hide();

public:
	Page(QScrollArea *parent, const QString & css ) : parent(parent), CSS(css) {};
	virtual ~Page() {};

protected:

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