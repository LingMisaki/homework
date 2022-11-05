#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

int main()
{
    int board_width = 11, board_height = 8;
    int board_N = board_width * board_height;
    Size board_size(board_width, board_height);
    vector<Point2f> points;
    vector<vector<Point2f>> points_useful;
    Mat gray_img;
    bool found = false;
    Size img_size;
    for (int i = 0; i <= 19; i++)
    {
        String calib1src = "../datapack/calib1/";
        Mat src = imread(calib1src.append(to_string(i)).append(".jpg"));
        if (i == 0)
        {
            img_size.width = src.cols;
            img_size.height = src.rows;
        }
        found = findChessboardCorners(src, board_size, points);
        if (found && points.size() == board_N)
        {
            cvtColor(src, gray_img, COLOR_BGR2GRAY);
            find4QuadCornerSubpix(gray_img, points, Size(5, 5));
            points_useful.push_back(points);
            Mat drawn_img = src.clone();
            drawChessboardCorners(drawn_img, board_size, points, found);
            imshow("Corners", drawn_img);
            waitKey(50);
        }
        else
            cout << "Not All Corners Are Found In Image " << i << endl;
        points.clear();
    }
    cout << points_useful.size() << " useful chess boards" << endl;

    Size square_size(10, 10);
    std::vector<std::vector<Point3f>> point_grid_pos;
    std::vector<Point3f> point_grid_pos_buf;
    std::vector<int> point_count;
    Mat camera_matrix(3, 3, CV_32FC1, Scalar::all(0));
    Mat dist_coeffs(1, 5, CV_32FC1, Scalar::all(0));
    std::vector<Mat> rvecs;
    std::vector<Mat> tvecs;
    for (int i = 0; i < points_useful.size(); i++)
    {
        for (int j = 0; j < board_height; j++)
        {
            for (int k = 0; k < board_width; k++)
            {
                Point3f pt;
                pt.x = k * square_size.width;
                pt.y = j * square_size.height;
                pt.z = 0;
                point_grid_pos_buf.push_back(pt);
            }
        }
        point_grid_pos.push_back(point_grid_pos_buf);
        point_grid_pos_buf.clear();
        point_count.push_back(board_height * board_width);
    }
    std::cout << calibrateCamera(point_grid_pos, points_useful, img_size, camera_matrix, dist_coeffs, rvecs, tvecs) << std::endl;
    std::cout << camera_matrix << std::endl
              << dist_coeffs << std::endl;
    

    board_width = 9, board_height = 6;
    board_N = board_width * board_height;
    board_size.width=board_width;
    board_size.height=board_height;
    points.clear();
    points_useful.clear();
    found = false;
    for (int i = 0; i <= 23; i++)
    {
        String calib1src = "../datapack/calib2/";
        Mat src = imread(calib1src.append(to_string(i)).append("_orig.jpg"));
        if (i == 0)
        {
            img_size.width = src.cols;
            img_size.height = src.rows;
        }
        found = findChessboardCorners(src, board_size, points);
        if (found && points.size() == board_N)
        {
            cvtColor(src, gray_img, COLOR_BGR2GRAY);
            find4QuadCornerSubpix(gray_img, points, Size(5, 5));
            points_useful.push_back(points);
            Mat drawn_img = src.clone();
            drawChessboardCorners(drawn_img, board_size, points, found);
            imshow("Corners", drawn_img);
            waitKey(50);
        }
        else
            cout << "Not All Corners Are Found In Image " << i << endl;
        points.clear();
    }
    cout << points_useful.size() << " useful chess boards" << endl;

    point_grid_pos.clear();
    point_grid_pos_buf.clear();
    point_count.clear();
    rvecs.clear();
    tvecs.clear();
    for (int i = 0; i < points_useful.size(); i++)
    {
        for (int j = 0; j < board_height; j++)
        {
            for (int k = 0; k < board_width; k++)
            {
                Point3f pt;
                pt.x = k * square_size.width;
                pt.y = j * square_size.height;
                pt.z = 0;
                point_grid_pos_buf.push_back(pt);
            }
        }
        point_grid_pos.push_back(point_grid_pos_buf);
        point_grid_pos_buf.clear();
        point_count.push_back(board_height * board_width);
    }
    std::cout << calibrateCamera(point_grid_pos, points_useful, img_size, camera_matrix, dist_coeffs, rvecs, tvecs) << std::endl;
    std::cout << camera_matrix << std::endl
              << dist_coeffs << std::endl;
    return 0;
}