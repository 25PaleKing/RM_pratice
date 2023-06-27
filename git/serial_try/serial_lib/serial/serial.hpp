#include <fcntl.h> //文件控制选项头文件
#include <iostream>
#include <opencv2/opencv.hpp>
#include <stdlib.h>
#include <termios.h> //linux串口相关的头文件
#include <unistd.h>
#include <thread>
#include <fmt/color.h>

namespace Serial {
  union data{
   std::uint8_t data[12];
   uint16_t o;
};
class Serial {
private:
  int fd;
public:
  Serial(const char* file);
  ~Serial() = default;
public:
  void read_data(std::uint8_t buff[], cv::Mat &canvas);
};
} // namespace Serial