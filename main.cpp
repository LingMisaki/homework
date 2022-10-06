#include <opencv2/opencv.hpp>

int main(){
    cv::Mat img = cv::imread("../apple.png");
    cv::imshow("test", img);
    cv::waitKey(0);
    
    return 0;
}