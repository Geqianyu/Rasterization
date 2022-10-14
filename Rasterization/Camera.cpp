
#include <cmath>

#include "Camera.h"

const double PI = std::asin(1.0) * 2.0;

Camera::Camera()
{

}

Camera::Camera(const Camera& camera)
{
    m_position = camera.m_position;
    m_z = camera.m_z;
    m_y = camera.m_y;
    m_x = camera.m_x;
    m_viewMatrix = camera.m_viewMatrix;
    m_projectionMatrix = camera.m_projectionMatrix;
    m_fovy = camera.m_fovy;
    m_aspect = camera.m_aspect;
    m_near = camera.m_near;
    m_far = camera.m_far;
}

Camera::Camera(Eigen::Vector3d eye, Eigen::Vector3d lookat, Eigen::Vector3d up, double fovy, double aspect, double nearPlane, double farPlane)
{
    m_position = eye;
    m_z = eye - lookat;
    m_z.normalize();
    m_y = up;
    m_y.normalize();
    m_x = m_y.cross(m_z);
    m_x.normalize();
    m_fovy = fovy * PI / 180.0;
    m_near = nearPlane;
    m_far = farPlane;
    m_aspect = aspect;
    generateViewMatrix();
    generateProjectionMatrix();
}

Camera::~Camera()
{

}

void Camera::setAspect(double aspect)
{
    m_aspect = aspect;
    generateViewMatrix();
    generateProjectionMatrix();
}

void Camera::changeFovy(double step)
{
    m_fovy = m_fovy + step * PI / 180.0;
    generateViewMatrix();
    generateProjectionMatrix();
}

Eigen::Matrix4d Camera::viewMatrix()
{
    return m_viewMatrix;
}

Eigen::Matrix4d Camera::projectionMatrix()
{
    return m_projectionMatrix;
}

Eigen::Vector3d Camera::XAxis()
{
    return m_x;
}

Eigen::Vector3d Camera::YAxis()
{
    return m_y;
}

Eigen::Vector3d Camera::ZAxis()
{
    return m_z;
}

Eigen::Vector3d Camera::position()
{
    return m_position;
}

void Camera::generateViewMatrix()
{
    Eigen::Matrix4d m1;
    Eigen::Matrix4d m2;
    m1 << m_x.x(), m_x.y(), m_x.z(), 0.0
        , m_y.x(), m_y.y(), m_y.z(), 0.0
        , m_z.x(), m_z.y(), m_z.z(), 0.0
        , 0.0, 0.0, 0.0, 1.0;
    m2 << 1.0, 0.0, 0.0, -m_position.x()
        , 0.0, 1.0, 0.0, -m_position.y()
        , 0.0, 0.0, 1.0, -m_position.z()
        , 0.0, 0.0, 0.0, 1.0;
    m_viewMatrix = m1 * m2;
}

void Camera::generateProjectionMatrix()
{
    double tanHalfFovy = std::tan(m_fovy / 2.0);
    m_projectionMatrix << 1.0 / m_aspect / tanHalfFovy, 0.0, 0.0, 0.0
        , 0.0, 1.0 / tanHalfFovy, 0.0, 0.0
        , 0.0, 0.0, (m_near + m_far) / (m_far - m_near), 2.0 * m_near * m_far / (m_far - m_near)
        , 0.0, 0.0, -1.0, 0.0;
}