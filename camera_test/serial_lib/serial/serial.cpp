#include "serial.hpp"

namespace Serial{

    Serial::Serial(const char* file){
          // 给串口设备赋权，使它可以读写
    system("sudo -S chmod 777 /dev/ttyUSB0");
    fd = open(file, O_RDWR);

    // 串口打开失败
    if (fd == -1)
      throw "open fail ...";

    struct termios options;

    // 获取fd的属性结构体
    tcgetattr(fd, &options);

    options.c_iflag = IGNPAR;                         //输入模式
    options.c_oflag = 0;                              //输出模式
    options.c_cflag = B115200 | CS8 | CLOCAL | CREAD; //控制模式
    options.c_lflag = 0;                              //本地模式
    options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);

    options.c_cc[VTIME] = 0; //最少读取字符数
    options.c_cc[VMIN] = 1;  //超时时间, 单位: 100ms

    tcsetattr(fd, TCSANOW, &options); //应用上面的设置
    std::cout<<"read get!!!"<<std::endl;
}

//14帧
 void Serial::read_data(std::uint8_t buff[], cv::Mat &canvas) {
    if (fd == -1) {
      std::cout << "open fail..." << std::endl;
      return;
    }
    // 字体
    auto font_face = cv::FONT_HERSHEY_COMPLEX;
    // 颜色
    auto font_color = cv::Scalar(0, 0, 0);
    cv::Point point;
    point.x = 0, point.y = 30;
    while (true) {
      // auto st = std::clock();
      if (read(fd, buff, 1) == 1) {
        uint8_t frame_head = buff[0];
        // 帧头正确
        if (frame_head == 0xff) {
          if (read(fd, buff + 1, 13) == 13) {
            std::uint8_t frame_tail = buff[13];
            std::cout << frame_tail;
            data convert_data;
            // 帧尾正确
            if (frame_tail == 0xfe) {
              // 转换#include "serial.hpp"数据格式
              for(int i=0;i<12;i++)
              convert_data.data[i] = buff[i+1];
              // convert_data.data[1] = buff[1];
              // 将十六为数据转为string可以画在Mat上
              auto data = std::to_string(convert_data.o);
              // cv::putText(canvas, data, point, font_face, 1, font_color, 2);
              // cv::imshow("img", canvas);
              // 按下esc结束程序
              int k = cv::waitKey(2);
              if (k == 27)
                break;
              // 竖直方向画出数字
              point.y += 30;
              if (point.y > canvas.rows) {
                point.y = 30; 
                point.x += 120;
              }
              // 休眠20ms
              std::this_thread::sleep_for(std::chrono::milliseconds(20));
            }
          }
          if (read(fd, buff + 1, 3) < 3)
            break;
        }
      }
      auto ed = std::clock();
      // std::cout << "spend :" << double(ed - st) / CLOCKS_PER_SEC  << "ms" <<
      // std::endl;
    }
  }
    }
