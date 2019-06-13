#include "Credit.h"


cv::Mat Credit::predict()
{
	/*
	cv::Mat in = (cv::Mat_<float>(1, 3) << salary, (amount / duration), age);
	cv::Mat result;

	net->predict(in, result);

	return result;
	*/

	return cv::Mat();
}

void Credit::setVals(int age, double salary, double amount, int duration)
{
	this->age = age;
	this->salary = salary;
	this->amount = amount;
	this->duration = duration;
}

/** Method decide to give credit
*	@param Age - age of person
*	@param Salary - how much does that person earn per month
*	@param Credit_amount - how much does that person want to get
*	@param Duration - how long time does it take that person to pay back
*	@param ymlModel - machine learning model
*	@return 0 - if is able to get, otherwise proposed amount or -1 if there is no possibility at all
*/
int Credit::isAbleToGetCredit()
{
	/*
		if (predict(Age, Salary, Credit_amount, Duration, ymlModel).at<float>(0) > 0.0)
		return 0;
	while (!(predict(Age, Salary, Credit_amount, Duration, ymlModel).at<float>(0) > 0.0))
	{
		if (Credit_amount <= 0)
			return -1;
		Credit_amount -= 500;
	}
	return (int)Credit_amount;
	*/
	
	return ((rand() % 2) * -1);
}