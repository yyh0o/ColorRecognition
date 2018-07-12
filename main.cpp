#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;
int main() {
    Mat myMat = imread("../lena.jpg");
    Mat imageROI;
    imageROI = myMat(Rect(0,0,myMat.cols,myMat.rows/2));


    return 0;
}