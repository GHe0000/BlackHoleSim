# BlackHoleSim

一个个人的练手项目，其渲染了 Schwarzschild 黑洞吸积盘的图像

## 编译要求

需要安装 cmake，eigen

仓库中的 cmake 设置了使用 clang 编译，可自行改成 gcc 编译

## 运行说明

（下面在代码中修改的参数之后会以一种更好的方式设置）

编译运行前可先修改 main.cpp 中的参数，如文件保存位置，渲染分辨率，比例等参数

在 gr.cpp 中的 Camera 类中可以设置相机位置、视角等参数

运行完成后，其会导出一个 PPM 文件，可以通过 tools 中的 ppm2png 工具转换为 PNG 格式（需要安装 Python 和 Pillow 库）

## 原理简介

一个简单的光线追踪，光线在 Schwarzschild 黑洞附近的轨迹通过下面方程计算（参考论文：Real-time High-Quality Rendering of Non-Rotating Black Holes Eric Bruneton arXiv:2010.08735）：

$$ \ddot{u} = \frac{3}{2} u^2 - u $$

其中 $u$ 为距离黑洞中心的距离的倒数
