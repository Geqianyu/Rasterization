
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "Texture.h"

Texture::Texture()
{

}

Texture::Texture(std::string _texture_file_path)
{
    load_texture(_texture_file_path);
}

Texture::~Texture()
{
    if (m_pTexture != nullptr)
    {
        stbi_image_free(m_pTexture);
        m_pTexture = nullptr;
    }
}

void Texture::load_texture(std::string _texture_file_path)
{
    stbi_set_flip_vertically_on_load(true);
    m_pTexture = stbi_load(_texture_file_path.c_str(), &m_width, &m_height, &m_channels, 0);
    if (m_pTexture == nullptr)
    {
        std::cout << "纹理加载失败: " << _texture_file_path << std::endl;
        exit(-3);
    }
}

GQYMath::vec3 Texture::texture(GQYMath::vec2 _texture_coord)
{
    double x_coord = _texture_coord.u * m_width;
    double y_coord = _texture_coord.v * m_height;
    int x_max = (int)(x_coord + 0.5);
    int y_max = (int)(y_coord + 0.5);
    int x_min = x_max - 1;
    int y_min = y_max - 1;
    double x_min_weight = (double)x_max + 0.5 - x_coord;
    double x_max_weight = 1.0 - x_min_weight;
    double y_min_weight = (double)y_max + 0.5 - y_coord;
    double y_max_weight = 1.0 - y_min_weight;
    x_max = (x_max + m_width) % m_width;
    x_min = (x_min + m_width) % m_width;
    y_max = (y_max + m_height) % m_height;
    y_min = (y_min + m_height) % m_height;
    GQYMath::vec3 left_bottom = GQYMath::vec3((double)(m_pTexture[m_channels * y_min * m_width + m_channels * x_min]) / 255.0, (double)(m_pTexture[m_channels * y_min * m_width + m_channels * x_min + 1]) / 255.0, (double)(m_pTexture[m_channels * y_min * m_width + m_channels * x_min + 2]) / 255.0);
    GQYMath::vec3 right_bottom = GQYMath::vec3((double)(m_pTexture[m_channels * y_min * m_width + m_channels * x_max]) / 255.0, (double)(m_pTexture[m_channels * y_min * m_width + m_channels * x_max + 1]) / 255.0, (double)(m_pTexture[m_channels * y_min * m_width + m_channels * x_max + 2]) / 255.0);
    GQYMath::vec3 left_top = GQYMath::vec3((double)(m_pTexture[m_channels * y_max * m_width + m_channels * x_min]) / 255.0, (double)(m_pTexture[m_channels * y_max * m_width + m_channels * x_min + 1]) / 255.0, (double)(m_pTexture[m_channels * y_max * m_width + m_channels * x_min + 2]) / 255.0);
    GQYMath::vec3 right_top = GQYMath::vec3((double)(m_pTexture[m_channels * y_max * m_width + m_channels * x_max]) / 255.0, (double)(m_pTexture[m_channels * y_max * m_width + m_channels * x_max + 1]) / 255.0, (double)(m_pTexture[m_channels * y_max * m_width + m_channels * x_max + 2]) / 255.0);
    GQYMath::vec3 result = y_min_weight * (x_min_weight * left_bottom + x_max_weight * right_bottom) + y_max_weight * (x_min_weight * left_top + x_max_weight * right_top);
    return result;
}