#ifndef _GQY_MESH_H_
#define _GQY_MESH_H_

#include <string>

/*
* Mesh类，顶点索引
*/
class Mesh
{
public:
    // 公有变量
    int m_vertex_indeices[3] = { 0, 0, 0 };                        // 顶点索引
    int m_normal_indeices[3] = { 0, 0, 0 };                        // 顶点法向量索引
    int m_texture_indeices[3] = { 0, 0, 0 };                       // 顶点纹理坐标索引
    std::string m_material = "";                                   // 材质名称

public:
    // 公有函数
    Mesh();
    Mesh(const Mesh& _mesh);
    ~Mesh();
};

#endif // !_GQY_MESH_H_
