// double calibrateCamera(const std::vector<std::vector<cv::Point3f>>& objectPoints,
//                        const std::vector<std::vector<cv::Point2f>>& imagePoints,
//                        const cv::Size& imageSize,
//                        cv::Mat& cameraMatrix,
//                        cv::Mat& distCoeffs,
//                        std::vector<cv::Mat>& rvecs,
//                        std::vector<cv::Mat>& tvecs,
//                        int flags = 0,
//                        cv::TermCriteria criteria = 
// cv::TermCriteria(cv::TermCriteria::COUNT + cv::TermCriteria::EPS, 30, DBL_EPSILON));

// 当使用calibrateCamera函数进行相机标定时，需要提供以下参数：

// 版本一参数解释（需要12个参数）：
// objectPoints：输入参数，包含物体点的向量的向量，每个向量包含一系列3D点的坐标。每个3D点对应于标定板上的一个角点。
// imagePoints：输入参数，包含图像点的向量的向量，每个向量包含一系列2D点的坐标。每个2D点对应于objectPoints中的一个3D点在图像上的投影。
// imageSize：输入参数，图像的大小（宽度和高度）。
// cameraMatrix：输入/输出参数，包含相机内部参数的3x3矩阵。在函数调用之前，可以将其初始化为一个合理的猜测，然后在函数调用后，它将被相机标定结果覆盖。
// distCoeffs：输入/输出参数，包含相机畸变系数的向量（k1，k2，p1，p2，k3）。在函数调用之前，可以将其初始化为一个合理的猜测，然后在函数调用后，它将被相机标定结果覆盖。
// rvecs：输出参数，旋转向量的输出数组，用于表示每个图像的相机旋转矩阵。
// tvecs：输出参数，平移向量的输出数组，用于表示每个图像的相机平移矩阵。
// stdDeviationsIntrinsics：输出参数，用于返回内部参数的标准差估计值。
// stdDeviationsExtrinsics：输出参数，用于返回外部参数（旋转和平移）的标准差估计值。
// perViewErrors：输出参数，用于返回每个图像的重投影误差。
// flags：输入参数，标定标志，用于指定标定过程中的特定选项和操作。
// criteria：输入参数，终止准则，用于指定标定过程的停止条件。



// 版本二参数解释（需要9个参数）：
// objectPoints：输入参数，包含物体点的向量的向量，每个向量包含一系列3D点的坐标。每个3D点对应于标定板上的一个角点。
// imagePoints：输入参数，包含图像点的向量的向量，每个向量包含一系列2D点的坐标。每个2D点对应于objectPoints中的一个3D点在图像上的投影。
// imageSize：输入参数，图像的大小（宽度和高度）。
// cameraMatrix：输入/输出参数，包含相机内部参数的3x3矩阵。
在函数调用之前，可以将其初始化为一个合理的猜测，然后在函数调用后，它将被相机标定结果覆盖。
// distCoeffs：输入/输出参数，包含相机畸变系数的向量（k1，k2，p1，p2，k3）。
在函数调用之前，可以将其初始化为一个合理的猜测，然后在函数调用后，它将被相机标定结果覆盖。
// rvecs：输出参数，旋转向量的输出数组，用于表示每个图像的相机旋转矩阵。
// tvecs：输出参数，平移向量的输出数组，用于表示每个图像的相机平移矩阵。
// flags：输入参数，标定标志，用于指定标定过程中的特定选项和操作。
// criteria：输入参数，终止准则，用于指定标定过程的停止条件。