#ifndef ____MESH_H____
#define ____MESH_H____

#include <Eigen/Dense>
#include <Eigen/Core>
#include <string>

/*
* Mesh类，顶点索引
*/
class Mesh
{
public:
    // 公有变量
    int m_vertexIndeices[3] = { 0, 0, 0 };                        // 顶点索引
    int m_normalIndeices[3] = { 0, 0, 0 };                        // 顶点法向量索引
    int m_textureIndeices[3] = { 0, 0, 0 };                       // 顶点纹理坐标索引
    std::string m_material = "";                                  // 材质名称

public:
    // 公有函数
    Mesh();
    Mesh(const Mesh& mesh);
    ~Mesh();
};

#endif // !____MESH_H____
