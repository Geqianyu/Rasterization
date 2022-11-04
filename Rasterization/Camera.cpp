
#include <cmath>

#include "Camera.h"

const double PI = std::asin(1.0) * 2.0;

Camera::Camera()
{

}

Camera::Camera(const Camera& _camera)
{
    m_position = _camera.m_position;
    m_z = _camera.m_z;
    m_y = _camera.m_y;
    m_x = _camera.m_x;
    m_view_matrix = _camera.m_view_matrix;
    m_projection_matrix = _camera.m_projection_matrix;
    m_fovy = _camera.m_fovy;
    m_aspect = _camera.m_aspect;
    m_near = _camera.m_near;
    m_far = _camera.m_far;
    m_elevation_angle = _camera.m_elevation_angle;
    m_yaw_angle = _camera.m_yaw_angle;
    m_first_mouse = _camera.m_first_mouse;
    m_last_x = _camera.m_last_x;
    m_last_y = _camera.m_last_y;
}

Camera::Camera(Point3 _eye, Point3 _lookat, GQYMath::vec3 _up, double _fovy, double _aspect, double _near_plane, double _far_plane)
{
    m_position = _eye;
    m_z = normalized_vector(_eye - _lookat);
    m_x = normalized_vector(cross(_up, m_z));
    m_y = normalized_vector(cross(m_z, m_x));
    m_fovy = _fovy * PI / 180.0;
    m_near = _near_plane;
    m_far = _far_plane;
    m_aspect = _aspect;
    m_elevation_angle = 180.0 / PI * std::atanf(-m_z.y / std::sqrtf((-m_z.x) * (-m_z.x) + (-m_z.z) * (-m_z.z)));
    GQYMath::vec3 temp = normalized_vector(GQYMath::vec3(-m_z.x, 0.0f, -m_z.z));
    float temp_angle = 180.0f / PI * std::acosf(dot(temp, GQYMath::vec3(1.0f, 0.0f, 0.0f)));
    if (temp.z < 0.0f)
    {
        m_yaw_angle = -temp_angle;
    }
    else
    {
        m_yaw_angle = temp_angle;
    }
    generate_view_matrix();
    generate_projection_matrix();
}

Camera::~Camera()
{

}

void Camera::set_aspect(double _aspect)
{
    m_aspect = _aspect;
    generate_projection_matrix();
}

void Camera::change_fovy(double _step)
{
    m_fovy = m_fovy + _step * PI / 180.0;
    if (m_fovy > PI / 2.0)
    {
        m_fovy = PI / 2.0;
    }
    if (m_fovy < 0.0)
    {
        m_fovy = 0.0;
    }
    generate_projection_matrix();
}

void Camera::move(MOVE_DIRECTION _move_direction)
{
    switch (_move_direction)
    {
    case MOVE_DIRECTION::FRONT:
        m_position -= m_z;
        break;
    case MOVE_DIRECTION::BACK:
        m_position += m_z;
        break;
    case MOVE_DIRECTION::LEFT:
        m_position -= m_x;
        break;
    case MOVE_DIRECTION::RIGHT:
        m_position += m_x;
        break;
    default:
        break;
    }
    generate_view_matrix();
}

void Camera::change_direction(double _position_x, double _position_y)
{
    if (m_first_mouse)
    {
        m_last_x = _position_x;
        m_last_y = _position_y;
        m_first_mouse = false;
    }

    double offset_x = _position_x - m_last_x;
    double offset_y = m_last_y - _position_y; // 注意这里是相反的，因为y坐标是从底部往顶部依次增大的
    m_last_x = _position_x;
    m_last_y = _position_y;

    double sensitivity = 0.05;
    offset_x *= sensitivity;
    offset_y *= sensitivity;

    m_yaw_angle += offset_x;
    m_elevation_angle += offset_y;
    if (m_elevation_angle > 89.0f)
    {
        m_elevation_angle = 89.0f;
    }
    if (m_elevation_angle < -89.0f)
    {
        m_elevation_angle = -89.0f;
    }

    GQYMath::vec3 front;
    front.x = std::cos(m_elevation_angle * PI / 180.0) * std::cos(m_yaw_angle * PI / 180.0);
    front.y = std::sin(m_elevation_angle * PI / 180.0);
    front.z = std::cos(m_elevation_angle * PI / 180.0) * std::sin(m_yaw_angle * PI / 180.0);
    m_z = -normalized_vector(front);
    m_x = normalized_vector(cross(GQYMath::vec3(0.0, 1.0, 0.0), m_z));
    m_y = normalized_vector(cross(m_z, m_x));
    generate_view_matrix();
}