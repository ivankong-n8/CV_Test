//#include "stdafx.h"
#include "AlgoHeader.hpp"
#include <algorithm>
#include "HistBalanceApi.h"

// OpenCV Test.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
using namespace cv;
using namespace std;

double alpha = 0;
double beta = 0;

//Mat  automatic_brightness_and_contrast(Mat& image, double& alpha, double& beta, int clip_hist_percent = 3)
//{
//	Mat grayImg;
//	cvtColor(image, grayImg, COLOR_BGR2GRAY);
//	int channels[] = { 0 };
//	Mat hist;
//	const int histSize[] = { 256 };
//	float range[] = { 0,256 };
//	const float* ranges[] = { range };
//	calcHist(&grayImg, 1, channels, Mat(), hist, 1, histSize, ranges, true, false);
//	double accumulator[256];
//	accumulator[0] = (hist.at<float>(0, 0));
//	double  temp = 0;
//	double maximum;
//	int maximum_gray = 0;;
//	int	minimum_gray = 0;
//	for (int i = 1; i < 256; i++)
//	{
//		temp = (hist.at<float>(i, 0));
//		/*	cout << temp << endl;*/
//		accumulator[i] = accumulator[i - 1] + temp;
//	}
//	maximum = accumulator[255];
//	clip_hist_percent *= (maximum / 100.0);
//	clip_hist_percent /= 2.0;
//	while (accumulator[minimum_gray] < clip_hist_percent)
//	{
//		minimum_gray += 1;
//	}
//	maximum_gray = 255;
//	while (accumulator[maximum_gray] >= (maximum - clip_hist_percent))
//	{
//		maximum_gray -= 1;
//	}
//	if (maximum_gray != minimum_gray)
//	{
//		alpha = ((double)255) / (maximum_gray - minimum_gray);
//		beta = -minimum_gray * alpha;
//		/*alpha = 1.1;
//		beta = 8;*/
//	}
//	else
//	{
//		alpha = 1;
//		beta = 0;
//	}
//	Mat auto_result;
//	convertScaleAbs(image, auto_result, alpha, beta);
//	return auto_result;
//}

//Mat ResizeWithAspectRatio(Mat image, double width, double height, int inter = cv::INTER_AREA)
//{
//	Size dim;
//	double h = image.rows;
//	double w = image.cols;
//	if (width == 0 && height == 0)
//		return image;
//	if (width == 0)
//	{
//		if (height < h)
//		{
//			double	 r = height / float(h);
//			dim.width = int(w * r);
//			dim.height = height;
//		}
//		else
//			return image;
//	}
//	else
//	{
//		if (width < w)
//		{
//			double r = width / float(w);
//			dim.width = width;
//			dim.height = int(h * r);
//		}
//		else
//			return image;
//	}
//	Mat dst;
//	cv::resize(image, dst, dim);
//	return dst;
//}
//
//void Show_Enhanced_Image(string in_filename, int clip_hist_percent = 3)
//{
//	Mat  image = imread(in_filename);
//	if (image.empty())
//	{
//		cout << "加载图片失败" << endl;
//		return;
//	}
//	Mat resultImg;
//	resultImg = automatic_brightness_and_contrast(image, alpha, beta, 3);
//
//	cout << "alpha: " << alpha << endl;
//	cout << "beta: " << beta << endl;
//
//	double  img_resized_width = 800;
//	//Mat	img_resize = ResizeWithAspectRatio(image,  img_resized_width,0);
//	//Mat	result_resize = ResizeWithAspectRatio(auto_result, img_resized_width,0);
//	//	imshow("Original", img_resize);
//	imshow("Original", image);
//	//imshow("Auto_result", result_resize);
//	imshow("Auto_result", resultImg);
//	//imwrite('auto_result.png', auto_result)
//}


int ImgAutoAdjust_test()
{
	//string	file_path = "E:\\DESKTOP\\OpenCV项目\\翻译python代码\\Project1\\H013-T-HS";
	//vector<string> txt_file_name;
	//file_name(file_path, txt_file_name);
	//int	total_num = txt_file_name.size();
	//string test_file_abs_path;
	//for (int i = 0; i < total_num; i++)
	//{
	//	Show_Enhanced_Image(txt_file_name[i]);
	//	waitKey(0);
	//	destroyAllWindows();
	//}
	//Show_Enhanced_Image("E:\\DESKTOP\\OpenCV项目\\翻译python代码\\Project1\\H013-T-HS\\00-01-roi.bmp");

	string path = "test/test2.bmp";
	string path2 = "test/test2rst.bmp";
	Mat img = imread("test/test2.bmp");
	ImgAutoAdjust(path, path2);

	//cvtColor(img, img, COLOR_BGR2GRAY);
	//Mat img_rst;
	//equalizeHist(img, img_rst);

	//namedWindow("test");
	//imshow("test", img);
	//waitKey(0);

	//imshow("test", img_rst);
	//waitKey(0);
	////system("pause");

	//Show_Enhanced_Image("test/test2.bmp");
	//waitKey(0);

	//destroyAllWindows();
	return 0;
}

