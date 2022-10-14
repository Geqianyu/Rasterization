#ifndef ____SHADER_H____
#define ____SHADER_H____

#include <Windows.h>
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
    Eigen::Matrix4d m_projectionMatrix = Eigen::Matrix4d::Identity();
    Eigen::Matrix4d m_viewMatrix = Eigen::Matrix4d::Identity();
    Eigen::Matrix4d m_modelMatrix = Eigen::Matrix4d::Identity();
    Eigen::Matrix3d m_inverseMatrix = Eigen::Matrix3d::Identity();
    Eigen::Vector3d m_lightAmbient;
    Eigen::Vector3d m_lightDirection;
    Eigen::Vector3d m_lightEmission;
    Eigen::Vector3d m_cameraPosition;
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

    BYTE* shading(Camera& camera, Light& light, Eigen::Matrix4d modelMatrix = Eigen::Matrix4d::Identity());

private:
    // 私有函数
    void vertexShading();
    void trianglesShading();
    void rasterizationAndFragmentShading();
    Eigen::Vector3d fragmentShader(Eigen::Vector3d fragmentPosition, Eigen::Vector3d fragmentNormal, Eigen::Vector2d fragmentTexture, std::string material);
};

#endif // !____SHADER_H____