#include<eigen3/Eigen/Core>
#include<eigen3/Eigen/Geometry>
#include<iostream>
#include<opencv2/opencv.hpp>
#include<cstdio>
int cnt;
double x,y,z;
int main(){
    std::freopen("../points.txt","r",stdin);
    Eigen::Matrix4d out_para;
    Eigen::Matrix<double,3,4> in_para;
    in_para<<400., 0., 190., 0.,    
             0., 400., 160.,  0., 
             0., 0.,   1.,   0.;
    out_para<<0.,  0., -1., 2.,
              1.,  0.,  0., 2.,
              0., -1.,  0., 2.,
              0., 0.,   0., 1.; 
    std::cin>>cnt;
    Eigen::Vector4d inputt;
    Eigen::Vector3d outputt;
    cv::Mat result(320,380,CV_8UC3);
    for(int i=1;i<=cnt;i++){
        std::cin>>x>>y>>z;
        inputt<<x,y,z,1.;
        Eigen::Vector4d Zc_tmp=out_para*inputt;
        double Zc=Zc_tmp(2,0);
        outputt=in_para*out_para*inputt/Zc;
        std::cout<<outputt(0,0)<<" "<<outputt(1,0)<<std::endl;
        cv::Point2d centre(outputt(0,0),outputt(1,0));
        cv::circle(result,centre,0.5,cv::Scalar(0,255,0));
    }
    std::fclose(stdin);
    cv::imshow("result",result);
    cv::waitKey(0);
}