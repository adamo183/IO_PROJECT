#pragma once

#include <QString>
//#include <opencv2/opencv.hpp>

namespace cv {
	class Mat {};
}

class Credit
{
	//Ptr<ANN_MLP> net;
	double amount, salary;
	int age, duration;

	cv::Mat predict();

public:
	Credit(const QString & ml_model) {
		//cv::FileStorage fs(ml_model, cv::FileStorage::READ | cv::FileStorage::MEMORY);
		//net = cv::Algorithm::read<ANN_MLP>(fs.getFirstTopLevelNode());
	};
	void setVals(int age, double salary, double amount, int duration);
	int isAbleToGetCredit();
};

