#include "opencv2\core.hpp"
#include "opencv2\highgui.hpp"
#include "opencv2\imgproc.hpp"

#include <iostream>
#include <string>

int main()
{
	const cv::String filePath = "����ӱ.jpg";
	cv::Mat src = cv::imread(filePath);
	if (src.empty())
	{
		std::cout << "���ļ�ʧ��\n";
		return 0;
	}
	std::cout << src.dims << "\n";
	cv::Mat gray;
	cv::cvtColor(src, gray, cv::COLOR_BGR2GRAY);

	//ʹ��Mat����ĳ�Աstep��data����Ԫ��
	//Mat�����dataָ��ָ��uchar��ֵ
	//ע�⣺ָ��洢���ǵ�ַ����ַ������uchar���͵ģ�
	//����ָ��ָ���������ʲô���͵�
	//�ο�����OpenCV�㷨���⡷P28
	uchar pix = *(gray.data + 3 * gray.step[0] + 4 * gray.step[1]);

	cv::Mat mat = (cv::Mat_<float>(3, 3) << 1, 2, 3,
											4, 5, 6,
											7, 8, 9);
	float floatp = *((float*)(mat.data + 2 * mat.step[0] + 2 * mat.step[1]));

	//Mat��N�г�ʼ����ʽ��N�й��캯����
	// 1. ָ����������
	cv::Mat mat1(3, 4, CV_8U);//ָ����Mat����Ĵ�С���������ͣ���û�г�ʼ��
	// 2. ʹ��sizeָ����С�����͡�
	cv::Mat mat2(cv::Size(4, 3), CV_8U);//���ͬ1��ע��Size�����д����Ƿ���
	// 3. ָ����С���������Ͳ�ʹ��Scalar����ֵ
	cv::Mat mat3(3, 4, CV_8U, cv::Scalar(0));
	cv::Mat mat4(cv::Size(4, 3), CV_8U, cv::Scalar(0));

	// 4. �����ʼ��
	int arr[4][3] = { {1, 2, 3}, {4, 5, 6}, {6, 7, 8}, {1, 2, 3} };
	cv::Mat mat5(4, 3, CV_32S, (int*)arr);

	return 0;
}
