#pragma once

#include <QString>
#include <opencv2/opencv.hpp>


class Credit
{
	cv::Ptr<cv::ml::ANN_MLP> net;
	double amount, salary;
	int age, duration;

	cv::Mat predict();

public:
	Credit(const QString & ml_model) {
		cv::FileStorage fs(ml_model.toStdString(), cv::FileStorage::READ | cv::FileStorage::MEMORY);
		net = cv::Algorithm::read<cv::ml::ANN_MLP>(fs.getFirstTopLevelNode());
	};
	void setVals(int age, double salary, double amount, int duration);
	int isAbleToGetCredit();
};

