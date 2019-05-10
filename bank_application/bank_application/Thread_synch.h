#pragma once
#include <QObject>
#include <QtWidgets/QMainWindow>

class Thread_synch : public QObject
{
	Q_OBJECT

public:
	Thread_synch() : ended(false), started(true) { status = false; }

	bool running() const { return status; }

	const bool ended, started;

public slots:
	void start() { change(true); };
	void stop() { change(false); };

signals:
	void changed(bool val);	/* true - started, false - ended */

private:
	bool status = false;
	void change(bool b) {
		if (status != b) {
			status = b;
			emit changed(b);
		}
	}
};