
#include "Light.h"

Light::Light()
{

}

Light::Light(const Light& _light) : m_ambient(_light.m_ambient), m_direction(_light.m_direction), m_emission(_light.m_emission)
{

}

Light::Light(GQYMath::vec3 _ambient, GQYMath::vec3 _direction, GQYMath::vec3 _emission) : m_ambient(_ambient), m_direction(_direction), m_emission(_emission)
{

}

Light::~Light()
{

}