#ifndef _DETECT_HPP_
#define _DETECT_HPP_
#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
#include "../../utils/robot.hpp"
namespace Detect{
class Detect{
private:
    const Robot::Color color;//敌方颜色
    cv::Scalar lowerb, upperb;          //二值化的高低阈值
    Robot::LightParams light_params;    //灯条条件参数
    Robot::ArmourParams armour_params;  //装甲板条件参数
public:   
   explicit Detect(Robot::Color &);
   bool detect(Robot::Detection_pack & detection_pack);
private:
   bool process(cv::Mat &,cv::Mat &);
   bool match_lights(const cv::Mat &,const cv::Mat &,std::vector<Robot::Light> &);
   bool match_Armour(const std::vector<Robot::Light> &, std::vector<Robot::Armour> &);
   bool containLight(const Robot::Light &, const Robot::Light &,const std::vector<Robot::Light> &);
   bool isArmour(Robot::Armour &);
   bool isLight(Robot::Light &);
   Detect(Detect const &) = delete;
   Detect & operator=(Detect const &) = delete;
};


}
#endif 