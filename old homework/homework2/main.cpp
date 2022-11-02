#include <opencv2/opencv.hpp>
const int width =440;
const int height =140;//车牌大小440*140（百度得）
int main(){
    cv::Mat src = cv::imread("../1634287874477.png");
    std::vector<cv::Point2f> Point_Src,Point_Dst;
    cv::Point2f point1(742,413),point2(747,488),point3(953,413),point4(966,488),point5(0,0),point6(0,height),point7(width,0),point8(width,height);
    Point_Src.push_back(point1);
    Point_Src.push_back(point2);
    Point_Src.push_back(point3);
    Point_Src.push_back(point4);
    Point_Dst.push_back(point5);
    Point_Dst.push_back(point6);
    Point_Dst.push_back(point7);
    Point_Dst.push_back(point8);
    cv::Mat result; 
    cv::Mat Mat_Trans=cv::getPerspectiveTransform(Point_Src,Point_Dst);
    cv::Size siz(width,height);
    cv::warpPerspective(src,result,Mat_Trans,siz);
    cv::imshow("result", result);
    cv::imwrite("../car_tag.jpg",result);
    cv::waitKey(0);
    
    return 0;
}