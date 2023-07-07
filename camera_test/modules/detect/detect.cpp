#include "detect.hpp"
/*代码逻辑：
   1 、 构造函数：读取配置文件的参数
   2 、 detect：功能实现函数
   3 、 process：二值化处理图片
   4 、 isLight：判定是否为灯条，根据灯条长宽比，倾斜角度的最大值和最小值的区间进行判定
   5 、 isArmour: 判定是否为装甲板以及大小类型，由长度比和长宽比以及倾斜角比判断
   6 、 containLight: 判定两个灯条之间是否存在其他灯条，
                      遍历所有匹配到的灯条的顶点、底部以及中心点是否在两个灯条之间的roi区域。
   6 、 match_lights: 匹配灯条，通过提取ROI区域，先判定是否为等条，然后获取ROI区域中R通道和B通道的色素点的数量，
                      进行对比确认红灯，蓝灯，最后将灯条对象存入作为light的vector容器中进行下一步的匹配装甲板。
   7 、 match_Armour: 根据匹配到的灯条来进行判定


   构造函数 -----> detect ------> process -----> match_lights--------->match_Armour
                                                  isLight        containLight以及isArmour
*/
namespace Detect{
Detect::Detect(Robot::Color &color):color(color)
{
   //从文件读取配置参数
    cv::FileStorage file(PROJECT_DIR "/Configs/detect/detect.yaml", cv::FileStorage::READ);
    //阈值
    if (color == Robot::Color::RED) {
        file["Thresholds"]["red"]["lowerb"] >> lowerb;
        file["Thresholds"]["red"]["upperb"] >> upperb;
    } else {
        file["Thresholds"]["blue"]["lowerb"] >> lowerb;
        file["Thresholds"]["blue"]["upperb"] >> upperb;
    }
    //灯条匹配条件参数
    file["light"]["min_ratio"] >> light_params.min_ratio;
    file["light"]["max_ratio"] >> light_params.max_ratio;
    file["light"]["max_angle"] >> light_params.max_angle;
    //装甲板匹配条件参数
    file["armour"]["max_angle"] >> armour_params.max_angle;
    file["armour"]["min_light_ratio"] >> armour_params.min_light_ratio;
    file["armour"]["min_small_center_distance"] >> armour_params.min_small_center_distance;
    file["armour"]["max_small_center_distance"] >> armour_params.max_small_center_distance;
    file["armour"]["min_large_center_distance"] >> armour_params.min_large_center_distance;
    file["armour"]["max_large_center_distance"] >> armour_params.max_large_center_distance;
}
//Detection_pack 为打包好的图片数据结构体
bool Detect::detect(Robot::Detection_pack & detection_pack){
     cv::Mat process_img;
    //  cv::Mat img=detection_pack.img;
     std::vector<Robot::Light> lights;
     //图片处理
    process(detection_pack.img,process_img);
    cv::imshow("process_image",process_img);
    //匹配灯条
    match_lights(detection_pack.img,process_img,lights);
    //匹配装甲板
    match_Armour(lights,detection_pack.armours);
    return true;
}
bool Detect::process(cv::Mat &img,cv::Mat &process_img)
{
    cv::Mat tempImage;

    //颜色空间的转化             
    cv::cvtColor(img, tempImage, cv::COLOR_BGR2HSV);
    //二值化, 在高低阈值内值为1(白色), 在阈值外则为0(黑色)
    cv::inRange(tempImage, lowerb, upperb, process_img);
    return true;
}
bool Detect::match_Armour(const std::vector<Robot::Light> & lights, std::vector<Robot::Armour> & armours)
{
     for (int i = 0; i < lights.size(); i++) {
        for (int j = i + 1; j < lights.size(); j++) {
            auto & light1 = lights[i];
            auto & light2 = lights[j];
            if (light1.color != color || light2.color != color) {
                continue;
            }
            if (containLight(light1, light2, lights)) {
                continue;
            }
            auto armour = Robot::Armour(light1, light2);
            if (isArmour(armour)) {
                armours.emplace_back(armour);
            }
        }
    }
    return true;
}
bool Detect::match_lights(const cv::Mat &img,const cv::Mat &process_img,std::vector<Robot::Light> &lights)
{
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(process_img,contours,
    cv::RETR_EXTERNAL,
    cv::CHAIN_APPROX_SIMPLE);
    for(const auto &contour:contours){
        //拟合旋转矩形并利用Robot的Light结构体进行匹配灯条
        auto light=Robot::Light(cv::minAreaRect(contour));
        if(!isLight(light))
        continue;
        //获取能够对应图片位置的ROI区域
        auto rect=light.boundingRect();
        //判定ROI是否超出图片边界
        bool isIn=!(rect.x >= 0 && rect.width >= 0 && rect.x + rect.width <= img.cols &&
              rect.y >= 0 && rect.height >= 0 && rect.y + rect.height <= img.rows);
        if(isIn)
        continue;
        //通过Mat的重载运算符提取ROI区域
        auto roi=img(rect);
        //Red通道的色素，Blue通道的色素
        int r_sum=0,b_sum=0;
        for(int i=0;i<roi.cols;i++)
        for(int j=0;j<roi.rows;j++){
            if(cv::pointPolygonTest(contour,cv::Point2f(i + rect.x, j + rect.y),false)>=0){
                r_sum+=roi.at<cv::Vec3b>(i,j)[2];
                b_sum+=roi.at<cv::Vec3b>(i,j)[0];
            }
        }
        light.color= r_sum> b_sum ?Robot::Color::RED : Robot::Color::BLUE;
        lights.emplace_back(light);
    }
    return true;
}
//判断是否为装甲板以及大小
//长度比 中心距离比 倾斜角度比
bool Detect::isArmour(Robot::Armour &armour)
{
    bool length_ratio_condition,center_length_ratio_condition,angle_ratio_condition,isArmour;

    auto light1=armour.left_light;
    auto light2=armour.right_light;
    //长度比
    length_ratio_condition=std::abs(light1.length-light2.length)/armour_params.min_light_ratio;

    //中心距离比
    auto x=std::abs(light1.center.x-light2.center.x);
    auto y=std::abs(light1.center.y-light2.center.y);
    auto distance=std::sqrt(x*x+y*y);
    double center_ratio=((light1.length+light2.length)/2)>distance
     ?((light1.length+light2.length)/2)/distance
     :distance/((light1.length+light2.length)/2);
    center_length_ratio_condition=(armour_params.min_small_center_distance < center_ratio &&
                                      center_ratio < armour_params.max_small_center_distance) ||
                                     (armour_params.min_large_center_distance < center_ratio &&
                                      center_ratio < armour_params.max_large_center_distance);
    armour.armour_type = center_ratio > armour_params.min_large_center_distance
                             ? Robot::ArmourType::Big
                             : Robot::ArmourType::Small;

    cv::Point2f diff = light1.center - light2.center;
    float angle      = std::abs(std::atan(diff.y / diff.x));
    angle_ratio_condition=angle<armour_params.max_angle;
    isArmour=angle_ratio_condition&&length_ratio_condition&&center_length_ratio_condition;
    return isArmour;
}
//根据灯条长宽比和倾斜角度的最大值和最小值的区间进行匹配
bool Detect::isLight(Robot::Light &light)
{
    //灯条长宽比
    float ratio          = light.width / light.length;  //短 / 长
    bool ratio_condition = light_params.min_ratio < ratio && ratio < light_params.max_ratio;
    //灯条倾斜角
    bool angle_condition = light.tile_angle < light_params.max_angle;

    bool is_light = ratio_condition && angle_condition;
    return is_light;
}
//判断两个灯条之间是否包含其他灯条
bool Detect::containLight(const Robot::Light & light1, const Robot::Light & light2,
    const std::vector<Robot::Light> & lights)
{
   auto points=std::vector<cv::Point2f>{light1.top,light1.bottom,
                                        light2.top,light2.bottom};
   auto roi=cv::boundingRect(points);
   for(const auto &light :lights){
    if(light.center==light1.center||light.center==light2.center)
      continue;
      //通过获取灯条的顶点和底部以及中心点来判断是否在区域内
    if(roi.contains(light.bottom)||roi.contains(light.top)||roi.contains(light.center))
       return true;
   }
   return false;
}
}