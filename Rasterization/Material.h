#ifndef _GQY_MATERIAL_H_
#define _GQY_MATERIAL_H_

#include <string>

#include "Math.h"
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
    GQYMath::vec3 m_Ka;
    GQYMath::vec3 m_Kd;
    GQYMath::vec3 m_Ks;
    GQYMath::vec3 m_Ke;
    bool m_map_Ka = false;
    Texture m_Ka_map;
    bool m_map_Kd = false;
    Texture m_Kd_map;

public:
    // 公有函数
    Material();
    ~Material();

    GQYMath::vec3 Ka(GQYMath::vec2 _texture_coord);
    GQYMath::vec3 Kd(GQYMath::vec2 _texture_coord);

    void loadKa(std::string _file_path);
    void loadKd(std::string _file_path);
};

#endif // !_GQY_MATERIAL_H_
