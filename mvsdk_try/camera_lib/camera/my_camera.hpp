#ifndef _MY_CAMERA_HPP
#define _MY_CAMERA_HPP

#include <opencv2/opencv.hpp>

#include <fmt/color.h>
#include <fmt/core.h>
#include <stdexcept>

#include "MVSDK/CameraApi.h"

namespace mvsdk_try{
class My_Camera{
private:
    CameraHandle handle; //相机句柄
    const std::string camera_cfg;
public:
    explicit My_Camera(const char *camera_cfg = PROJECT_DIR"/Configs/camera/MV-SUA133GC-T-Manifold.config");
    bool read(cv::Mat &) const;
    bool open();
    bool close();
    bool isOpen()const;
    ~My_Camera();
};
}


#endif 