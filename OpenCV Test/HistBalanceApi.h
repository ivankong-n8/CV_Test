#include "basic.h"

int ImgAutoAdjust(string OrigImgPath, string outputImgPath);
Mat  automatic_brightness_and_contrast(Mat image, double& alpha, double& beta, int clip_hist_percent = 3);
