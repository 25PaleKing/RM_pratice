#include <iostream>
#include <fmt/color.h>
#include <opencv2/opencv.hpp>
#include <opencv2/calib3d/calib3d.hpp>
// #include "serial_lib/serial/serial.hpp"
#include "camera_lib/camera/my_camera.hpp"
#include "modules/detect/detect.hpp"
#include "test.cpp"
int main(){
    // video_detect_test();
    camera_detect_test();
}