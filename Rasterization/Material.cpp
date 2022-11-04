
#include <iostream>
#include <fstream>

#include "Material.h"

Material::Material()
{

}

Material::~Material()
{

}

void Material::loadKa(std::string _file_path)
{
    m_map_Ka = true;
    m_Ka_map.load_texture(_file_path);
}

void Material::loadKd(std::string _file_path)
{
    m_map_Kd = true;
    m_Kd_map.load_texture(_file_path);
}

GQYMath::vec3 Material::Ka(GQYMath::vec2 _texture_coord)
{
    if (m_map_Ka)
    {
        return m_Ka_map.texture(_texture_coord);
    }
    else
    {
        return m_Ka;
    }
}

GQYMath::vec3 Material::Kd(GQYMath::vec2 _texture_coord)
{
    if (m_map_Kd)
    {
        return m_Kd_map.texture(_texture_coord);
    }
    else
    {
        return m_Kd;
    }
}