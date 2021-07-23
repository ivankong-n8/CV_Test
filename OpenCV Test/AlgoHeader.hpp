#pragma once
#include "basic.h"
#include <iostream>
#include <string>
#include <list>


#ifdef ALGO_DLL_EXPORTS
#define ALGO_DLL_API extern "C" __declspec(dllexport)
#else
#define ALGO_DLL_API extern "C" __declspec(dllimport)
#endif

#ifndef AlgoHeader_hpp
#define AlgoHeader_hpp

#pragma warning( disable : 4996 )

//算法返回结果
#define ALL_OK 0
#define ALGO_ERROR 1
#define ROI_ERROR 2

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

int FindMinRange(QuadCoord& Q1, QuadCoord& Q2, int& ImgWitdh, int& ImgHeight);
void DrawPolygon(Mat inputImage, vector<Point> polygonPoint, bool bIsFill, bool bIsClosed = true);
vector<Point> getPoints(QuadCoord Q1);
//算法执行函数,传入参数分别为算法参数和算法类型
//ALGO_DLL_API int run(void* str, void* ptr);
//ALGO_DLL_API int TestFun(int a, int b);
//ALGO_DLL_API void DefectDetails();

ALGO_DLL_API double CalInterOverUnion(QuadCoord Q1, QuadCoord Q2); //有修改
#endif