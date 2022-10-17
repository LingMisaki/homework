#include <opencv2/opencv.hpp>
int main(){
    cv::VideoCapture capture("../IMG_8511.mp4");
    cv::Mat src;
    int cnt=0;
    bool flag=false;//标识前一帧有无刚射出的子弹
    while(capture.read(src)){
        
        cv::Mat hsv;
        cv::cvtColor(src, hsv, cv::COLOR_BGR2HSV);
        cv::Mat hsv_;
        cv::inRange(hsv, cv::Scalar(70, 0, 0), cv::Scalar(90, 255, 255),hsv_);
        cv::Mat blur_result;
        cv::medianBlur(hsv_, blur_result, 3);
        

        cv::Mat morph_result;
        cv::Mat element=getStructuringElement(cv::MORPH_RECT,cv::Size(5,5));
        cv::morphologyEx(blur_result,morph_result,cv::MORPH_CLOSE,element);
   
        std::vector<std::vector<cv::Point>> contours;
        std::vector<cv::Vec4i> hierachy;
        cv::findContours(morph_result,contours,hierachy,cv::RETR_TREE,cv::CHAIN_APPROX_NONE);

        bool isempty=true;//标记当前帧是否有刚射出的子弹
        int fontFace = cv::FONT_HERSHEY_SCRIPT_SIMPLEX;
        cv::Point2f dot(80,80);
        for(int i=0;i<contours.size();i++){
            cv::putText(src,std::to_string(cnt),dot,fontFace,2,cv::Scalar(255,255,255),3);
            cv::RotatedRect rr =cv::minAreaRect(contours[i]);
            //if(cv::contourArea(contours[i])<10)
            //    continue;
            if(std::max(rr.size.height,rr.size.width)/std::min(rr.size.height,rr.size.width)<7)
                continue;
            if(rr.angle<-10&&rr.angle>-15&&rr.size.height>100){
                if(flag==false)
                    cnt++;//前一帧没有子弹，此帧有子弹，则计数加一
                isempty=false;
                cv::putText(src,std::to_string(cnt),rr.center,fontFace,2,cv::Scalar(255,255,255),3);
            }                
            cv::Point2f pts[10];
            rr.points(pts);
            cv::line(src,pts[0],pts[1],cv::Scalar(0,0,255),2);
            cv::line(src,pts[1],pts[2],cv::Scalar(0,0,255),2);
            cv::line(src,pts[2],pts[3],cv::Scalar(0,0,255),2);
            cv::line(src,pts[3],pts[0],cv::Scalar(0,0,255),2);
            cv::circle(src,rr.center,8,cv::Scalar(255,255,255),2);
            //cv::putText(src,std::to_string(rr.angle),rr.center,fontFace,1,cv::Scalar(255,255,255));
        }
        if(isempty)
            flag=false;
        cv::imshow("src",src);
        cv::waitKey(50);
    }

    return 0;
}