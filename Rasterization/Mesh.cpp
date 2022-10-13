
#include "Mesh.h"

Mesh::Mesh()
{

}

Mesh::Mesh(const Mesh& mesh)
{
    for (int i = 0; i < 3; i++)
    {
        m_vertexIndeices[i] = mesh.m_vertexIndeices[i];
        m_normalIndeices[i] = mesh.m_normalIndeices[i];
        m_textureIndeices[i] = mesh.m_textureIndeices[i];
    }
    m_material = mesh.m_material;
}

Mesh::~Mesh()
{

}

// void Mesh::rorate(Eigen::Vector3f axis, float angle)
// {
//     Eigen::Matrix4f translate;
//     translate << 1.0f, 0.0f, 0.0f, -(_right + _left) / 2.0f,
//         0.0f, 1.0f, 0.0f, -(_top + _bottom) / 2.0f,
//         0.0f, 0.0f, 1.0f, -(_front + _back) / 2.0f,
//         0.0f, 0.0f, 0.0f, 1.0f;
//     Eigen::Matrix4f rorate;
//     float cosAngle = std::cosf(angle);
//     float _cosAngle = 1 - cosAngle;
//     float sinAngle = std::sinf(angle);
//     rorate << cosAngle + _cosAngle * axis.x() * axis.x(), _cosAngle* axis.x()* axis.y() - sinAngle * axis.z(), _cosAngle* axis.x()* axis.z() + sinAngle * axis.y(), 0.0f,
//         _cosAngle* axis.x()* axis.y() + sinAngle * axis.z(), cosAngle + _cosAngle * axis.y() * axis.y(), _cosAngle* axis.y()* axis.z() - sinAngle * axis.x(), 0.0f,
//         _cosAngle* axis.z()* axis.x() - sinAngle * axis.y(), _cosAngle* axis.y()* axis.z() + sinAngle * axis.x(), cosAngle + _cosAngle * axis.z() * axis.z(), 0.0f,
//         0.0f, 0.0f, 0.0f, 1.0f;
//     Eigen::Matrix4f _translate;
//     _translate << 1.0f, 0.0f, 0.0f, (_right + _left) / 2.0f,
//         0.0f, 1.0f, 0.0f, (_top + _bottom) / 2.0f,
//         0.0f, 0.0f, 1.0f, (_front + _back) / 2.0f,
//         0.0f, 0.0f, 0.0f, 1.0f;
//     size_t size = _vs.size();
//     for (size_t i = 0; i < size; i++)
//     {
//         _vs[i] = translate * _vs[i];
//         _vs[i] = rorate * _vs[i];
//         _vs[i] = _translate * _vs[i];
//     }
// }