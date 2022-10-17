#include <opencv2/opencv.hpp>
int main(){
    cv::Mat src = cv::imread("../apple.png");
    assert(src.channels()==3);

    cv::Mat hsv;
    cv::cvtColor(src,hsv,cv::COLOR_BGR2HSV);
    //BGR->HSV

    cv::Mat hsv_part1, hsv_part2;
    cv::inRange(hsv, cv::Scalar(0, 43, 46), cv::Scalar(22, 255, 255), hsv_part1);
    cv::inRange(hsv, cv:: Scalar(161, 43, 46), cv::Scalar(180, 255, 255), hsv_part2);
    // 提取红⾊和橙⾊

    cv::Mat ones_mat = cv::Mat::ones(cv::Size(src.cols, src.rows), CV_8UC1);
    cv::Mat hsv_result = 255 * (ones_mat - (ones_mat - hsv_part1 /255).mul(ones_mat - hsv_part2 / 255));
    // 对hsv_part1的结果和hsv_part2的结果取并集

    cv::Mat blur_result;
    cv::medianBlur(hsv_result, blur_result, 9);
    //中值滤波

    cv::Mat morph_result;
    cv::Mat element=getStructuringElement(cv::MORPH_RECT,cv::Size(35,35));
    cv::morphologyEx(blur_result,morph_result,cv::MORPH_OPEN,element);
    //开运算

    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierachy;
    cv::findContours(morph_result,contours,hierachy,cv::RETR_TREE,cv::CHAIN_APPROX_NONE);
    //轮廓提取

    std::vector<cv::Rect> rec(contours.size());
    for(int i=0;i<contours.size();i++){
        rec[i]=cv::boundingRect(contours[i]);
        //cv::drawContours(src,contours,i,cv::Scalar(255,0,0));
        rec[i].tl().x;
        cv::rectangle(src,rec[i].tl(),rec[i].br(),cv::Scalar(0,255,0));
    }
    //寻找外接矩形

    cv::imshow("result", src);
    cv::waitKey(0);
    
    return 0;
}