#include <cmath>
#include <omp.h>

#include "Shader.h"

Shader::Shader(Obj* _obj, int _width, int _height)
{
    m_obj = _obj;
    m_width = _width;
    m_height = _height;
    m_zBuffer = new double[_width * _height];
    m_frameBuffer = new BYTE[3 * _width * _height];
    m_gl_vertices = std::vector<Point4>(_obj->m_vs.size());
}

Shader::~Shader()
{
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

BYTE* Shader::shading(Camera& camera, Light& light, GQYMath::mat4& _translate)
{
    std::fill(m_zBuffer, m_zBuffer + m_width * m_height, -FLT_MAX);
    std::fill(m_frameBuffer, m_frameBuffer + 3 * m_width * m_height, 0X00);
    m_matrix = _translate * camera.projection_matrix() * camera.view_matrix();
    m_camera_position = camera.position();
    m_light_ambient = light.m_ambient;
    m_light_direction = normalized_vector(light.m_direction);
    m_light_emission = light.m_emission;

    // 顶点处理
    vertex_shading();

    // 三角形处理
    triangles_shading();

    return m_frameBuffer;
}

void Shader::vertex_shading()
{
    int vertices_size = static_cast<int>(m_obj->m_vs.size());
#pragma omp parallel for
    for (int i = 0; i < vertices_size; i++)
    {
        m_gl_vertices[i] = m_matrix * m_obj->m_vs[i];
    }
}

void Shader::triangles_shading()
{
    // 背面剔除
    int triangles_size = static_cast<int>(m_obj->m_meshs.size());
#pragma omp parallel for
    for (int i = 0; i < triangles_size; i++)
    {
        Point3 first_point = m_obj->m_vs[m_obj->m_meshs[i].m_vertex_indeices[0]];
        Point3 second_point = m_obj->m_vs[m_obj->m_meshs[i].m_vertex_indeices[1]];
        Point3 third_point = m_obj->m_vs[m_obj->m_meshs[i].m_vertex_indeices[2]];
        GQYMath::vec3 d = m_camera_position - first_point;
        GQYMath::vec3 first_edge = second_point - first_point;
        GQYMath::vec3 second_edge = third_point - first_point;
        GQYMath::vec3 r = cross(first_edge, second_edge);
        if (dot(r, d) > 0.0)
        {
            // 光栅化
            rasterization(i);
        }
    }
}

void Shader::rasterization(int& _index)
{
    Point4 first_point = m_gl_vertices[m_obj->m_meshs[_index].m_vertex_indeices[0]];
    Point4 second_point = m_gl_vertices[m_obj->m_meshs[_index].m_vertex_indeices[1]];
    Point4 third_point = m_gl_vertices[m_obj->m_meshs[_index].m_vertex_indeices[2]];
    Point3 A((first_point.x / first_point.w + 1.0) / 2.0 * m_width, (first_point.y / first_point.w + 1.0) / 2.0 * m_height, 0.0);
    Point3 B((second_point.x / second_point.w + 1.0) / 2.0 * m_width, (second_point.y / second_point.w + 1.0) / 2.0 * m_height, 0.0);
    Point3 C((third_point.x / third_point.w + 1.0) / 2.0 * m_width, (third_point.y / third_point.w + 1.0) / 2.0 * m_height, 0.0);
    GQYMath::vec3 AB = B - A;
    GQYMath::vec3 BC = C - B;
    GQYMath::vec3 CA = A - C;
    int top = min(m_height - 1, (int)(max(A.y, max(B.y, C.y))));
    int bottom = max(0, (int)(min(A.y, min(B.y, C.y))));
    int right = min(m_width - 1, (int)(max(A.x, max(B.x, C.x))));
    int left = max(0, (int)(min(A.x, min(B.x, C.x))));
#pragma omp parallel for
    for (int j = bottom; j <= top; j++)
    {
        for (int k = left; k <= right; k++)
        {
            Point3 P((double)k + 0.5, (double)j + 0.5, 0.0);
            GQYMath::vec3 AP = P - A;
            GQYMath::vec3 BP = P - B;
            GQYMath::vec3 CP = P - C;
            GQYMath::vec3 AB_cross_AP = cross(AB, AP);
            GQYMath::vec3 BC_cross_BP = cross(BC, BP);
            GQYMath::vec3 CA_cross_CP = cross(CA, CP);
            if (AB_cross_AP.z * BC_cross_BP.z > 0.0 && AB_cross_AP.z * CA_cross_CP.z > 0.0 && BC_cross_BP.z * CA_cross_CP.z > 0.0)
            {
                double alpha = AB_cross_AP.length();
                double beta = BC_cross_BP.length();
                double gama = CA_cross_CP.length();
                double sum = alpha + beta + gama;
                double first_rate = beta / sum;
                double second_rate = gama / sum;
                double third_rate = alpha / sum;
                setpixel(first_rate, second_rate, third_rate, _index, k, j);
            }
        }
    }
}

void Shader::setpixel(double& _alpha, double& _beta, double& _gama, int& _index, int& _x_position, int& _y_position)
{
    double fragment_depth = _alpha * m_gl_vertices[m_obj->m_meshs[_index].m_vertex_indeices[0]].z + _beta * m_gl_vertices[m_obj->m_meshs[_index].m_vertex_indeices[1]].z + _gama * m_gl_vertices[m_obj->m_meshs[_index].m_vertex_indeices[2]].z;
    if (fragment_depth > m_zBuffer[_y_position * m_width + _x_position])
    {
        m_zBuffer[_y_position * m_width + _x_position] = fragment_depth;
        Point3 fragment_position = _alpha * m_obj->m_vs[m_obj->m_meshs[_index].m_vertex_indeices[0]] + _beta * m_obj->m_vs[m_obj->m_meshs[_index].m_vertex_indeices[1]] + _gama * m_obj->m_vs[m_obj->m_meshs[_index].m_vertex_indeices[2]];
        GQYMath::vec3 fragment_normal = _alpha * m_obj->m_vns[m_obj->m_meshs[_index].m_normal_indeices[0]] + _beta * m_obj->m_vns[m_obj->m_meshs[_index].m_normal_indeices[1]] + _gama * m_obj->m_vns[m_obj->m_meshs[_index].m_normal_indeices[2]];
        GQYMath::vec2 fragment_texture = _alpha * m_obj->m_vts[m_obj->m_meshs[_index].m_texture_indeices[0]] + _beta * m_obj->m_vts[m_obj->m_meshs[_index].m_texture_indeices[1]] + _gama * m_obj->m_vts[m_obj->m_meshs[_index].m_texture_indeices[2]];
        Color color = fragment_shader(fragment_position, fragment_normal, fragment_texture, m_obj->m_meshs[_index].m_material);
        m_frameBuffer[3 * _y_position * m_width + 3 * _x_position] = (BYTE)(color.b * 255);
        m_frameBuffer[3 * _y_position * m_width + 3 * _x_position + 1] = (BYTE)(color.g * 255);
        m_frameBuffer[3 * _y_position * m_width + 3 * _x_position + 2] = (BYTE)(color.r * 255);
    }
}

Color Shader::fragment_shader(Point3& _fragment_position, GQYMath::vec3& _fragment_normal, GQYMath::vec2& _fragment_texture, std::string& _material)
{
    GQYMath::vec3 normal = normalized_vector(_fragment_normal);
    Color ambient_color = m_light_ambient * m_obj->m_materials[_material].Ka(_fragment_texture);
    double diffuse = max(0.0, dot(normal, -m_light_direction));
    Color diffuse_color = diffuse * m_light_emission * m_obj->m_materials[_material].Kd(_fragment_texture);
    GQYMath::vec3 half_vector = normalized_vector(m_camera_position - _fragment_position);
    half_vector = normalized_vector(half_vector - m_light_direction);
    double specular = std::pow(max(0.0, dot(half_vector, normal)), m_obj->m_materials[_material].m_Ns);
    Color specular_color = specular * m_light_emission * m_obj->m_materials[_material].m_Ks;
    return (ambient_color + diffuse_color + specular_color);
}