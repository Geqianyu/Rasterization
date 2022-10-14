
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
    double xCoord = textureCoord.x() * m_width;
    double yCoord = textureCoord.y() * m_height;
    int xMax = (int)(xCoord + 0.5);
    int yMax = (int)(yCoord + 0.5);
    int xMin = xMax - 1;
    int yMin = yMax - 1;
    double xMinWeight = (double)xMax + 0.5 - xCoord;
    double xMaxWeight = 1.0 - xMinWeight;
    double yMinWeight = (double)yMax + 0.5 - yCoord;
    double yMaxWeight = 1.0 - yMinWeight;
    xMax = (xMax + m_width) % m_width;
    xMin = (xMin + m_width) % m_width;
    yMax = (yMax + m_height) % m_height;
    yMin = (yMin + m_height) % m_height;
    Eigen::Vector3d leftBottom = Eigen::Vector3d((double)(m_pTexture[m_channels * yMin * m_width + m_channels * xMin]) / 255.0, (double)(m_pTexture[m_channels * yMin * m_width + m_channels * xMin + 1]) / 255.0, (double)(m_pTexture[m_channels * yMin * m_width + m_channels * xMin + 2]) / 255.0);
    Eigen::Vector3d rightBottom = Eigen::Vector3d((double)(m_pTexture[m_channels * yMin * m_width + m_channels * xMax]) / 255.0, (double)(m_pTexture[m_channels * yMin * m_width + m_channels * xMax + 1]) / 255.0, (double)(m_pTexture[m_channels * yMin * m_width + m_channels * xMax + 2]) / 255.0);
    Eigen::Vector3d leftTop = Eigen::Vector3d((double)(m_pTexture[m_channels * yMax * m_width + m_channels * xMin]) / 255.0, (double)(m_pTexture[m_channels * yMax * m_width + m_channels * xMin + 1]) / 255.0, (double)(m_pTexture[m_channels * yMax * m_width + m_channels * xMin + 2]) / 255.0);
    Eigen::Vector3d rightTop = Eigen::Vector3d((double)(m_pTexture[m_channels * yMax * m_width + m_channels * xMax]) / 255.0, (double)(m_pTexture[m_channels * yMax * m_width + m_channels * xMax + 1]) / 255.0, (double)(m_pTexture[m_channels * yMax * m_width + m_channels * xMax + 2]) / 255.0);
    Eigen::Vector3d result = yMinWeight * (xMinWeight * leftBottom + xMaxWeight * rightBottom) + yMaxWeight * (xMinWeight * leftTop + xMaxWeight * rightTop);
    return result;
}