#include "gr.hpp"

// 一个使用了 floor 函数的 mod 函数
// fmod 中其相当于将函数的 floor 改成了 x>0?floor(x):ceil(x)
// 即在大于 0 和小于 0 时的取整方向不同
// 因此这里需要单独实现 mod 函数
inline double floorMod(double x, double y) {
    return x - y * floor(x / y);
}

// 临时放置的吸积盘函数
// 之后应该会抽象成一个类，并通过物理模型计算吸积盘颜色
Eigen::Vector3d diskColor(double rMin, double rMax, double r) {
    double k = 2.5 / (rMax - rMin);
    double b = (5.0 * (rMin - 0.5 * rMax)) / (rMin - rMax);
    double rN = k * r + b;
    return Eigen::Vector3d(1.0 / (exp((rN-4.9) / 0.03) + 1), 2.0 / (exp((rN-5) / 0.3) + 1) -1, -pow(rN+3,3) * (rN-5)/432);
}


Ray::Ray(Eigen::Vector3d origin, Eigen::Vector3d direction) {
    this->origin = origin;
    this->direction = direction;
}

// TODO: 这里使用的是 Euler 法求解，可以改成 Runge-Kutta 法提高精度
Color Ray::getRayColor() {
    Color color = Eigen::Vector3d::Zero();
    Eigen::Vector3d origin = this->origin;
    Eigen::Vector3d direction = this->direction.normalized();
    Eigen::Vector3d x,y,z;
    x = origin.normalized();
    y = direction.cross(x).normalized();
    z = x.cross(y);
    Eigen::Matrix3d Ano; // Ano 为从 new 到 old 的变换矩阵
    Ano << x, y, z;
    Eigen::Matrix3d Aon = Ano.inverse(); // Aon 为从 old 到 new 的变换矩阵
    
    // 迭代计算初始值设置
    double phi = 0.0;
    double dphi = 0.001;

    double dudphi = -cos(acos(x.dot(direction))) / (sin(acos(x.dot(direction))) * origin.norm());
    Eigen::Vector3d accre_l = (Aon * y.cross(Eigen::Vector3d(0,1,0))).normalized();
    // WARNING:注意 mod 的符号问题
    double accre_phi1 = floorMod(atan2(accre_l[2], accre_l[0]) , 2*PI);
    double accre_phi2 = floorMod(atan2(accre_l[2], accre_l[0])+PI, 2*PI);
    double u = 1 / origin.norm();
    
    // Euler 法迭代计算
    for(int i=0;i<10000;i++) {
        phi += dphi;
        phi = floorMod(phi, 2*PI);
        dudphi += -u * (1 - 3.0/2.0 * u) * dphi; // 根据论文给出的光线的微分方程
        u += dudphi * dphi;
        double r = 1 / u;
        if (r > 500) break;
        if (r < 0.01) break;
        if (((phi - accre_phi1) * (phi - dphi - accre_phi1) <= 0) or ((phi - accre_phi2) * (phi - dphi - accre_phi2) <= 0)) { // 如果穿越吸积盘
            if (3 < r && r < 7) {
                color += diskColor(3, 7, r);
                break;
            }
            /*if (2.5 < r && r < 5) {*/
            /*    // TODO: 这里应该是计算吸积盘颜色，应单独调用吸积盘函数*/
            /*    color += Eigen::Vector3d(1.0 / (exp((r-4.9) / 0.03) + 1), 2.0 / (exp((r-5) / 0.3) + 1) -1, -pow(r+3,3) * (r-5)/432);*/
            /*    break;*/
            /*}*/
        }
    }
    return color;
}

void Camera::setupCamera() {
    // TODO: 实现摄像机参数设置
    this->fov = 60; // NOTE: 临时设置 
    this->aspectRatio = 16.0/9.0; // NOTE: 临时设置 
    this->lookFrom << 0.0, 1.0, 4.0;
    this->lookAt << 3.0, 0.0, 1.0;
    /*this->lookFrom << 0.0, 0.3, 3.0;*/
    /*this->lookAt << 0.9, 0.2, 0.0;*/
    this->viewUp << 0.0, 1.0, 0.0;
    double theta = this->fov * (PI / 180.0);
    double halfHeight = tan(theta / 2.0);
    double halfWidth = this->aspectRatio * halfHeight;
    this->camOrigin = this->lookFrom;
    Eigen::Vector3d w = (this->lookFrom - this->lookAt).normalized();
    Eigen::Vector3d u = (this->viewUp.cross(w)).normalized();
    Eigen::Vector3d v = w.cross(u);
    this->camUpperLeft = this->camOrigin - halfWidth * u + halfHeight * v - w;
    this->camHorizontal = 2 * halfWidth * u;
    this->camVertical = 2 * halfHeight * v;
}

Ray Camera::genRay(double u, double v) {
    return Ray(this->camOrigin,
            this->camUpperLeft
            + u * this->camHorizontal
            - v * this->camVertical
            - this->camOrigin);
}
