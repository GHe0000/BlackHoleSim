#include "gr.hpp"
#include "ppm.hpp"

#include <eigen3/Eigen/src/Core/Matrix.h>
#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>

// 渲染参数设置
#define ASPECT_RATIO (16.0/9.0)
#define IMAGE_WIDTH 320
#define IMAGE_HEIGHT ((int)(IMAGE_WIDTH/ASPECT_RATIO))
#define SAMPLE_PER_PIXEL 1 // 单个像素的采样次数
#define SAVE_PATH "figure_800x450.ppm"

// 渲染图像
int main() {
    srand(time(NULL));

    // 创建一个空白图像
    ppm image(IMAGE_WIDTH, IMAGE_HEIGHT);
    // 创建一个 Camera 对象
    Camera camera;
    camera.setupCamera();
    camera.setCameraLookAt(Eigen::Vector3d(0,0,0));
    camera.setCameraPos(Eigen::Vector3d(0, 8, 0.1));
    
    char savePath[100] = {};

    double distence = 8.0;
    for(int n=0;n<90;n++) {
        double theta = 4 * n * PI / 180.0 + 0.1;
        Eigen::Vector3d pos(0, distence * sin(theta), distence * cos(theta));
        camera.setCameraPos(pos);
        if(theta > PI/2 and theta < 3*PI/2) {
            camera.setCameraViewUp(Eigen::Vector3d(0,-1,0));
        }
        std::cout << "---------- " << n << " / 90" << " ----------" <<  std::endl;
        // 保存路径
        sprintf(savePath, "./save/figure_%dx%d_%d.ppm", IMAGE_WIDTH, IMAGE_HEIGHT, n);

        unsigned int kk=0;
        for(unsigned int j=0;j<IMAGE_HEIGHT;j++) {
            for(unsigned int i=0;i<IMAGE_WIDTH;i++) {
                Color color = Eigen::Vector3d::Zero();
                for(int _=0; _<SAMPLE_PER_PIXEL; _++ ) { // 单个像素多次采样
                    double u = ((double)i + (double)rand() / RAND_MAX) / IMAGE_WIDTH;
                    double v = ((double)j + (double)rand() / RAND_MAX) / IMAGE_HEIGHT;
                    Ray ray = camera.genRay(u, v);
                    color += ray.getRayColor();
                }
                color /= SAMPLE_PER_PIXEL;
                image.r[kk] = floor(color[0] * 255);
                image.g[kk] = floor(color[1] * 255);
                image.b[kk] = floor(color[2] * 255);
                kk++;
            }
            // 渲染进度显示
            if((j+1) % 10 == 0) {
                std::cout << "Rendering " << (j+1) << " / " << IMAGE_HEIGHT << std::endl;
            }
        }
        image.write(savePath);
    }


    return 0;
 }
