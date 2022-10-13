
#include <iostream>
#include <fstream>

#include "Material.h"

Material::Material()
{

}

Material::~Material()
{

}

void Material::loadKa(std::string filePath)
{
    m_map_Ka = true;
    m_Ka_map.loadTexture(filePath);
}

void Material::loadKd(std::string filePath)
{
    m_map_Kd = true;
    m_Kd_map.loadTexture(filePath);
}

Eigen::Vector3d Material::Ka(Eigen::Vector2d textureCoord)
{
    if (m_map_Ka)
    {
        return m_Ka_map.texture(textureCoord);
    }
    else
    {
        return m_Ka;
    }
}

Eigen::Vector3d Material::Kd(Eigen::Vector2d textureCoord)
{
    if (m_map_Kd)
    {
        return m_Kd_map.texture(textureCoord);
    }
    else
    {
        return m_Kd;
    }
}