
#include "FindContour.h"

//使用大津法Mat的阈值
int GetMatOTSU(Mat& img)
{
    //判断如果不是单通道直接返回128
    if (img.channels() > 1) return 128;
    int rows = img.rows;
    int cols = img.cols;
    //定义数组
    float mathists[256] = { 0 };
    //遍历计算0-255的个数
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            int val = img.at<uchar>(row, col);
            mathists[val]++;
        }
    }

    //定义灰度级像素在整个图像中的比例
    float grayPro[256] = { 0 };
    int matSize = rows * cols;
    for (int i = 0; i < 256; ++i) {
        grayPro[i] = (float)mathists[i] / (float)matSize;
    }

    //大津法OTSU，前景与背景分割，计算出方差最大的灰度值
    int calcval;
    int calcMax = 0;
    for (int i = 0; i < 256; ++i) {
        float w0 = 0, w1 = 0, u0tmp = 0, u1tmp = 0, u0 = 0, u1 = 0, u = 0, calctmp = 0;

        for (int k = 0; k < 256; ++k) {
            float curGray = grayPro[k];
            //计算背景部分
            if (k <= i) {
                //以i为阈值分类，第一类总的概率
                w0 += curGray;
                u0tmp += curGray * k;
            }
            //计算前景部分
            else {
                //以i为阈值分类，第一类总的概率
                w1 += curGray;
                u1tmp += curGray * k;
            }
        }

        //求出第一类和第二类的平均灰度
        u0 = u0tmp / w0;
        u1 = u1tmp / w1;
        //求出整幅图像的平均灰度
        u = u0tmp + u1tmp;

        //计算类间方差
        calctmp = w0 * pow((u0 - u), 2) + w1 * pow((u1 - u), 2);

        //更新最大类间方差，并设置阈值
        if (calctmp > calcMax) {
            calcMax = calctmp;
            calcval = i;
        }
    }

    return calcval;
}

void GetMatMinMaxThreshold(Mat& img, int& minval, int& maxval, int calctype, float sigma)
{
    int midval;
    switch (calctype)
    {
    case 1: {
        midval = GetMatOTSU(img);
        break;
    }
    default:
        // midval = GetMatMidVal(img);
        break;
    }
    cout << "midval:" << midval << endl;
    // 计算低阈值
    minval = saturate_cast<uchar>((1.0 - sigma) * midval);
    //计算高阈值
    maxval = saturate_cast<uchar>((1.0 + sigma) * midval);
}