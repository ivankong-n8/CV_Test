// OpenCV Test.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <string>

using namespace cv;
using namespace std;

struct QuadCoord {
	int x1;
	int y1;//左上
	int x2;
	int y2;//右上
	int x3;
	int y3;//右下
	int x4;
	int y4;//左下
};


vector<Point> getPoints(QuadCoord Q1) {
	vector<Point> Q1PolygonPoint;
	Q1PolygonPoint.push_back(Point(Q1.x1, Q1.y1));
	Q1PolygonPoint.push_back(Point(Q1.x2, Q1.y2));
	Q1PolygonPoint.push_back(Point(Q1.x3, Q1.y3));
	Q1PolygonPoint.push_back(Point(Q1.x4, Q1.y4));
	return Q1PolygonPoint;
}

void DrawPolygon(Mat inputImage, vector<Point> polygonPoint, bool bIsFill, bool bIsClosed = true)
{
	vector<vector<Point>> contours;
	contours.push_back(polygonPoint);

	if (bIsFill)
		fillPoly(inputImage, contours, Scalar(255, 255, 255), 8);
	else
		polylines(inputImage, polygonPoint, bIsClosed, Scalar(255, 255, 255), 2, 8);
}


double CalInterOverUnion(int ImgHeight, int ImgWitdh, QuadCoord Q1, QuadCoord Q2) {
	
	Mat Q1Img = Mat::zeros(ImgHeight, ImgWitdh, CV_8UC1);
	Mat Q2Img = Mat::zeros(ImgHeight, ImgWitdh, CV_8UC1);
	
	vector<Point> Q1PolygonPoint = getPoints(Q1);
	vector<Point> Q2PolygonPoint = getPoints(Q2);



	//绘制四边形
	DrawPolygon(Q1Img, Q1PolygonPoint, true);
	DrawPolygon(Q2Img, Q2PolygonPoint, true);

	namedWindow("Q1");
	imshow("Q1", Q1Img);
	waitKey();

	namedWindow("Q2");
	imshow("Q2", Q2Img);
	waitKey();


	//计算 交集 并集
	Mat interImg, unionImg;
	bitwise_and(Q1Img, Q2Img, interImg);
	bitwise_or(Q1Img, Q2Img, unionImg);

	namedWindow("interImg");
	imshow("interImg", interImg);
	waitKey();

	namedWindow("unionImg");
	imshow("unionImg", unionImg);
	waitKey();

	double areaInter = countNonZero(interImg);
	double areaUnion = countNonZero(unionImg);

	destroyAllWindows();
	double ratio = areaInter / areaUnion;
	cout << ratio << endl;
	return ratio;
}




//int main()
//{
//    std::cout << "Hello World!\n";
//
//	//std::string str0 = "./20210608 - LALS and HALS/8-back-LALS.png";
//	//std::string str1 = "./20210608 - LALS and HALS/8-back-HALS.png";
//	//Mat RstImgHALS = imread(str1, IMREAD_GRAYSCALE);
//	//Mat RstImgLALS = imread(str0, IMREAD_GRAYSCALE);
//	//
//	////Mat finaLabels, finaStatus, finaCenter;
//	////int totalNumHLAS = connectedComponentsWithStats(RstImgHALS, finaLabels, finaStatus, finaCenter);
//
//
//	//Mat finalDefectsImg, dustImg;
//	//ExtractDustImg(RstImgHALS, RstImgLALS, finalDefectsImg, dustImg);
//
//	//imwrite("DustImg.png", dustImg);
//	//imwrite("finalDefectsImg.png", finalDefectsImg);
//	QuadCoord Q1;
//	QuadCoord Q2;
//	Q1.x1 = 50;
//	Q1.y1 = 50;
//	Q1.x2 = 200;
//	Q1.y2 = 50;
//	Q1.x3 = 200;
//	Q1.y3 = 200;
//	Q1.x4 = 50;
//	Q1.y4 = 200;
//
//	//Q2.x1 = 100;
//	//Q2.y1 = 100;
//	//Q2.x2 = 300;
//	//Q2.y2 = 100;
//	//Q2.x3 = 300;
//	//Q2.y3 = 300;
//	//Q2.x4 = 100;
//	//Q2.y4 = 300;
//	Q2 = Q1;
//
//	return CalInterOverUnion(500, 500, Q1, Q2);
//
//}
