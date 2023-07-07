#include "my_camera.hpp"
#include "MVSDK/CameraDefine.h"
namespace mvsdk_try
{
// template<typename T,typename... Args>
// inline void assert_warning(T expr,Args... args){
//    if(!expr){
//     fmt::print(fg(fmt::color::orange), "[WARNING] {} \n", std::forward<Args>(args)...);
//    }
// }
#define MV_CHECK_API_ERROR(expr, info, ...)                                           \
    do {                                                                              \
        auto status = (expr);                                                         \
        if (status != CAMERA_STATUS_SUCCESS) {                                        \
            fmt::print(                                                               \
                fg(fmt::color::red), "[ERROR] '" #expr "' = ({}) " info "\n", status, \
                ##__VA_ARGS__);                                                       \
            return false;                                                             \
        }                                                                             \
    } while (0)
#define MV_ASSERT_ERROR(expr, info, ...)                                                \
    do {                                                                                \
        if ((expr) == false) {                                                          \
            fmt::print(fg(fmt::color::red), "[ERROR] " #expr info "\n", ##__VA_ARGS__); \
            return false;                                                               \
        }                                                                               \
    } while (0)
#define MV_CHECK_API_WARNING(expr, info, ...)                                         \
    do {                                                                              \
        auto status = (expr);                                                         \
        if (status != CAMERA_STATUS_SUCCESS) {                                        \
            fmt::print(                                                               \
                fg(fmt::color::orange), "[WARNING] '" #expr "' = ({}) " info, status, \
                ##__VA_ARGS__);                                                       \
        }                                                                             \
    } while (0)
My_Camera::My_Camera(const char * camera_cfg) : camera_cfg(camera_cfg)
{
    CameraSdkInit(1);
    handle = -1;
}
bool My_Camera::open(){
    if (isOpen()) {
        if (!close()) return false;
    }
    //相机设备信息
    tSdkCameraDevInfo infos[2];
    int dev_num = 2;
    //获得设备的信息, dev_num返回找到的相机个数
    CameraEnumerateDevice(infos, &dev_num);
    if(!(dev_num>0)){
        fmt::print("未发现设备!");
    }

    //相机初始化，根据相机型号名从文件中加载参数，例如MV-U300
    CameraInit(&infos[0], PARAM_MODE_BY_MODEL, -1, &handle);

    MV_ASSERT_ERROR(dev_num > 0, "未发现设备！");

    // tSdkCameraCapbility tCapability;  //设备描述信息
    // //获得相机的信息
    // CameraGetCapability(handle, &tCapability);
    fmt::print("配置文件路径：{}\n", camera_cfg);
    //加载相机参数
    MV_CHECK_API_WARNING(
        CameraReadParameterFromFile(handle, (char *)camera_cfg.data()),
        "从文件读取相机配置文件错误，路径为: {}", camera_cfg);
    //使驱动开始工作，接受来自相机的图像
    MV_CHECK_API_ERROR(CameraPlay(handle), "");
    //设置相机传入的图片形式
    MV_CHECK_API_ERROR(CameraSetIspOutFormat(handle, CAMERA_MEDIA_TYPE_BGR8), "");

    return true;
}
bool My_Camera::read(cv::Mat &img)const
{
     if(!isOpen()){
     fmt::print("open fail");
     return false;
     }
     //帧头
    tSdkFrameHead head;
    //缓冲区
    BYTE * buffer;
    //获取一帧图片
    CameraGetImageBuffer(handle, &head, &buffer, 1000);
    img = cv::Mat(head.iHeight, head.iWidth, CV_8UC3);
    //处理图片
    CameraImageProcess(handle, buffer, img.data, &head);
    //释放缓冲区
    CameraReleaseImageBuffer(handle, buffer);
    return true;
}
bool My_Camera::isOpen()const{
    return handle >= 0;
}
bool My_Camera::close(){
    if (handle < 0){
        fmt::print("相机已经关闭！\n");
        return true;
    }
    //逆初始化（好奇怪的起名，不应该是注销吗）
    MV_CHECK_API_ERROR(CameraUnInit(handle), "");
    handle = -1;
    return true;
}
My_Camera::~My_Camera(){
   if (isOpen()) {
        close();
    }
    fmt::print(fg(fmt::color::red) | fmt::emphasis::bold, "相机已释放！");
}
}