学习OpenCV
======
# 第一天
学习Mat对象的初始化：指定Mat对象的大小和数据类型，通过Scalar或者数组初始化Mat对象的值。
指定Mat对象大小的方式：rows， cols， Size(cols, rows)
指定Mat对象数据类型的方式：CV_8U（uchar），CV_32S（int）， CV_32F（float），CV_64F（double）

* Mat对象数据连续的含义以及data和step的用法如下图所示：<br>
![](https://github.com/Assassintears/OpenCVExer/raw/master/imgs/Mat数据连续性.jpg)  

# 第二天

Mat对象的ROI选择一般通过Mat的复制构造函数复制Mat对象的一部分数据，所以，`Mat对象的复制构造函数生成的Mat对象与原Mat对象共享内存块`，
对ROI的操作会影响原图。利用这一点可：

* 填充边界
```c
cv::Mat src(cv::Size, CV_8UC1, cv::Scalar(0));
cv::Mat roi = src(cv::Rect(cv::Size, width, height));
roi.setTo(1);
```

* 复制logo
```c
cv::Mat src = cv::imread("...");
cv::Mat logo = cv::imread("...");
cv::Mat roi = src(cv::Rect(x, y, logo.Size().width, logo.Size().height));//指定Logo要复制到原图的区域
roi.copyTo(src);
```

    OpenCV人脸检测顺序：

* 包含人脸检测分类器头文件<br>
#include "opencv2/objdetect.h"
<br>
* 加载人脸检测分类器

```
cv::CascadeClassifier faceDetector;//定义分类器对象
cv::String xml = "../../../thirdParty/OpenCV400/etc/haarcascades/haarcascade_frontalface_alt2.xml";//指定模型文件路径
bool ok = faceDetector.load(xml);//读取分类器模型
if (!ok)
{
  std::cout << "加载Haar检测器模型失败\n";
  return 0;
}
```
* 执行检测
```
std::vector<cv::Rect> faces;
faceDetector.detectMultiScale(src, faces);
```
