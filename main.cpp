#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;
//int main() {
//    Mat myMat = imread("../infantry.jpg");
//    Mat imageROI;
//    vector<Mat> channels;
////    imageROI = myMat(Rect(myMat.cols/4,0,myMat.cols/2,myMat.rows/7*2));
////    imshow("1",imageROI);
//    waitKey(0);
///**把一个3通道图像转换成3个单通道图像*/
//    split(myMat,channels);
//    imageROI=channels.at(0);
//
//    for (Mat k : channels) {
//        imshow("",k);
//        waitKey(0);
//    }
////    channels.push_back(channels.at(2));
//    merge(channels,imageROI);
//    imshow("",imageROI);
////    addWeighted(imageROI(Rect(385,250,myMat.cols,myMat.rows)),1.0,myMat,0.5,0.,imageROI(Rect(385,250,myMat.cols,myMat.rows)));
////
////    merge(channels,myMat);
////
////    namedWindow("sample");
////    imshow("sample",myMat);
//    waitKey(0);
//
//
//    return 0;
//}

int main(int argc, char** atgv){
    namedWindow("Control", CV_WINDOW_AUTOSIZE);

    int iLowH = 0;
    int iHighH = 57;

    int iLowS = 28;
    int iHighS = 104;

    int iLowV = 250;
    int iHighV = 255;

    int talpha = 0;
    double alpha = (talpha + 10)/10; //控制对比度
    int beta = 0; //控制亮度

    //Create trackbars in "Control" window
    cvCreateTrackbar("alpha", "Control", &talpha, 20); //alpha (10 - 30)
    cvCreateTrackbar("beta", "Control", &beta, 100); //beta (0 - 100)


    cvCreateTrackbar("LowH", "Control", &iLowH, 179); //Hue (0 - 179)
    cvCreateTrackbar("HighH", "Control", &iHighH, 179);

    cvCreateTrackbar("LowS", "Control", &iLowS, 255); //Saturation (0 - 255)
    cvCreateTrackbar("HighS", "Control", &iHighS, 255);

    cvCreateTrackbar("LowV", "Control", &iLowV, 255); //Value (0 - 255)
    cvCreateTrackbar("HighV", "Control", &iHighV, 255);

    while (true){

        Mat imgOriginal;
        imgOriginal = imread("../infantry.jpg");

        Mat new_image = imgOriginal;
       // new_image(i,j) = alpha*image(i,j) + beta
        for( int y = 0; y < imgOriginal.rows; y++ )    {
            for( int x = 0; x < imgOriginal.cols; x++ )        {
                for( int c = 0; c < 3; c++ )            {
                    new_image.at<Vec3b>(y,x)[c] = saturate_cast<uchar>( alpha*( imgOriginal.at<Vec3b>(y,x)[c] ) - beta );
                }
            }
        }

//        imshow("Control",imgOriginal); //在control窗口显示imgOriginal图片

        Mat imgHSV;
        vector<Mat> hsvSplit;
        cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV);//将图片转化到HSV空间

        split(imgHSV, hsvSplit);
        equalizeHist(hsvSplit[2],hsvSplit[2]);
        merge(hsvSplit, imgHSV);
        Mat imgThresholded;
        inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded); //Threshold the image

        //开操作 (去除一些噪点)
        Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));
//        morphologyEx(imgThresholded, imgThresholded, MORPH_OPEN, element);

        //闭操作 (连接一些连通域)
        morphologyEx(imgThresholded, imgThresholded, MORPH_CLOSE, element);

        imshow("Thresholded Image", imgThresholded); //show the thresholded image
        imshow("Control", imgOriginal); //show the original image

        char key = (char) waitKey(300);
        if(key == 27)
            break;
    }
    return 0;

}
