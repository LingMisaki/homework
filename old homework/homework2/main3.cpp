#include<eigen3/Eigen/Core>
#include<eigen3/Eigen/Geometry>
#include<iostream>
#include<opencv2/opencv.hpp>
#include<cstdlib>
#include<cmath>
cv::Point2d camera(Eigen::Vector4d world,Eigen::Matrix3d rota,double x_cam_w = 1000, double y_cam_w = 0, double z_cam_w = 500.){
    Eigen::Matrix4d converter = [&x_cam_w, &y_cam_w, &z_cam_w,&rota]() {
        Eigen::Vector3d cam_w = {x_cam_w, y_cam_w, z_cam_w};        
        Eigen::Matrix4d converter = Eigen::Matrix4d::Zero();
        Eigen::Matrix3d rot_c_to_w = rota;
       
        converter.block(0, 0, 3, 3) = rot_c_to_w.transpose().cast<double>();
        converter.block(0, 3, 3, 1) =-rot_c_to_w.transpose().cast<double>() * cam_w;
        converter(3, 3) = 1.;
        return converter;
    }();
    Eigen::Matrix<double, 3, 4> cam_f;
    cam_f << 400., 0., 190., 0.,
             0., 400., 160., 0.,
             0., 0., 1., 0.;

    Eigen::Vector3d ans=cam_f*converter*world;
    ans /= ans(2, 0);
    cv::Point2d centre(ans(0,0),ans(1,0));
    return centre;
}
Eigen::Matrix3d eulerAnglesToRotationMatrix(Eigen::Vector3d &theta)
{
    Eigen::Matrix3d R_x;    // 计算旋转矩阵的X分量
    R_x <<  1,              0,               0,
            0,  cos(theta[0]),  -sin(theta[0]),
            0,  sin(theta[0]),   cos(theta[0]);

    Eigen::Matrix3d R_y;    // 计算旋转矩阵的Y分量
    R_y <<  cos(theta[1]),   0, sin(theta[1]),
            0,   1,             0,
            -sin(theta[1]),  0, cos(theta[1]);

    Eigen::Matrix3d R_z;    // 计算旋转矩阵的Z分量
    R_z <<  cos(theta[2]), -sin(theta[2]), 0,
            sin(theta[2]),  cos(theta[2]), 0,
            0,              0,             1;
    Eigen::Matrix3d R = R_z * R_y * R_x;
    return R;
}
int main(){
    srand((unsigned)time(NULL));
    std::vector<Eigen::Vector4d> points;
    cv::Mat src=cv::imread("../4001666005799_.pic.png");
    cv::Mat gray;
    cv::cvtColor(src,gray,cv::COLOR_BGR2GRAY);
    cv::Mat thres_result;
    cv::threshold(gray,thres_result,200,255,cv::THRESH_BINARY);
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierachy;
    cv::findContours(thres_result,contours,hierachy,cv::RETR_TREE,cv::CHAIN_APPROX_NONE);
    const int ma=50;
    const int mi=0;//z坐标的随机范围
    for(int i=0;i<contours.size();i++){
        for(int j=0;j<contours[i].size();j++){
            
            Eigen::Vector4d world;
            world<<contours[i][j].x,contours[i][j].y,std::rand()%(ma-mi+1)+mi,1;
            points.push_back(world);
        }      
    }
    //以上都在轮廓提取，然后把点都变成Vector4d之后push到points数组里面
    std::vector<double> dot_size;
    const int dotma=20;
    const int dotmi=1;//点的大小的随机范围(*10)
    for(int j=0;j<points.size();j++){
        dot_size.push_back((double)(std::rand()%(dotma-dotmi+1)+dotmi)/10);
    }
    //对点的大小进行随机处理
    cv::Size2d siz(1280,720);
    cv::VideoWriter writer("../dragon.mp4",cv::VideoWriter::fourcc('M','P','4','V'),30,siz);
    //以下为控制相机运动
    const double camxst=200,camyst=200,camzst=-100;
    const double camxed=0,camyed=50,camzed=500;
    double camx_,camy_,camz_;
    const double angxst=0,angyst=M_PI/2,angzst=M_PI;
    const double angxed=0,angyed=0,angzed=M_PI;
    double angx_,angy_,angz_;
    cv::Mat fraps=cv::Mat::zeros(720,1280,CV_8UC3);
    int frp_cnt=100;
    for(int i=0;i<=frp_cnt;i++){
        fraps=cv::Mat::zeros(720,1280,CV_8UC3);
        camx_=(camxed-camxst)/frp_cnt*i+camxst;
        camy_=(camyed-camyst)/frp_cnt*i+camyst;
        camz_=(camzed-camzst)/frp_cnt*i+camzst;
        angx_=(angxed-angxst)/frp_cnt*i+angxst;
        angy_=(angyed-angyst)/frp_cnt*i+angyst;
        angz_=(angzed-angzst)/frp_cnt*i+angzst;
        Eigen::Vector3d theta;
        theta<<angx_,angy_,angz_;
        Eigen::Matrix3d rota=eulerAnglesToRotationMatrix(theta);
        for(int j=0;j<points.size();j++){
            cv::circle(fraps,camera(points[j],rota,camx_,camy_,camz_),dot_size[j],cv::Scalar(255,255,255),-1);
        }
        cv::imshow("Dragon",fraps);
        cv::waitKey(50); 
        writer.write(fraps);
    }
    cv::imshow("Dragon",fraps);
    cv::waitKey(0); 
    return 0;
}