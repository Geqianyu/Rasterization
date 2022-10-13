#ifndef ____SHADER_H____
#define ____SHADER_H____

#include <Windows.h>
#include "obj.h"
#include "Camera.h"
/*
Shader 类，模拟渲染管线
*/
class Shader
{
private:
    // 私有变量
    Obj* m_obj = nullptr;
    Eigen::Matrix4d m_projectionMatrix = Eigen::Matrix4d::Identity();
    Eigen::Matrix4d m_viewMatrix = Eigen::Matrix4d::Identity();
    Eigen::Matrix4d m_modelMatrix = Eigen::Matrix4d::Identity();
    Eigen::Matrix3d m_inverseMatrix = Eigen::Matrix3d::Identity();
    std::vector<Eigen::Vector4d> m_gl_vertices;
    std::vector<Eigen::Vector3d> m_calculate_vertices;
    std::vector<Eigen::Vector3d> m_calculate_normals;
    bool* m_flag = nullptr;
    double* m_zBuffer = nullptr;
    BYTE* m_frameBuffer = nullptr;
    int m_width = 0;
    int m_height = 0;

public:
    // 公有函数
    Shader(Obj* obj, int width, int height);
    ~Shader();

    BYTE* shading(Camera& camera, Eigen::Matrix4d modelMatrix = Eigen::Matrix4d::Identity());

private:
    // 私有函数
    void vertexShading();
    void trianglesShading();
    void rasterizationAndFragmentShading();
};

#endif // !____SHADER_H____