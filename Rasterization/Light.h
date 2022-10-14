#ifndef ____LIGHT_H____
#define ____LIGHT_H____

#include <Eigen/Dense>
#include <Eigen/Core>

/*
* Light 类，光源的信息
*/
class Light
{
public:
    Eigen::Vector3d m_ambient;              // 环境光强度
    Eigen::Vector3d m_direction;            // 定向光方向
    Eigen::Vector3d m_emission;             // 光源强度

public:
    Light();
    Light(const Light& light);
    Light(Eigen::Vector3d ambient, Eigen::Vector3d direction, Eigen::Vector3d emission);
    ~Light();
};

#endif // !____LIGHT_H____
