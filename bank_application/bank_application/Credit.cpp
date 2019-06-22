#include "Credit.h"

cv::Mat Credit::predict()
{
	cv::Mat in = (cv::Mat_<float>(1, 3) << salary, (amount / duration), age);
	cv::Mat result;

	net->predict(in, result);

	return result;
}

void Credit::setVals(int age, double salary, double amount, int duration)
{
	this->age = age;
	this->salary = salary;
	this->amount = amount;
	this->duration = duration;
}

int Credit::isAbleToGetCredit()
{
	
	if (predict().at<float>(0) > 0.0)
		return 0;
	while (!(predict().at<float>(0) > 0.0))
	{
		if (amount <= 0)
			return -1;
		amount -= 500;
	}
	return (int)amount;
}