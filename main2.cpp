#include<eigen3/Eigen/Core>
#include<eigen3/Eigen/Geometry>
#include<iostream>
#include<opencv2/opencv.hpp>
#include<cstdio>
int cnt;
double x,y,z;
cv::Point2d camera(Eigen::Vector4d world){
    double x_cam_w = 2., y_cam_w = 2., z_cam_w = 2.;
    Eigen::Quaterniond q={-0.5,0.5,0.5,-0.5}; //0.5i + 0.5j + -0.5k + -0.5
    Eigen::Matrix4d converter = [&q, &x_cam_w, &y_cam_w, &z_cam_w]() {
        Eigen::Vector3d cam_w = {x_cam_w, y_cam_w, z_cam_w};        
        Eigen::Matrix4d converter = Eigen::Matrix4d::Zero();
        Eigen::Matrix3d rot_c_to_w = q.matrix();
       
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
int main(){
    std::freopen("../points.txt","r",stdin);
    std::cin>>cnt;
    Eigen::Vector4d inputt;
    cv::Mat result(720,1280,CV_8UC3);
    for(int i=1;i<=cnt;i++){
        std::cin>>x>>y>>z;
        inputt<<x,y,z,1.;
        cv::circle(result,camera(inputt),0.5,cv::Scalar(255,255,255));
    }
    std::fclose(stdin);
    cv::imshow("result",result);
    cv::waitKey(0);
}