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

/**
* Enum signałów jakie mogą zostać wyemitowane po zakończeniu pracy wątku pracującego.
*/
enum class Thread_signals { 
	/**
	* Ukrywanie bieżącej strony.
	*/
	HIDE, 
	/**
	* Wylogowywanie użytkownika.
	*/
	LOGOUT, 
	/**
	* Wyświetlenie strony od kredytów.
	*/
	CREDIT_PAGE, 
	/**
	* Wyświetlenie strony historii transakcji.
	*/
	TRANS_HIST_PAGE, 
	/**
	* Wyświetlenie strony ustawień.
	*/
	SETT_PAGE 
};

/** 
* Klasa bazowa dla stron.
*/
class Page : public QObject
{
	Q_OBJECT

private:

	QLabel * lbl_mv = Q_NULLPTR;
	QLabel * lbl_txt = Q_NULLPTR;
	QMovie * mv = Q_NULLPTR;
	std::atomic<bool> finished_succeed = false;

signals:
	/** Syganał ukrywający stronę.
	*/
	void hide();

	/** Sygnał wylogowywujący.
	*/
	void logout();

	/** Sygnał wyświetlający stronę od kredytów.
	*/
	void creditPage();

	/** Sygnał wyświetlający stronę historii transakcji.
	*/
	void transHistPage();

	/** Sygnał wyświetlający stronę ustawień.
	*/
	void settPage();

	/** Sygnał ustawiający zamykalność bieżącego okna.
	*	@param true - okno możliwe do zamknięcia, false - brak możliwości zamknięcia okna.
	*/
	void setCloseAble(bool par);

public slots:
	/** Slot wyświetlający bieżącą stronę.
	*/
	virtual void showPage() = 0;

	/** Slot ukrywający bieżącą stronę.
	*	@param true - emituje sygnał ukrycia strony, false - nie emituje sygnału ukrycia strony.
	*/
	virtual void setHidden(bool emitSignal = true) { emit hide(); };

public:
	/** Konstruktor inicjalizujący.
	*	@param parent - przodek obiektu.
	*	@param css - arkusz css.
	*/
	Page(QScrollArea *parent, const QString & css) : parent(parent), CSS(css) {};

	/** Wirtualny destruktor.
	*/
	virtual ~Page() {};

	/** Metoda sprawdzająca czy bieżąca strona jest widoczna.
	*	@return true - jest widoczna, false - jest aktualnie ukryta.
	*/
	bool isVisible() { return !isHidden; };


protected slots:
	/** Slot inicjalizujący wykonanie zadanej pracy w nowym wątku, oraz emisję sygnału.
	*	@param signal2emit Sygnał który ma zostać wyemitowany po zakączeniu pracy przez wątek pracujący, domyślnie sygnał ukrywania strony.
	*/
	void wait_for_the_thread_and_emit_signal(Thread_signals signal2emit = Thread_signals::HIDE);

protected:

	/**
	* Sygnał jaki zostanie wyemitowany po zakończeniu pracy przez wątek pracujący.
	*/
	Thread_signals current_signal;

	/** Metoda w której wykonywana jest praca czasochłonna
	*	@return true - opracja zakończona sukcesem, false - wystąpił błąd. 
	*/
	virtual bool work_in_new_thread() { return true; };

	/** Metoda ustawiająca style biażącej strony na podstawie CSS.
	*/
	void setCSS() { parent->setStyleSheet(CSS); };

	/** Metoda nadająca opis procesu wykonywanego w wątku pracującym.
	*	@param desc - opis procesu.
	*/
	void setProcessDescription(const QString & desc) { process_descript = desc; };

	/**
	* Przodek bieżącej strony.
	*/
	QScrollArea * parent = Q_NULLPTR;

	/**
	* Widget główny bieżącej strony.
	*/
	QGroupBox * group_box = Q_NULLPTR;

	/**
	* Główny layout strony.
	*/
	QVBoxLayout * main_lay = Q_NULLPTR;

	/**
	* Opis wykonywanego procesu po ukryciu strony.
	*/
	QString process_descript;

	/**
	* Opis ostatniego błędu.
	*/
	QString last_error;

	/**
	* Arkusz CSS.
	*/
	const QString CSS;

	/**
	* Obiek odpowidzialny za synchronizację GUI oraz wątku pracującego.
	*/
	Thread_synch thread_synch;

	/**
	* Flaga czy aktualna strona jest ukryta. True - jest ukryta, false - nie jest ukryta.
	*/
	bool isHidden = true;
};