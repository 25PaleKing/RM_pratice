#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include "my_camera.hpp"

static unsigned int num=0;
static unsigned int sum=0;
void test(cv::Mat &frame,cv::Size& chessboardSize, 
std::vector<std::vector<cv::Point3f>> objectPoints,std::vector<std::vector<cv::Point2f>> imagePoints
,std::vector<cv::Point3f> &obj ){
     std::vector<cv::Point2f> corners;
        bool found = cv::findChessboardCorners(frame, chessboardSize, corners,cv::CALIB_CB_ADAPTIVE_THRESH);
        cv::FileStorage file(PROJECT_DIR "/Configs/test.yaml",cv::FileStorage::WRITE);
        file<<"camera_test"<<"测试";
        if (found) {        
            cv::Mat gray;
            cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
            cv::cornerSubPix(gray, corners, cv::Size(11, 11), cv::Size(-1, -1),
                             cv::TermCriteria(cv::TermCriteria::EPS + cv::TermCriteria::MAX_ITER, 30, 0.1));
            // 显示棋盘格角点
            cv::drawChessboardCorners(frame, chessboardSize, corners, found);

            // 存储角点坐标
            objectPoints.push_back(obj);
            imagePoints.push_back(corners);
            file<<"camera_test1"<<"成功";
            num++;
        }
        // 反馈
        if(num!=0)
        fmt::print("{} test!!!\n",num);
}

int main() {
   // 设置棋盘格尺寸
    cv::Size chessboardSize(7, 9);

    // 准备存储棋盘格角点的容器
    std::vector<std::vector<cv::Point3f>> objectPoints; // 物体三维坐标
    std::vector<std::vector<cv::Point2f>> imagePoints;  // 图像二维坐标

    // 生成物体三维坐标
    std::vector<cv::Point3f> obj;
    for (int j = 0; j < chessboardSize.height; j++) {
        for (int i = 0; i < chessboardSize.width; i++) {
            obj.push_back(cv::Point3f(i, j, 0));
        }
    }

    // 读取标定图像并检测棋盘格角点
    mvsdk_try::My_Camera capture{PROJECT_DIR "/Configs/camera/MV-SUA133GC-T-Manifold.config"}; // 打开默认相机设备
    cv::Mat frame;
    std::vector<cv::Mat> frames;
    capture.open();
    cv::namedWindow("frame",cv::WINDOW_NORMAL);
    while (capture.read(frame)) {
        cv::imshow("frame",frame);
        auto key=cv::waitKey(2);
        if(key==13){
        frames.push_back(frame);
        fmt::print("{} \n",++sum);
        }
        if (key==27||frames.size()>100)
        break;
        
    } 
    cv::destroyAllWindows();

    for(int i=0;i<frames.size();i++)
    test(frame,chessboardSize,objectPoints,imagePoints,obj);

    for(int i=0;i<objectPoints.size();i++)
        std::cout<<objectPoints[i]<<std::endl;
    


    // 相机内部参数的输出变量
    // cv::Mat cameraMatrix = cv::Mat::eye(3, 3, CV_64F);
    // cv::Mat distCoeffs = cv::Mat::zeros(5, 1, CV_64F);

    // // 进行相机标定
    // std::vector<cv::Mat> rvecs, tvecs;
    // cv::calibrateCamera(objectPoints, imagePoints, 
    // frame.size(), cameraMatrix,
    //  distCoeffs, rvecs, 
    //  tvecs);
    // 打印相机内部参数和畸变系数
    // std::cout << "Camera Matrix:\n" << cameraMatrix << std::endl;
    // std::cout << "Distortion Coefficients:\n" << distCoeffs << std::endl;
    return 0;
}
