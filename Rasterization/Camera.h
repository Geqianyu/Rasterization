#ifndef _GQY_CAMERA_H_
#define _GQY_CAMERA_H_

#include "Math.h"

enum class MOVE_DIRECTION
{
    FRONT = 0,
    BACK,
    LEFT,
    RIGHT
};

/*
* Camera类，保存相机相关信息
*/
class Camera
{
private:
    // 变量
    Point3 m_position;                  // 相机坐标
    GQYMath::vec3 m_x;                  // 右方向
    GQYMath::vec3 m_z;                  // 看向的反方向
    GQYMath::vec3 m_y;                  // 上方向
    GQYMath::mat4 m_view_matrix;        // 视坐标变换矩阵
    GQYMath::mat4 m_projection_matrix;  // 投影矩阵
    double m_fovy = 90.0;               // 角度
    double m_aspect = 1.0;              // 高度 / 宽度
    double m_near = 1.0;                // 近平面
    double m_far = 10.0;                // 远平面
    double m_elevation_angle = 0.0;     // 仰角
    double m_yaw_angle = -90.0;         // 偏航角
    bool m_first_mouse = true;          // 鼠标第一次进入窗口的标记
    double m_last_x = 0.0;              // 鼠标上一次停留的X位置
    double m_last_y = 0.0;              // 鼠标上一次停留的Y位置

public:
    // 公有函数
    Camera();
    Camera(const Camera& _camera);
    Camera(Point3 _eye, Point3 _lookat, GQYMath::vec3 _up, double _fovy, double _aspect, double _near_plane, double _far_plane);
    ~Camera();
    void set_aspect(double _aspect);
    void change_fovy(double _step);
    void move(MOVE_DIRECTION _move_direction);
    void change_direction(double _position_x, double _position_y);

    inline GQYMath::mat4 view_matrix()
    {
        return m_view_matrix;
    }

    inline GQYMath::mat4 projection_matrix()
    {
        return m_projection_matrix;
    }

    inline Point3 position()
    {
        return m_position;
    }

private:
    // 私有函数
    inline void generate_view_matrix()
    {
        GQYMath::mat4 m1(
            m_x.x, m_x.y, m_x.z, 0.0
            , m_y.x, m_y.y, m_y.z, 0.0
            , m_z.x, m_z.y, m_z.z, 0.0
            , 0.0, 0.0, 0.0, 1.0);
        GQYMath::mat4 m2(
            1.0, 0.0, 0.0, -m_position.x
            , 0.0, 1.0, 0.0, -m_position.y
            , 0.0, 0.0, 1.0, -m_position.z
            , 0.0, 0.0, 0.0, 1.0);
        m_view_matrix = m1 * m2;
    }

    inline void generate_projection_matrix()
    {
        double tan_half_fovy = std::tan(m_fovy / 2.0);
        m_projection_matrix = GQYMath::mat4(
            1.0 / m_aspect / tan_half_fovy, 0.0, 0.0, 0.0
            , 0.0, 1.0 / tan_half_fovy, 0.0, 0.0
            , 0.0, 0.0, (m_near + m_far) / (m_far - m_near), 2.0 * m_near * m_far / (m_far - m_near)
            , 0.0, 0.0, -1.0, 0.0);
    }
};

#endif // !_GQY_CAMERA_H_