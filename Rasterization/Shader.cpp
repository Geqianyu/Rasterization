#include <iostream>
#include <cmath>
#include <omp.h>

#include "Shader.h"

Shader::Shader(Obj* obj, int width, int height)
{
    m_obj = obj;
    m_flag = new bool[obj->m_meshs.size()];
    m_width = width;
    m_height = height;
    m_zBuffer = new double[width * height];
    m_frameBuffer = new BYTE[3 * width * height];
    m_gl_vertices = std::vector<Eigen::Vector4d>(obj->m_vs.size());
    m_calculate_vertices = std::vector<Eigen::Vector3d>(obj->m_vs.size());
    m_calculate_normals = std::vector<Eigen::Vector3d>(obj->m_vns.size());
}

Shader::~Shader()
{
    if (m_flag != nullptr)
    {
        delete[] m_flag;
        m_flag = nullptr;
    }
    if (m_zBuffer != nullptr)
    {
        delete[] m_zBuffer;
        m_zBuffer = nullptr;
    }
    if (m_frameBuffer != nullptr)
    {
        delete[] m_frameBuffer;
        m_frameBuffer = nullptr;
    }
}

BYTE* Shader::shading(Camera& camera, Eigen::Matrix4d modelMatrix)
{
    std::fill(m_flag, m_flag + m_obj->m_meshs.size(), true);
    std::fill(m_zBuffer, m_zBuffer + m_width * m_height, -FLT_MAX);
    std::fill(m_frameBuffer, m_frameBuffer + 3 * m_width * m_height, 0X00);
    m_projectionMatrix = camera.projectionMatrix();
    m_viewMatrix = camera.viewMatrix();
    m_modelMatrix = modelMatrix;
    Eigen::Matrix4d tempInverse = m_modelMatrix.inverse().transpose();
    m_inverseMatrix << tempInverse(0, 0), tempInverse(0, 1), tempInverse(0, 2)
        , tempInverse(1, 0), tempInverse(1, 1), tempInverse(1, 2)
        , tempInverse(2, 0), tempInverse(2, 1), tempInverse(2, 2);

    // 顶点处理
    vertexShading();

    // 三角形处理
    trianglesShading();

    // 光栅化和片段处理
    rasterizationAndFragmentShading();

    return m_frameBuffer;
}

void Shader::vertexShading()
{
    int verticesSize = m_obj->m_vs.size();
#pragma omp parallel for
    for (int i = 0; i < verticesSize; i++)
    {
        Eigen::Vector4d temp = m_modelMatrix * Eigen::Vector4d(m_obj->m_vs[i].x(), m_obj->m_vs[i].y(), m_obj->m_vs[i].z(), 1.0);
        m_calculate_vertices[i] = Eigen::Vector3d(temp.x(), temp.y(), temp.z());
        m_gl_vertices[i] = (m_projectionMatrix * m_viewMatrix * temp);
    }

    int normalSize = m_obj->m_vns.size();
#pragma omp parallel for
    for (int i = 0; i < normalSize; i++)
    {
        m_calculate_normals[i] = m_inverseMatrix * m_obj->m_vns[i];
    }
}

void Shader::trianglesShading()
{
    int verticesSize = m_obj->m_vs.size();
#pragma omp parallel for
    for (int i = 0; i < verticesSize; i++)
    {
        if (m_gl_vertices[i].x() / m_gl_vertices[i].w() > 1.000001f || m_gl_vertices[i].x() / m_gl_vertices[i].w() < -1.000001f
            || m_gl_vertices[i].y() / m_gl_vertices[i].w() > 1.000001f || m_gl_vertices[i].y() / m_gl_vertices[i].w() < -1.000001f
            || m_gl_vertices[i].z() / m_gl_vertices[i].w() > 1.000001f || m_gl_vertices[i].z() / m_gl_vertices[i].w() < -1.000001f)
        {
            size_t len = m_obj->m_relatingFaces[i].size();
            for (size_t j = 0; j < len; j++)
            {
                m_flag[m_obj->m_relatingFaces[i][j]] = false;
            }
        }
    }

    // int trianglesSize = m_obj->m_meshs.size();
    // #pragma omp parallel for
    // for (int i = 0; i < trianglesSize; i++)
    // {
    //     if (m_flag[i])
    //     {
    //         Eigen::Vector3d firstPoint = m_calculate_vertices[m_obj->m_meshs[i].m_vertexIndeices[0]];
    //         Eigen::Vector3d secondPoint = m_calculate_vertices[m_obj->m_meshs[i].m_vertexIndeices[1]];
    //         Eigen::Vector3d thirdPoint = m_calculate_vertices[m_obj->m_meshs[i].m_vertexIndeices[2]];
    //         Eigen::Vector3d firstEdge = secondPoint - firstPoint;
    //         Eigen::Vector3d secondEdge = thirdPoint - firstPoint;
    //         Eigen::Vector3d r = firstEdge.cross(secondEdge);
    //         if (r.z() < 0.0)
    //         {
    //             m_flag[i] = false;
    //         }
    //     }
    // }
}

