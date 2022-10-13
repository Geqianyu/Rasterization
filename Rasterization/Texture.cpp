
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "Texture.h"

Texture::Texture()
{

}

Texture::Texture(std::string textureFilePath)
{
    loadTexture(textureFilePath);
}

Texture::~Texture()
{
    if (m_pTexture != nullptr)
    {
        stbi_image_free(m_pTexture);
        m_pTexture = nullptr;
    }
}

void Texture::loadTexture(std::string textureFilePath)
{
    stbi_set_flip_vertically_on_load(true);
    m_pTexture = stbi_load(textureFilePath.c_str(), &m_width, &m_height, &m_channels, 0);
    if (m_pTexture == nullptr)
    {
        std::cout << "纹理加载失败: " << textureFilePath << std::endl;
        exit(-3);
    }
}

Eigen::Vector3d Texture::texture(Eigen::Vector2d textureCoord)
{
    int x = (int)(textureCoord.x() * m_width);
    int y = (int)(textureCoord.y() * m_height);
    return Eigen::Vector3d((double)(m_pTexture[m_channels * y * m_width + m_channels * x]) / 255.0, (double)(m_pTexture[m_channels * y * m_width + m_channels * x + 1]) / 255.0, (double)(m_pTexture[m_channels * y * m_width + m_channels * x + 2]) / 255.0);
}