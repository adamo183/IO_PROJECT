#pragma once

#include <atomic>

#include <QObject>
#include <QtWidgets/QMainWindow>

class Thread_synch : public QObject
{
	Q_OBJECT

public:

	bool running() const { return state; }

	bool started()	const { return state ? true : false; };
	bool finished()	const { return state ? false : true; };

public slots:
	void start() { change(true); };
	void stop() { change(false); };

signals:
	void changed();		

private:
	std::atomic<bool> state = false;

	void change(bool b) {
		if (state != b) {
			state = b;
			emit changed();
		}
	}
};