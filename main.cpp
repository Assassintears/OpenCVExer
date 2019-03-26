#include "opencv2\core.hpp"
#include "opencv2\highgui.hpp"
#include "opencv2\imgproc.hpp"

#include <iostream>
#include <string>

int main()
{
	const cv::String filePath = "赵丽颖.jpg";
	cv::Mat src = cv::imread(filePath);
	if (src.empty())
	{
		std::cout << "打开文件失败\n";
		return 0;
	}
	std::cout << src.dims << "\n";
	cv::Mat gray;
	cv::cvtColor(src, gray, cv::COLOR_BGR2GRAY);

	//使用Mat对象的成员step和data访问元素
	//Mat对象的data指针指向uchar的值
	//注意：指针存储的是地址，地址本身是uchar类型的，
	//不管指针指向的内容是什么类型的
	//参考：《OpenCV算法精解》P28
	uchar pix = *(gray.data + 3 * gray.step[0] + 4 * gray.step[1]);

	cv::Mat mat = (cv::Mat_<float>(3, 3) << 1, 2, 3,
											4, 5, 6,
											7, 8, 9);
	float floatp = *((float*)(mat.data + 2 * mat.step[0] + 2 * mat.step[1]));

	//Mat的N中初始化方式（N中构造函数）
	// 1. 指定行列类型
	cv::Mat mat1(3, 4, CV_8U);//指定了Mat对象的大小和数据类型，并没有初始化
	// 2. 使用size指定大小和类型‘
	cv::Mat mat2(cv::Size(4, 3), CV_8U);//结果同1，注意Size的行列次序是反的
	// 3. 指定大小和数据类型并使用Scalar赋初值
	cv::Mat mat3(3, 4, CV_8U, cv::Scalar(0));
	cv::Mat mat4(cv::Size(4, 3), CV_8U, cv::Scalar(0));

	// 4. 数组初始化
	int arr[4][3] = { {1, 2, 3}, {4, 5, 6}, {6, 7, 8}, {1, 2, 3} };
	cv::Mat mat5(4, 3, CV_32S, (int*)arr);

	return 0;
}
