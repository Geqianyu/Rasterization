#ifndef _GQY_LIGHT_H_
#define _GQY_LIGHT_H_

#include "Math.h"

/*
* Light 类，光源的信息
*/
class Light
{
public:
    GQYMath::vec3 m_ambient;              // 环境光强度
    GQYMath::vec3 m_direction;            // 定向光方向
    GQYMath::vec3 m_emission;             // 光源强度

public:
    Light();
    Light(const Light& _light);
    Light(GQYMath::vec3 _ambient, GQYMath::vec3 _direction, GQYMath::vec3 _emission);
    ~Light();
};

#endif // !_GQY_LIGHT_H_
