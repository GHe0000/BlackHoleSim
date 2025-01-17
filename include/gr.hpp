#include <eigen3/Eigen/Eigen>
#include <eigen3/Eigen/src/Core/GlobalFunctions.h>
#include <eigen3/Eigen/src/Core/Matrix.h>
#include <eigen3/Eigen/src/Core/BooleanRedux.h>


#define PI 3.1415926535897932384626434

// Light Propagation in GR by C++
// 此库用来计算史瓦西时空中的光线传播

#ifndef GR_HPP
#define GR_HPP

typedef Eigen::Vector3d Color;

class Ray {
    public:
        Eigen::Vector3d origin;
        Eigen::Vector3d direction;
        
        Color getRayColor();
        Ray(Eigen::Vector3d origin, Eigen::Vector3d direction);
};

class Camera {
    public:
        double fov;
        double aspectRatio;
        Eigen::Vector3d lookFrom;
        Eigen::Vector3d lookAt;
        Eigen::Vector3d viewUp;
        
        Eigen::Vector3d camUpperLeft;
        Eigen::Vector3d camHorizontal;
        Eigen::Vector3d camVertical;
        Eigen::Vector3d camOrigin;
        
        void setupCamera();
        Ray genRay(double u, double v);
};

#endif
