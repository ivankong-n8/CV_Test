
#include "FindContour.h"

//ʹ�ô��Mat����ֵ
int GetMatOTSU(Mat& img)
{
    //�ж�������ǵ�ͨ��ֱ�ӷ���128
    if (img.channels() > 1) return 128;
    int rows = img.rows;
    int cols = img.cols;
    //��������
    float mathists[256] = { 0 };
    //��������0-255�ĸ���
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            int val = img.at<uchar>(row, col);
            mathists[val]++;
        }
    }

    //����Ҷȼ�����������ͼ���еı���
    float grayPro[256] = { 0 };
    int matSize = rows * cols;
    for (int i = 0; i < 256; ++i) {
        grayPro[i] = (float)mathists[i] / (float)matSize;
    }

    //���OTSU��ǰ���뱳���ָ������������ĻҶ�ֵ
    int calcval;
    int calcMax = 0;
    for (int i = 0; i < 256; ++i) {
        float w0 = 0, w1 = 0, u0tmp = 0, u1tmp = 0, u0 = 0, u1 = 0, u = 0, calctmp = 0;

        for (int k = 0; k < 256; ++k) {
            float curGray = grayPro[k];
            //���㱳������
            if (k <= i) {
                //��iΪ��ֵ���࣬��һ���ܵĸ���
                w0 += curGray;
                u0tmp += curGray * k;
            }
            //����ǰ������
            else {
                //��iΪ��ֵ���࣬��һ���ܵĸ���
                w1 += curGray;
                u1tmp += curGray * k;
            }
        }

        //�����һ��͵ڶ����ƽ���Ҷ�
        u0 = u0tmp / w0;
        u1 = u1tmp / w1;
        //�������ͼ���ƽ���Ҷ�
        u = u0tmp + u1tmp;

        //������䷽��
        calctmp = w0 * pow((u0 - u), 2) + w1 * pow((u1 - u), 2);

        //���������䷽���������ֵ
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
    // �������ֵ
    minval = saturate_cast<uchar>((1.0 - sigma) * midval);
    //�������ֵ
    maxval = saturate_cast<uchar>((1.0 + sigma) * midval);
}