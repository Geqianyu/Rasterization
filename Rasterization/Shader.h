#ifndef _GQY_SHADER_H_
#define _GQY_SHADER_H_

#include <Windows.h>
#include "Math.h"
#include "obj.h"
#include "Camera.h"
#include "Light.h"

/*
Shader 类，模拟渲染管线
*/
class Shader
{
private:
    // 私有变量
    Obj* m_obj = nullptr;
    GQYMath::mat4 m_matrix;
    GQYMath::vec3 m_light_ambient;
    GQYMath::vec3 m_light_direction;
    GQYMath::vec3 m_light_emission;
    Point3 m_camera_position;
    std::vector<Point4> m_gl_vertices;
    double* m_zBuffer = nullptr;
    BYTE* m_frameBuffer = nullptr;
    int m_width = 0;
    int m_height = 0;

public:
    // 公有函数
    Shader(Obj* _obj, int _width, int _height);
    ~Shader();

    BYTE* shading(Camera& _camera, Light& _light, GQYMath::mat4& _translate);

private:
    // 私有函数
    void vertex_shading();
    void triangles_shading();
    void rasterization(int& _index);
    void setpixel(double& _alpha, double& _beta, double& _gama, int& _index, int& _x_position, int& _y_position);
    Color fragment_shader(Point3& _fragment_position, GQYMath::vec3& _fragment_normal, GQYMath::vec2& _fragment_texture, std::string& _material);
};

#endif // !_GQY_SHADER_H_