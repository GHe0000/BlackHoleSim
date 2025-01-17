#include <iostream>
#include "gr.hpp"
#include <eigen3/Eigen/Eigen>

int main() {
    double u = 154.0/320.0;
    double v = 154.0/180.0;

    Camera camera;
    camera.setupCamera();

    Ray ray = camera.genRay(u, v);
    Color color = ray.getRayColor();
    std::cout << color << std::endl;
    return 0;
}

