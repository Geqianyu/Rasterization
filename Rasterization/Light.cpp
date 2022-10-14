
#include "Light.h"

Light::Light()
{

}

Light::Light(const Light& light)
{
    m_ambient = light.m_ambient;
    m_direction = light.m_direction;
    m_emission = light.m_emission;
}

Light::Light(Eigen::Vector3d ambient, Eigen::Vector3d direction, Eigen::Vector3d emission)
{
    m_ambient = ambient;
    m_direction = direction;
    m_emission = emission;
}

Light::~Light()
{

}