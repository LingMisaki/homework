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
    //Eigen::Quaterniond in_para_qua(-0.5,0.5,0.5,-0.5);//0.5i + 0.5j + -0.5k + -0.5
    //std::cout<<in_para_qua.matrix();
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
        inputt<<x,y,z,1;
        outputt=in_para*out_para*inputt/z;
        cv::Point2d centre(outputt(1,1),outputt(2,1));
        std::cout<<outputt<<std::endl;
        cv::circle(result,centre,1,cv::Scalar(0,255,0));
    }
    std::fclose(stdin);
    cv::imshow("result",result);
    cv::waitKey(0);
}