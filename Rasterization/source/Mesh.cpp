
#include "../header/Mesh.h"

Mesh::Mesh()
{

}

Mesh::Mesh(const Mesh& _mesh)
{
    for (int i = 0; i < 3; i++)
    {
        m_vertex_indeices[i] = _mesh.m_vertex_indeices[i];
        m_normal_indeices[i] = _mesh.m_normal_indeices[i];
        m_texture_indeices[i] = _mesh.m_texture_indeices[i];
    }
    m_material = _mesh.m_material;
}

Mesh::~Mesh()
{

}