
#include <iostream>
#include <fstream>
#include <cmath>

#include "Obj.h"

Obj::Obj()
{

}

Obj::Obj(const Obj& obj)
{
    m_vs = obj.m_vs;
    m_vns = obj.m_vns;
    m_vts = obj.m_vts;
    m_meshs = obj.m_meshs;
    m_materials = obj.m_materials;
    m_relatingFaces = obj.m_relatingFaces;
}

Obj::Obj(std::string filePath)
{
    loadObj(filePath);
}

Obj::~Obj()
{

}

void Obj::loadObj(std::string filePath)
{
    std::ifstream objFile;
    std::string str, currentMaterial;
    objFile.open(filePath, std::ios::in);
    if (!objFile.is_open())
    {
        std::cout << ".obj 文件打开失败: " << filePath << std::endl;
        exit(-2);
    }

    while (objFile >> str)
    {
        if (str == "v")
        {
            double tempV[3];
            for (int i = 0; i < 3; i++)
            {
                objFile >> str;
                tempV[i] = std::stod(str);
            }
            m_vs.push_back(Eigen::Vector3d(tempV[0], tempV[1], tempV[2]));
        }
        else if (str == "vt")
        {
            double tempVt[2];
            for (int i = 0; i < 2; i++)
            {
                objFile >> str;
                tempVt[i] = std::stod(str);
            }
            while (tempVt[0] < 0.0)
            {
                tempVt[0] = tempVt[0] + 1.0;
            }
            while (tempVt[0] > 1.0)
            {
                tempVt[0] = tempVt[0] - 1.0;
            }
            while (tempVt[1] < 0.0)
            {
                tempVt[1] = tempVt[1] + 1.0;
            }
            while (tempVt[1] > 1.0)
            {
                tempVt[1] = tempVt[1] - 1.0;
            }
            m_vts.push_back(Eigen::Vector2d(tempVt[0], tempVt[1]));
        }
        else if (str == "vn")
        {
            double tempVn[3];
            for (int i = 0; i < 3; i++)
            {
                objFile >> str;
                tempVn[i] = std::stod(str);
            }
            m_vns.push_back(Eigen::Vector3d(tempVn[0], tempVn[1], tempVn[2]));
        }
        else if (str == "f")
        {
            Mesh tempMesh;
            for (int i = 0; i < 3; i++)
            {
                objFile >> str;
                size_t firstIndex = str.find('/');
                size_t secondIndex = str.find_last_of('/');
                tempMesh.m_vertexIndeices[i] = std::stoi(str.substr(0, firstIndex)) - 1;
                tempMesh.m_textureIndeices[i] = std::stoi(str.substr(firstIndex + 1, secondIndex - firstIndex - 1)) - 1;
                tempMesh.m_normalIndeices[i] = std::stoi(str.substr(secondIndex + 1, str.length() - secondIndex - 1)) - 1;
            }
            tempMesh.m_material = currentMaterial;
            m_meshs.push_back(tempMesh);
            int meshIndex = m_meshs.size() - 1;
            m_relatingFaces[m_meshs[meshIndex].m_vertexIndeices[0]].push_back(meshIndex);
            m_relatingFaces[m_meshs[meshIndex].m_vertexIndeices[1]].push_back(meshIndex);
            m_relatingFaces[m_meshs[meshIndex].m_vertexIndeices[2]].push_back(meshIndex);
        }
        else if (str == "mtllib")
        {
            objFile >> str;
            std::string mtlFilePath = filePath.substr(0, filePath.find_last_of('/')) + '/' + str;
            loadMtl(mtlFilePath);
        }
        else if (str == "usemtl")
        {
            objFile >> currentMaterial;
        }
    }
}

void Obj::loadMtl(std::string filePath)
{
    std::ifstream mtlFile;
    std::string str, currentMaterial;
    mtlFile.open(filePath, std::ios::in);
    if (!mtlFile.is_open())
    {
        std::cout << ".mtl 文件打开失败: " << filePath << std::endl;
        exit(-2);
    }

    while (mtlFile >> str)
    {
        if (str == "Ns")
        {
            mtlFile >> str;
            m_materials[currentMaterial].m_Ns = std::stod(str);
        }
        else if (str == "Ni")
        {
            mtlFile >> str;
            m_materials[currentMaterial].m_Ni = std::stod(str);
        }
        else if (str == "d")
        {
            mtlFile >> str;
            m_materials[currentMaterial].m_d = std::stod(str);
        }
        else if (str == "Tr")
        {
            mtlFile >> str;
            m_materials[currentMaterial].m_Tr = std::stod(str);
        }
        else if (str == "Tf")
        {
            double tempTf[3];
            for (int i = 0; i < 3; i++)
            {
                mtlFile >> str;
                tempTf[i] = std::stod(str);
            }
            m_materials[currentMaterial].m_Tf = Eigen::Vector3d(tempTf[0], tempTf[1], tempTf[2]);
        }
        else if (str == "Ka")
        {
            double tempKa[3];
            for (int i = 0; i < 3; i++)
            {
                mtlFile >> str;
                tempKa[i] = std::stod(str);
            }
            m_materials[currentMaterial].m_Ka = Eigen::Vector3d(tempKa[0], tempKa[1], tempKa[2]);
        }
        else if (str == "Kd")
        {
            double tempKd[3];
            for (int i = 0; i < 3; i++)
            {
                mtlFile >> str;
                tempKd[i] = std::stod(str);
            }
            m_materials[currentMaterial].m_Kd = Eigen::Vector3d(tempKd[0], tempKd[1], tempKd[2]);
        }
        else if (str == "Ks")
        {
            double tempKs[3];
            for (int i = 0; i < 3; i++)
            {
                mtlFile >> str;
                tempKs[i] = std::stod(str);
            }
            m_materials[currentMaterial].m_Ks = Eigen::Vector3d(tempKs[0], tempKs[1], tempKs[2]);
        }
        else if (str == "Ke")
        {
            double tempKe[3];
            for (int i = 0; i < 3; i++)
            {
                mtlFile >> str;
                tempKe[i] = std::stod(str);
            }
            m_materials[currentMaterial].m_Ke = Eigen::Vector3d(tempKe[0], tempKe[1], tempKe[2]);
        }
        else if (str == "map_Ka")
        {
            mtlFile >> str;
            std::string mapFilePath = filePath.substr(0, filePath.find_last_of('/')) + '/' + str;
            m_materials[currentMaterial].loadKa(mapFilePath);
        }
        else if (str == "map_Kd")
        {
            mtlFile >> str;
            std::string mapFilePath = filePath.substr(0, filePath.find_last_of('/')) + '/' + str;
            m_materials[currentMaterial].loadKd(mapFilePath);
        }
        else if (str == "newmtl")
        {
            mtlFile >> currentMaterial;
            m_materials[currentMaterial] = Material();
        }
    }
}