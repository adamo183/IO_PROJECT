#pragma once

#include <atomic>
#include <QObject>

/**
* Klasa odpowiedzialna za synchronizację wątków gui oraz wykonującego czasochłonne zadanie.
*/
class Thread_synch : public QObject
{
	Q_OBJECT

public:

	/** Metoda zwracająca status wątku pracującego.
	* @return true - pracuje, false - praca zakończona.
	*/
	bool running() const { return state; }

	/** Metoda zwracająca czy wątek pracujący zaczął pracę.
	* @return Czy wątek zaczął pracę, true - tak.
	*/
	bool started()	const { return state ? true : false; };
	 
	/** Metoda zwracająca czy wątek pracujący zakończył pracę.
	* @return Czy wątek zakończył pracę, true - tak.
	*/
	bool finished()	const { return state ? false : true; };

public slots:
	/** Slot emitujący sygnał początku pracy.
	*/
	void start() { change(true); };

	/** Slot emitujący sygnał końca pracy.
	*/
	void stop() { change(false); };

signals:
	/** Sygnał zmiany statusu wątku pracującego.
	*/
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