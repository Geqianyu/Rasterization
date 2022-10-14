#ifndef ____OBJ_H____
#define ____OBJ_H____

#include <Eigen/Dense>
#include <Eigen/Core>
#include <vector>
#include <map>
#include <string>

#include "Mesh.h"
#include "Material.h"

/*
Obj 类，用于加载模型获取模型相关的数据
*/
class Obj
{
public:
    // 公有变量
    std::vector<Eigen::Vector3d> m_vs;                        // 顶点
    std::vector<Eigen::Vector3d> m_vns;                       // 顶点法向量
    std::vector<Eigen::Vector2d> m_vts;                       // 顶点纹理坐标
    std::vector<Mesh> m_meshs;                                // 保存三角形的索引
    std::map<std::string, Material> m_materials;              // 材质
    std::map<int, std::vector<int>> m_relatingFaces;          // 保存与某一顶点相关的三角形
    Eigen::Vector3d m_center;                                 // 模型的中心

public:
    // 公有函数
    Obj();
    Obj(const Obj& obj);
    Obj(std::string filePath);
    ~Obj();

    void loadObj(std::string filePath);
    Eigen::Matrix4d rotate(double angle, Eigen::Vector3d normal);
    Eigen::Matrix4d translate(double step, Eigen::Vector3d direction);

private:
    // 私有函数
    void loadMtl(std::string filePath);
};

#endif // !____OBJ_H____

