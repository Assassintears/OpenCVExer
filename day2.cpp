#include "opencv2\core.hpp"
#include "opencv2\highgui.hpp"
#include "opencv2\objdetect.hpp"
#include "opencv2\imgproc.hpp"

#include <iostream>
#include <string>
#include <vector>

int main()
{
	cv::String zhao = "赵丽颖.jpg";
	cv::String da = "11.jpg";

	cv::Mat srcZhao = cv::imread(zhao);
	cv::Mat srcDa = cv::imread(da);

	////通道分割
	//std::vector<cv::Mat> splitZhao, splitDa;
	//cv::split(srcZhao, splitZhao);
	//cv::split(srcDa, splitDa);

	//ROI提取
	//srcZhao(cv::Rect(100, 100, 100, 100)).copyTo(srcDa(cv::Rect(100,100,100,100)));
	/*cv::Mat roiZhao = srcZhao(cv::Rect(0, 0, srcZhao.cols, 650)).clone();

	cv::Mat roiDa = srcDa(cv::Rect(0, 180, srcDa.cols - 150, 300));*/

	cv::CascadeClassifier faceDetector;
	cv::String xml = "../../../thirdParty/OpenCV400/etc/haarcascades/haarcascade_frontalface_alt2.xml";
	bool ok = faceDetector.load(xml);
	if (!ok)
	{
		std::cout << "加载Haar检测器模型失败\n";
		return 0;
	}
	std::vector<cv::Rect> Zhaofaces, Dafaces;
	faceDetector.detectMultiScale(srcZhao, Zhaofaces);
	faceDetector.detectMultiScale(srcDa, Dafaces);
	cv::Mat dst = srcZhao.clone();
	cv::RNG rng;
	for (std::vector<cv::Rect>::iterator it = Zhaofaces.begin();
		it < Zhaofaces.end();)
	{
		if (it->height < 150)
		{
			it = Zhaofaces.erase(it);
			continue;
		}
		else
		{
			cv::rectangle(dst, *it,
				cv::Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)));
			++it;
		}
	}

	//取ROI
	cv::Mat roiZhao = srcZhao(Zhaofaces[0]);

	cv::Mat roiDa = srcDa(Dafaces[0]);
	cv::Mat dest, dest1;
	cv::resize(roiZhao, dest, roiDa.size());
	//dest.copyTo(roiDa);
	double alpha = 0.7, belta = 0.3;
	cv::addWeighted(dest, alpha, roiDa, belta, 0, dest1);
	dest1.copyTo(roiDa);

	cv::String winName = "test";
	cv::namedWindow(winName, cv::WINDOW_GUI_NORMAL);
	cv::imshow(winName, srcDa);
	cv::waitKey();

	return 0;
}
