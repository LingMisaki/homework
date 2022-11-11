#include <opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;                                                                             
int main(){
    Mat src1 = imread("../hw4_t1/9407.png");
    Mat src2 = imread("../hw4_t1/9408.png");   
    Mat gray1, gray2;
    cvtColor(src1, gray1,COLOR_BGR2GRAY);
    cvtColor(src2, gray2,COLOR_BGR2GRAY);
    Ptr<ORB> orb = ORB::create();
    vector<KeyPoint> feature_points1, feature_points2;
    orb->detect(gray1,feature_points1);
    orb->detect(gray2,feature_points2);
    Mat descriptor1,descriptor2;
    orb->compute(gray1,feature_points1,descriptor1);
    orb->compute(gray2,feature_points2,descriptor2);
    BFMatcher matcher(NORM_HAMMING);
    vector<DMatch> pairs;
    matcher.match(descriptor1,descriptor2,pairs);
    vector<DMatch> good;
    double min_dist = 10000000;
    for(const auto i:pairs){
        if(i.distance < min_dist)
            min_dist = i.distance;
    }
    for(const auto i:pairs){
        if(i.distance < max(min_dist, 30.))
            good.push_back(i);
    }
    Mat canvas;
    drawMatches(src1, feature_points1, src2, feature_points2, good, canvas);
    imwrite("../t1_ans.jpg", canvas);
    namedWindow("result", WINDOW_NORMAL);
    resizeWindow("result", 800, 600);
    imshow("result", canvas);
    waitKey(0);

    return 0; 
}