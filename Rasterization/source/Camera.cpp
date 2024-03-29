﻿
#include <cmath>

#include "../header/Camera.h"

Camera::Camera()
{

}

Camera::Camera(const Camera& _camera)
{
    m_position = _camera.m_position;
    m_lookat = _camera.m_lookat;
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
}

Camera::Camera(Point3 _eye, Point3 _lookat, GQYMath::vec3 _up, double _fovy, double _aspect, double _near_plane, double _far_plane)
{
    m_position = _eye;
    m_lookat = _lookat;
    m_z = normalized_vector(_eye - _lookat);
    m_x = normalized_vector(cross(_up, m_z));
    m_y = normalized_vector(cross(m_z, m_x));
    m_fovy = GQYMath::degree_to_radians(_fovy);
    m_near = _near_plane;
    m_far = _far_plane;
    m_aspect = _aspect;
    m_elevation_angle = std::atan(m_z.y / std::sqrt((m_z.x) * (m_z.x) + (m_z.z) * (m_z.z)));
    GQYMath::vec3 temp = normalized_vector(GQYMath::vec3(m_z.x, 0.0, m_z.z));
    double temp_angle = std::acos(dot(temp, GQYMath::vec3(1.0, 0.0, 0.0)));
    if (temp.z < 0.0)
    {
        m_yaw_angle = -temp_angle;
    }
    else
    {
        m_yaw_angle = temp_angle;
    }
}

Camera::~Camera()
{

}

void Camera::set_aspect(double _aspect)
{
    m_aspect = _aspect;
}

void Camera::change_fovy(double _step)
{
    m_fovy += GQYMath::degree_to_radians(_step);
    if (m_fovy > GQYMath::PI * 2.0 / 3.0)
    {
        m_fovy = GQYMath::PI * 2.0 / 3.0;
    }
    if (m_fovy < GQYMath::PI / 6.0)
    {
        m_fovy = GQYMath::PI / 6.0;
    }
}

void Camera::rotate(double _yaw_angle, double _elevation_angle)
{
    double distance = (m_lookat - m_position).length();
    m_yaw_angle += GQYMath::degree_to_radians(_yaw_angle);
    m_elevation_angle += GQYMath::degree_to_radians(_elevation_angle);
    if (m_elevation_angle > GQYMath::PI / 2.0)
    {
        m_elevation_angle = GQYMath::PI / 2.0;
    }
    if (m_elevation_angle < -GQYMath::PI / 2.0)
    {
        m_elevation_angle = -GQYMath::PI / 2.0;
    }
    GQYMath::vec3 front;
    front.x = std::cos(m_elevation_angle) * std::cos(m_yaw_angle);
    front.y = std::sin(m_elevation_angle);
    front.z = std::cos(m_elevation_angle) * std::sin(m_yaw_angle);
    m_z = normalized_vector(front);
    m_x = normalized_vector(cross(GQYMath::vec3(0.0, 1.0, 0.0), m_z));
    m_y = normalized_vector(cross(m_z, m_x));
    m_position = m_lookat + distance * m_z;
}