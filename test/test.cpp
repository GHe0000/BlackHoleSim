#include "gr.hpp"
#include "ppm.hpp"

#include <eigen3/Eigen/src/Core/Matrix.h>
#include <iostream>

// 临时测试
// 非 0 输入：
// 1.6 0 0
//   0 1 0
int main() {
    Ray ray(Eigen::Vector3d::Zero(), Eigen::Vector3d::Zero());
    // 从输入中读取光线的起点和方向
    std::cin >> ray.origin[0] >> ray.origin[1] >> ray.origin[2];
    std::cin >> ray.direction[0] >> ray.direction[1] >> ray.direction[2];
    // 调用 updateEuler 函数计算颜色
    Color color = ray.getRayColor();
    // 输出颜色
    std::cout << color[0] << " " << color[1] << " " << color[2] << std::endl;
    return 0;
}
