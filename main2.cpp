#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <ctime>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <Eigen/Dense>
#include <opencv2/core/eigen.hpp>
using namespace std;
using namespace cv;
using namespace Eigen;
int main()
{
    std::freopen("../hw3_t2/dollar.txt","r",stdin);

    double data;
    std::vector<double> data_v;
    while(cin >> data){
        data_v.push_back(data);
    }
    // calculate speed
    const int Z_N = 1, X_N = 2;
    Matrix<double, X_N, 1> X;
    Matrix<double, X_N, X_N> A;
    Matrix<double, X_N, X_N> P;
    Matrix<double, X_N, X_N> R;
    Matrix<double, X_N, Z_N> K;
    Matrix<double, Z_N, X_N> C;
    Matrix<double, Z_N, Z_N> Q;
    X << data_v[0], 0;
    A << 1, 1, 0, 1;
    C << 1, 0;
    R << 2, 0, 0, 2;
    Q << 10;
    for (int i = 1; i < data_v.size(); i++)
    {
        // 更新预测
        Matrix<double, X_N, 1> X_k = A * X;
        P = A * P * A.transpose() + R;
        // 更新观测
        K = P * C.transpose() * (C * P * C.transpose() + Q).inverse();
        Matrix<double, Z_N, 1> Z{data_v[i]};
        X = X_k + K * (Z - C * X_k);
        P = (Matrix<double, X_N, X_N>::Identity() - K * C) * P;
        std::cout << "step " << i << ": " << X[1] << std::endl;
    }
    std::cout << "final speed: " << X[1] << std::endl;
    Matrix<double, X_N, 1> X_k = A * X;
    std::cout << "predict: " << X_k[0] << std::endl;
    std::fclose(stdin);
    return 0;
}