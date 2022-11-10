#ifndef _GQY_OBJ_H_
#define _GQY_OBJ_H_

#include <vector>
#include <map>
#include <string>

#include "../header/Math.h"
#include "../header/Mesh.h"
#include "../header/Material.h"

/*
Obj 类，用于加载模型获取模型相关的数据
*/
class Obj
{
public:
    // 公有变量
    std::vector<Point3> m_vs;                               // 顶点
    std::vector<GQYMath::vec3> m_vns;                       // 顶点法向量
    std::vector<GQYMath::vec2> m_vts;                       // 顶点纹理坐标
    std::vector<Mesh> m_meshs;                              // 保存三角形的索引
    std::map<std::string, Material> m_materials;            // 材质

public:
    // 公有函数
    Obj();
    Obj(const Obj& _obj);
    Obj(std::string _file_path);
    ~Obj();

    void load_obj(std::string _file_path);

private:
    // 私有函数
    void load_mtl(std::string _file_path);
};

#endif // !_GQY_OBJ_H_