void Shader::rasterizationAndFragmentShading()
{
    size_t trianglesSize = m_obj->m_meshs.size();
    for (size_t i = 0; i < trianglesSize; i++)
    {
        if (m_flag[i])
        {
            Eigen::Vector4d firstPoint = m_gl_vertices[m_obj->m_meshs[i].m_vertexIndeices[0]];
            Eigen::Vector4d secondPoint = m_gl_vertices[m_obj->m_meshs[i].m_vertexIndeices[1]];
            Eigen::Vector4d thirdPoint = m_gl_vertices[m_obj->m_meshs[i].m_vertexIndeices[2]];
            Eigen::Vector3d A((firstPoint.x() / firstPoint.w() + 1.0) / 2.0 * m_width, (firstPoint.y() / firstPoint.w() + 1.0) / 2.0 * m_height, 0.0);
            Eigen::Vector3d B((secondPoint.x() / secondPoint.w() + 1.0) / 2.0 * m_width, (secondPoint.y() / secondPoint.w() + 1.0) / 2.0 * m_height, 0.0);
            Eigen::Vector3d C((thirdPoint.x() / thirdPoint.w() + 1.0) / 2.0 * m_width, (thirdPoint.y() / thirdPoint.w() + 1.0) / 2.0 * m_height, 0.0);
            Eigen::Vector3d AB = B - A;
            Eigen::Vector3d BC = C - B;
            Eigen::Vector3d CA = A - C;
            int top = (int)(max(A.y(), max(B.y(), C.y())));
            int bottom = (int)(min(A.y(), min(B.y(), C.y())));
            int right = (int)(max(A.x(), max(B.x(), C.x())));
            int left = (int)(min(A.x(), min(B.x(), C.x())));
#pragma omp parallel for
            for (int j = bottom; j <= top; j++)
            {
                for (int k = left; k <= right; k++)
                {
                    Eigen::Vector3d P((double)k + 0.5, (double)j + 0.5, 0.0);
                    Eigen::Vector3d AP = P - A;
                    Eigen::Vector3d BP = P - B;
                    Eigen::Vector3d CP = P - C;
                    Eigen::Vector3d ABcrossAP = AB.cross(AP);
                    Eigen::Vector3d BCcrossBP = BC.cross(BP);
                    Eigen::Vector3d CAcrossCP = CA.cross(CP);
                    if (ABcrossAP.z() * BCcrossBP.z() > 0.0f && ABcrossAP.z() * CAcrossCP.z() > 0.0f && BCcrossBP.z() * CAcrossCP.z() > 0.0f)
                    {
                        double alpha = ABcrossAP.norm();
                        double beta = BCcrossBP.norm();
                        double gama = CAcrossCP.norm();
                        double sum = alpha + beta + gama;
                        double firstRate = beta / sum;
                        double secondRate = gama / sum;
                        double thirdRate = alpha / sum;
                        Eigen::Vector3d fragmentPosition = firstRate * m_calculate_vertices[m_obj->m_meshs[i].m_vertexIndeices[0]] + secondRate * m_calculate_vertices[m_obj->m_meshs[i].m_vertexIndeices[1]] + thirdRate * m_calculate_vertices[m_obj->m_meshs[i].m_vertexIndeices[2]];
                        if (fragmentPosition.z() > m_zBuffer[j * m_width + k])
                        {
                            Eigen::Vector3d fragmentNormal = firstRate * m_calculate_normals[m_obj->m_meshs[i].m_normalIndeices[0]] + secondRate * m_calculate_normals[m_obj->m_meshs[i].m_normalIndeices[1]] + thirdRate * m_calculate_normals[m_obj->m_meshs[i].m_normalIndeices[2]];
                            Eigen::Vector2d fragmentTexture = firstRate * m_obj->m_vts[m_obj->m_meshs[i].m_textureIndeices[0]] + secondRate * m_obj->m_vts[m_obj->m_meshs[i].m_textureIndeices[1]] + thirdRate * m_obj->m_vts[m_obj->m_meshs[i].m_textureIndeices[2]];
                            Eigen::Vector3d Kd = m_obj->m_materials[m_obj->m_meshs[i].m_material].Kd(fragmentTexture);
                            m_zBuffer[j * m_width + k] = fragmentPosition.z();
                            m_frameBuffer[3 * j * m_width + 3 * k] = (BYTE)(Kd.z() * 255);
                            m_frameBuffer[3 * j * m_width + 3 * k + 1] = (BYTE)(Kd.y() * 255);
                            m_frameBuffer[3 * j * m_width + 3 * k + 2] = (BYTE)(Kd.x() * 255);
                        }
                    }
                }
            }
        }
    }
}