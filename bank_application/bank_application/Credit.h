#pragma once

#include <QString>
#include <opencv2/opencv.hpp>

/**
*	Klasa wykorzystująca uczenie maszynowe do podejmowania decyzji kredytowych.
*/
class Credit
{
	cv::Ptr<cv::ml::ANN_MLP> net;
	double amount, salary;
	int age, duration;

	cv::Mat predict();

public:

	/** Konstruktor inicjalizujący uczenie maszynowe gotowym modelem.
	*	@param ml_model - model uczenia maszynowego.
	*/
	Credit(const QString & ml_model) {
		cv::FileStorage fs(ml_model.toStdString(), cv::FileStorage::READ | cv::FileStorage::MEMORY);
		net = cv::Algorithm::read<cv::ml::ANN_MLP>(fs.getFirstTopLevelNode());
	};


	/**	Metoda ustawiająca wartości które potrzebuje model uczenia maszynowego.
	*	@param age - wiek osoby ubiegającej się o kredyt.
	*	@param salary - miesięczne zarobki tej osoby.
	*	@param amount - kwota kredytu o jaką się ubiega ta osoba.
	*	@param duration - ilość miesięcy, kiedy ta osoba będzie spłacać kredyt .
	*/
	void setVals(int age, double salary, double amount, int duration);

	/** Metoda decydująca o możliwości przyznania kredytu, oraz jego wysokości.
	*	@return 0 - jeżeli jest w stanie otrzymać tyle ile rząda,
				-1 - jeżeli nie jest w stanie dostać rzadnego kredytu,
				lub proponowana kwota jaką jest w stanie otrzymać, mniejsza od rządanej.
	*/
	int isAbleToGetCredit();
};