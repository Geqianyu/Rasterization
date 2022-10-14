#ifndef ____CAMERA_H____
#define ____CAMERA_H____

#include <Eigen/Dense>
#include <Eigen/Core>

/*
* Camera类，保存相机相关信息
*/
class Camera
{
private:
    // 变量
    Eigen::Vector3d m_position;         // 相机坐标
    Eigen::Vector3d m_x;                // 右方向
    Eigen::Vector3d m_z;                // 看向的反方向
    Eigen::Vector3d m_y;                // 上方向
    Eigen::Matrix4d m_viewMatrix;       // 视坐标变换矩阵
    Eigen::Matrix4d m_projectionMatrix; // 投影矩阵
    double m_fovy = 90.0;               // 角度
    double m_aspect = 1.0;              // 高度 / 宽度
    double m_near = 1.0;                // 近平面
    double m_far = 10.0;                // 远平面

public:
    // 公有函数
    Camera();
    Camera(const Camera& camera);
    Camera(Eigen::Vector3d eye, Eigen::Vector3d lookat, Eigen::Vector3d up, double fovy, double aspect, double nearPlane, double farPlane);
    ~Camera();
    void setAspect(double aspect);
    void changeFovy(double step);
    Eigen::Matrix4d viewMatrix();
    Eigen::Matrix4d projectionMatrix();
    Eigen::Vector3d position();
    Eigen::Vector3d XAxis();
    Eigen::Vector3d YAxis();
    Eigen::Vector3d ZAxis();

private:
    // 私有函数
    void generateViewMatrix();
    void generateProjectionMatrix();
};

#endif // !____CAMERA_H____

