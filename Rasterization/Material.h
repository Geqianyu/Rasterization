#ifndef ____MATERIAL_H____
#define ____MATERIAL_H____

#include <Eigen/Dense>
#include <Eigen/Core>
#include <string>

#include "Texture.h"

/*
Material 类，用于存储材质相关信息
*/
class Material
{
public:
    // 公有变量
    double m_Ns = 1.0;
    double m_Ni = 1.0;
    double m_d = 1.0;
    double m_Tr = 0.0;
    Eigen::Vector3d m_Tf;
    Eigen::Vector3d m_Ka;
    Eigen::Vector3d m_Kd;
    Eigen::Vector3d m_Ks;
    Eigen::Vector3d m_Ke;
    bool m_map_Ka = false;
    Texture m_Ka_map;
    bool m_map_Kd = false;
    Texture m_Kd_map;

public:
    // 公有函数
    Material();
    ~Material();

    Eigen::Vector3d Ka(Eigen::Vector2d textureCoord);
    Eigen::Vector3d Kd(Eigen::Vector2d textureCoord);

    void loadKa(std::string filePath);
    void loadKd(std::string filePath);
};

#endif // !____MATERIAL_H____
