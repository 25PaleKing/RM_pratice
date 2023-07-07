#include <iostream>
#include <fmt/color.h>
#include <opencv2/opencv.hpp>
#include <opencv2/calib3d/calib3d.hpp>
// #include "serial_lib/serial/serial.hpp"
#include "camera_lib/camera/my_camera.hpp"
#include "modules/detect/detect.hpp"

void video_detect_test(){
    cv::VideoCapture video;
    auto color=Robot::Color::BLUE;
    Detect::Detect data{color};
    video.open(0);
    while(video.isOpened()){
        cv::Mat img;
        video>>img;
        Robot::Detection_pack detection_pack(img);
        data.detect(detection_pack);
        cv::putText(detection_pack.img,std::to_string(detection_pack.armours.size()),cv::Point2f(0, 40), cv::FONT_HERSHEY_SIMPLEX,1, cv::Scalar(0, 0, 255));
        Robot::drawArmours(detection_pack.armours,detection_pack.img,color);
        cv::imshow("detect_img",img);
        auto k=cv::waitKey(2);
        if(k==27)
        break;
    }
}

void camera_detect_test(){
    mvsdk_try::My_Camera my_camera;
    auto color=Robot::Color::BLUE;
    Detect::Detect data{color};
    my_camera.open();
    cv::Mat img;
    while (my_camera.isOpen()) {
       my_camera.read(img);
        Robot::Detection_pack detection_pack(img);
        data.detect(detection_pack);
        cv::putText(detection_pack.img,std::to_string(detection_pack.armours.size())
        ,cv::Point2f(detection_pack.img.cols/2,detection_pack.img.rows/2), cv::FONT_HERSHEY_SIMPLEX,1, cv::Scalar(0, 0, 255));
        Robot::drawArmours(detection_pack.armours,detection_pack.img,color);
        cv::imshow("detect_img",img);
        auto k=cv::waitKey(2);
        if(k==27)
        break;
    }
}