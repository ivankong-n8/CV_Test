#include "HistBalanceApi.h"
#include "AlgoHeader.hpp"

int test_img_copy() {


	Mat tmpImg = Mat::zeros(Size2i(500, 500), CV_8UC1); 
	RotatedRect roiInputRect = RotatedRect(Point2i(100, 100), Size2i(50, 10), 45);
	rectangle(tmpImg, roiInputRect.boundingRect(), Scalar(255), 10);
	//����������ͼ��

	Mat tmpImg2 = Mat::zeros(Size2i(1000, 1000), CV_8UC1);
	//����Ŀ��ͼ��


	namedWindow("test");
	imshow("test", tmpImg2);
	waitKey(0);

	Mat srcROI(tmpImg2, Rect(Point(0, 0), Size(500, 500))); 
	//��Ŀ��ͼ���У�ָ��Ҫճ����λ��

	tmpImg.copyTo(srcROI);
	//�Ѵ���ͼ�� tmpImg��ճ����tmpImg2��ָ��λ��


	imshow("test", tmpImg2);
	waitKey(0);
	//���Թ۲쵽tmpImg2ԭͼ���б��޸�


	Mat corpedImg = tmpImg2(roiInputRect.boundingRect());
	//��ȡ�ü�ͼƬ

	imshow("test", corpedImg);
	waitKey(0);

	destroyAllWindows();
	return 0;
}

int test_erode_withDirection() {
	string windowName;
	Mat tmpImg = Mat::zeros(Size2i(500, 500), CV_8UC1);
	RotatedRect roiInputRect = RotatedRect(Point2i(100, 100), Size2i(50, 10), 45);
	rectangle(tmpImg, roiInputRect.boundingRect(), Scalar(255), 10);
	//����������ͼ��

	windowName = "��ʴǰ";
	cv::namedWindow(windowName);
	cv::imshow(windowName, tmpImg);
	cv::waitKey();
	//cv::destroyWindow(windowName);

	cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(1, 30));
	cv::erode(tmpImg, tmpImg, element);

	windowName = "��ʴ��";
	cv::namedWindow(windowName);
	cv::imshow(windowName, tmpImg);
	cv::waitKey();
	cv::destroyWindow(windowName);
	

	return 0;
}

void main() {
	//test_img_copy();
	test_erode_withDirection();

}

