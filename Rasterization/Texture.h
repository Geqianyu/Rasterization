#ifndef ____TEXTURE_H____
#define ____TEXTURE_H____

#include <windows.h>
#include <string>
#include <Eigen/Dense>
#include <Eigen/Core>

/*
* Texture 类，保存纹理
*/
class Texture
{
private:
    // 私有变量
    BYTE* m_pTexture = nullptr;
    int m_width = 0, m_height = 0, m_channels = 0;

public:
    // 公有函数
    Texture();
    Texture(std::string textureFilePath);
    ~Texture();

    void loadTexture(std::string textureFilePath);
    Eigen::Vector3d texture(Eigen::Vector2d textureCoord);
};

#endif // !____TEXTURE_H____
