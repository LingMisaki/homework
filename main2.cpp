#include "hw4_t2/VO.h"

int main(){

    FileStorage params("../hw4_t2/camera.yaml", FileStorage::READ);
    Mat camera_matrix;
    params["K"] >> camera_matrix;
    Mat src1 =imread("../hw4_t2/stereo-data/0_orig.jpg");
    Mat src2 =imread("../hw4_t2/stereo-data/1_orig.jpg");
    Mat depth1 =imread("../hw4_t2/stereo-data/0_dpt.tiff",IMREAD_UNCHANGED);
    Mat depth2 =imread("../hw4_t2/stereo-data/1_dpt.tiff",IMREAD_UNCHANGED);
    Mat rvec, tvec;
    find_PnP(src1, depth1, src2, depth2, camera_matrix, rvec, tvec);
    Mat R;
    Rodrigues(rvec, R);
    process_Stitch_project(src1, depth1, src2, depth2, camera_matrix, R, tvec, "result");
    return 0;

}