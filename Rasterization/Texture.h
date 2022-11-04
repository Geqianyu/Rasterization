#ifndef _GQY_TEXTURE_H_
#define _GQY_TEXTURE_H_

#include <windows.h>
#include <string>

#include "Math.h"

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
    Texture(std::string _texture_file_path);
    ~Texture();

    void load_texture(std::string _texture_file_path);
    GQYMath::vec3 texture(GQYMath::vec2 _texture_coord);
};

#endif // !_GQY_TEXTURE_H_
