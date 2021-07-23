//#include "stdafx.h"
//#include "AlgoHeader.hpp"
//#include <algorithm>

#include "HistBalanceApi.h"

int ImgAutoAdjust(string OrigImgPath, string outputImgPath) {
	Mat  image = imread(OrigImgPath);
	if (image.empty())
	{
		cout << "¼ÓÔØÍ¼Æ¬Ê§°Ü!" << endl;
		return -1;
	}
	double alpha = 0;
	double beta = 0;
	Mat outputImg = automatic_brightness_and_contrast(image, alpha, beta);
	imwrite(outputImgPath, outputImg);
	destroyAllWindows();
	return 0;
}

Mat  automatic_brightness_and_contrast(Mat image, double& alpha, double& beta, int clip_hist_percent)
{
	Mat grayImg;
	cvtColor(image, grayImg, COLOR_BGR2GRAY);
	int channels[] = { 0 };
	Mat hist;
	const int histSize[] = { 256 };
	float range[] = { 0,256 };
	const float* ranges[] = { range };
	calcHist(&grayImg, 1, channels, Mat(), hist, 1, histSize, ranges, true, false);
	double accumulator[256];
	accumulator[0] = (hist.at<float>(0, 0));
	double  temp = 0;
	double maximum;
	int maximum_gray = 0;;
	int	minimum_gray = 0;
	for (int i = 1; i < 256; i++)
	{
		temp = (hist.at<float>(i, 0));
		/*	cout << temp << endl;*/
		accumulator[i] = accumulator[i - 1] + temp;
	}
	maximum = accumulator[255];
	clip_hist_percent *= (maximum / 100.0);
	clip_hist_percent /= 2.0;
	while (accumulator[minimum_gray] < clip_hist_percent)
	{
		minimum_gray += 1;
	}
	maximum_gray = 255;
	while (accumulator[maximum_gray] >= (maximum - clip_hist_percent))
	{
		maximum_gray -= 1;
	}
	if (maximum_gray != minimum_gray)
	{
		alpha = ((double)255) / (maximum_gray - minimum_gray);
		beta = -minimum_gray * alpha;
		/*alpha = 1.1;
		beta = 8;*/
	}
	else
	{
		alpha = 1;
		beta = 0;
	}
	Mat auto_result;
	convertScaleAbs(image, auto_result, alpha, beta);
	return auto_result;
}