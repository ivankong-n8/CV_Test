//#include "stdafx.h"
#include "AlgoHeader.hpp"
#include <algorithm>

// OpenCV Test.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
using namespace cv;
using namespace std;

int FindMinRange(QuadCoord &Q1, QuadCoord &Q2, int &ImgWitdh, int& ImgHeight) {
	vector<int> listX;
	vector<int> listY;
	listX.push_back(Q1.x1);
	listX.push_back(Q1.x2);
	listX.push_back(Q1.x3);
	listX.push_back(Q1.x4);
	listX.push_back(Q2.x1);
	listX.push_back(Q2.x2);
	listX.push_back(Q2.x3);
	listX.push_back(Q2.x4);
	listY.push_back(Q1.y1);
	listY.push_back(Q1.y2);
	listY.push_back(Q1.y3);
	listY.push_back(Q1.y4);
	listY.push_back(Q2.y1);
	listY.push_back(Q2.y2);
	listY.push_back(Q2.y3);
	listY.push_back(Q2.y4);

	int XmaxValue = *max_element(listX.begin(), listX.end());
	int XminValue = *min_element(listX.begin(), listX.end());

	int YmaxValue = *max_element(listY.begin(), listY.end());
	int YminValue = *min_element(listY.begin(), listY.end());

	Q1.x1-= XminValue;
	Q1.x2-= XminValue;
	Q1.x3-= XminValue;
	Q1.x4-= XminValue;
	Q2.x1-= XminValue;
	Q2.x2-= XminValue;
	Q2.x3-= XminValue;
	Q2.x4-= XminValue;

	Q1.y1-= YminValue;
	Q1.y2-= YminValue;
	Q1.y3-= YminValue;
	Q1.y4-= YminValue;
	Q2.y1-= YminValue;
	Q2.y2-= YminValue;
	Q2.y3-= YminValue;
	Q2.y4-= YminValue;

	ImgWitdh = XmaxValue - XminValue;
	ImgHeight = YmaxValue - YminValue;

	return 0;
}

vector<Point> getPoints(QuadCoord Q1) 
{
	vector<Point> Q1PolygonPoint;
	Q1PolygonPoint.push_back(Point(Q1.x1, Q1.y1));
	Q1PolygonPoint.push_back(Point(Q1.x2, Q1.y2));
	Q1PolygonPoint.push_back(Point(Q1.x3, Q1.y3));
	Q1PolygonPoint.push_back(Point(Q1.x4, Q1.y4));
	return Q1PolygonPoint;
}

void DrawPolygon(Mat inputImage, vector<Point> polygonPoint, bool bIsFill, bool bIsClosed)
{
	vector<vector<Point>> contours;
	contours.push_back(polygonPoint);

	if (bIsFill)
		fillPoly(inputImage, contours, Scalar(255, 255, 255), 8);
	else
		polylines(inputImage, polygonPoint, bIsClosed, Scalar(255, 255, 255), 2, 8);
}

double CalInterOverUnion(QuadCoord Q1, QuadCoord Q2) 
{
	int ImgHeight, ImgWitdh;
	FindMinRange(Q1, Q2, ImgWitdh, ImgHeight);

	Mat Q1Img = Mat::zeros(ImgHeight, ImgWitdh, CV_8UC1);
	Mat Q2Img = Mat::zeros(ImgHeight, ImgWitdh, CV_8UC1);

	namedWindow("Test");
	imshow("Test", Q1Img);
	waitKey();

	imshow("Test", Q2Img);
	waitKey();

	vector<Point> Q1PolygonPoint = getPoints(Q1);
	vector<Point> Q2PolygonPoint = getPoints(Q2);

	//绘制四边形
	DrawPolygon(Q1Img, Q1PolygonPoint, true);
	DrawPolygon(Q2Img, Q2PolygonPoint, true);

	//计算 交集 并集
	Mat interImg, unionImg;
	bitwise_and(Q1Img, Q2Img, interImg);
	bitwise_or(Q1Img, Q2Img, unionImg);

	imshow("Test", interImg);
	waitKey();

	imshow("Test", unionImg);
	waitKey();

	destroyAllWindows();

	double areaInter = countNonZero(interImg);
	double areaUnion = countNonZero(unionImg);

	double ratio = areaInter / areaUnion;
	cout << ratio << endl;
	return ratio;
}

int test_IoU()
{

	//std::string str0 = "./20210608 - LALS and HALS/8-back-LALS.png";
	//std::string str1 = "./20210608 - LALS and HALS/8-back-HALS.png";
	//Mat RstImgHALS = imread(str1, IMREAD_GRAYSCALE);
	//Mat RstImgLALS = imread(str0, IMREAD_GRAYSCALE);
	//
	////Mat finaLabels, finaStatus, finaCenter;
	////int totalNumHLAS = connectedComponentsWithStats(RstImgHALS, finaLabels, finaStatus, finaCenter);


	//Mat finalDefectsImg, dustImg;
	//ExtractDustImg(RstImgHALS, RstImgLALS, finalDefectsImg, dustImg);

	//imwrite("DustImg.png", dustImg);
	//imwrite("finalDefectsImg.png", finalDefectsImg);
	//QuadCoord Q1;
	//QuadCoord Q2;
	//Q1.x1 = 50;
	//Q1.y1 = 50;
	//Q1.x2 = 200;
	//Q1.y2 = 50;
	//Q1.x3 = 200;
	//Q1.y3 = 200;
	//Q1.x4 = 50;
	//Q1.y4 = 200;

	//Q2.x1 = 100;
	//Q2.y1 = 100;
	//Q2.x2 = 300;
	//Q2.y2 = 100;
	//Q2.x3 = 300;
	//Q2.y3 = 300;
	//Q2.x4 = 100;
	//Q2.y4 = 300;
	////Q2 = Q1;

	//return CalInterOverUnion(Q1, Q2);
	return 0;
}

