#pragma once
#include "basic.h"

int GetMatOTSU(Mat& img);
void GetMatMinMaxThreshold(Mat& img, int& minval, int& maxval, int calctype, float sigma = 0.3);