#include <fstream>
#include <cmath>

#include "../header/Obj.h"

Obj::Obj()
{

}

Obj::Obj(const Obj& _obj)
{
    m_vs = _obj.m_vs;
    m_vns = _obj.m_vns;
    m_vts = _obj.m_vts;
    m_meshs = _obj.m_meshs;
    m_materials = _obj.m_materials;
}

Obj::Obj(std::string _file_path)
{
    load_obj(_file_path);
}

Obj::~Obj()
{

}

void Obj::load_obj(std::string _file_path)
{
    std::ifstream obj_file;
    std::string str, current_material;
    obj_file.open(_file_path, std::ios::in);
    if (!obj_file.is_open())
    {
        exit(-2);
    }

    while (obj_file >> str)
    {
        if (str == "v")
        {
            double temp_v[3];
            for (int i = 0; i < 3; i++)
            {
                obj_file >> str;
                temp_v[i] = std::stod(str);
            }
            m_vs.push_back(Point3(temp_v[0], temp_v[1], temp_v[2]));
        }
        else if (str == "vt")
        {
            double temp_vt[2];
            for (int i = 0; i < 2; i++)
            {
                obj_file >> str;
                temp_vt[i] = std::stod(str);
                while (temp_vt[i] < 0.0)
                {
                    temp_vt[i] = temp_vt[i] + 1.0;
                }
                while (temp_vt[i] > 1.0)
                {
                    temp_vt[i] = temp_vt[i] - 1.0;
                }
            }
            m_vts.push_back(GQYMath::vec2(temp_vt[0], temp_vt[1]));
        }
        else if (str == "vn")
        {
            double temp_vn[3];
            for (int i = 0; i < 3; i++)
            {
                obj_file >> str;
                temp_vn[i] = std::stod(str);
            }
            m_vns.push_back(GQYMath::vec3(temp_vn[0], temp_vn[1], temp_vn[2]));
        }
        else if (str == "f")
        {
            Mesh temp_mesh;
            for (int i = 0; i < 3; i++)
            {
                obj_file >> str;
                size_t first_index = str.find('/');
                size_t second_index = str.find_last_of('/');
                temp_mesh.m_vertex_indeices[i] = std::stoi(str.substr(0, first_index)) - 1;
                temp_mesh.m_texture_indeices[i] = std::stoi(str.substr(first_index + 1, second_index - first_index - 1)) - 1;
                temp_mesh.m_normal_indeices[i] = std::stoi(str.substr(second_index + 1, str.length() - second_index - 1)) - 1;
            }
            temp_mesh.m_material = current_material;
            m_meshs.push_back(temp_mesh);
        }
        else if (str == "mtllib")
        {
            obj_file >> str;
            std::string mtl_file_path = _file_path.substr(0, _file_path.find_last_of('/')) + '/' + str;
            load_mtl(mtl_file_path);
        }
        else if (str == "usemtl")
        {
            obj_file >> current_material;
        }
    }
}

void Obj::load_mtl(std::string _file_path)
{
    std::ifstream mtl_file;
    std::string str, current_material;
    mtl_file.open(_file_path, std::ios::in);
    if (!mtl_file.is_open())
    {
        exit(-2);
    }

    while (mtl_file >> str)
    {
        if (str == "Ns")
        {
            mtl_file >> str;
            m_materials[current_material].m_Ns = std::stod(str);
        }
        else if (str == "Ni")
        {
            mtl_file >> str;
            m_materials[current_material].m_Ni = std::stod(str);
        }
        else if (str == "Ka")
        {
            double temp_Ka[3];
            for (int i = 0; i < 3; i++)
            {
                mtl_file >> str;
                temp_Ka[i] = std::stod(str);
            }
            m_materials[current_material].m_Ka = GQYMath::vec3(temp_Ka[0], temp_Ka[1], temp_Ka[2]);
        }
        else if (str == "Kd")
        {
            double temp_Kd[3];
            for (int i = 0; i < 3; i++)
            {
                mtl_file >> str;
                temp_Kd[i] = std::stod(str);
            }
            m_materials[current_material].m_Kd = GQYMath::vec3(temp_Kd[0], temp_Kd[1], temp_Kd[2]);
        }
        else if (str == "Ks")
        {
            double temp_Ks[3];
            for (int i = 0; i < 3; i++)
            {
                mtl_file >> str;
                temp_Ks[i] = std::stod(str);
            }
            m_materials[current_material].m_Ks = GQYMath::vec3(temp_Ks[0], temp_Ks[1], temp_Ks[2]);
        }
        else if (str == "Ke")
        {
            double temp_Ke[3];
            for (int i = 0; i < 3; i++)
            {
                mtl_file >> str;
                temp_Ke[i] = std::stod(str);
            }
            m_materials[current_material].m_Ke = GQYMath::vec3(temp_Ke[0], temp_Ke[1], temp_Ke[2]);
        }
        else if (str == "map_Ka")
        {
            mtl_file >> str;
            std::string map_file_path = _file_path.substr(0, _file_path.find_last_of('/')) + '/' + str;
            m_materials[current_material].loadKa(map_file_path);
        }
        else if (str == "map_Kd")
        {
            mtl_file >> str;
            std::string map_file_path = _file_path.substr(0, _file_path.find_last_of('/')) + '/' + str;
            m_materials[current_material].loadKd(map_file_path);
        }
        else if (str == "newmtl")
        {
            mtl_file >> current_material;
            m_materials[current_material] = Material();
        }
    }
}