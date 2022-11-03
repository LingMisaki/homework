#include <opencv2/opencv.hpp>
#include <opencv2/opencv.hpp>
#include<iostream>
#include<eigen3/Eigen/Core>
#include<eigen3/Eigen/Geometry>
#include "opencv2/core/eigen.hpp"
const std::vector<cv::Point3d> PW_BIG{// 灯条坐标，单位：m
{-0.115, 0.0265, 0.},
{-0.115, -0.0265, 0.},
{0.115, -0.0265, 0.},
{0.115, 0.0265, 0.}
};
const std::vector<cv::Point2d>Image_Points{{575.508, 282.175},
{573.93, 331.819},
{764.518, 337.652},
{765.729, 286.741},
};                                                                                
int main(){
    cv::Mat src = cv::imread("../hw3_t1/hero.jpg");
    cv::Mat camera_matrix;
    cv::Mat distort_matrix;
    cv::FileStorage reader("../hw3_t1/f_mat_and_c_mat.yml", cv::FileStorage::READ);
    reader["F"] >> camera_matrix;
    reader["C"] >> distort_matrix;
    cv::Mat rvec, tvec;
    cv::solvePnP(PW_BIG, Image_Points, camera_matrix, distort_matrix, rvec, tvec);
    /*
    solvePnP求解的r和t是将世界坐标系下的点变换到相机坐标系所需要的旋转和平移，实际上也是相机在世界坐标系下的位姿，即R*Pw + T = Pc。
    r和t不是图像2D坐标和物体3D坐标之间的一个关系，而是相机坐标系（3D）和世界坐标系（3D）之间的关系。
    */
    //0.994363i + -0.0676645j + -0.00122528k + -0.0816168
    Eigen::Quaterniond q(-0.0816168, 0.994363, -0.0676645, -0.00122528);
    Eigen::Matrix3d rot_c_to_w = q.matrix();
    Eigen::Vector3d tvec_(tvec.at<double>(0,0),tvec.at<double>(1,0),tvec.at<double>(2,0));
    auto result = rot_c_to_w*tvec_;
    std::cout<<result<<std::endl;
    cv::waitKey(0);
    return 0;
}