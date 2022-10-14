#ifndef ____RASTERIZATION_H____
#define ____RASTERIZATION_H____

#include <string>
#include <cmath>

#include "Screen.h"
#include "Obj.h"
#include "Camera.h"
#include "Shader.h"

/*
* 光栅化空间
*/

// 回调函数
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

namespace Rasterization
{
    const double PI = std::asin(1.0) * 2.0;
    Screen m_screen;                                                        // 显示窗口
    Camera m_camera;                                                        // 相机
    Obj m_obj;                                                              // 用于加载 .obj 文件
    Shader* m_pShader = nullptr;                                            // 着色器指针
    bool m_LisDown = false;                                                 // 标记鼠标左键是否按下
    bool m_RisDown = false;                                                 // 标记鼠标右键是否按下
    double m_aspect = 1.0;                                                  // 显示窗口的 宽高 比
    LPPOINT m_lastPoint = new POINT();                                      // 保存鼠标按下时的鼠标值
    LPPOINT m_point = new POINT();                                          // 保存鼠标移动时的鼠标值
    Eigen::Matrix4d m_modelMatrix = Eigen::Matrix4d::Identity();            // 模型的变换矩阵
    Eigen::Matrix4d m_modelRotate = Eigen::Matrix4d::Identity();            // 模型的旋转变换
    Eigen::Matrix4d m_modelTranslate = Eigen::Matrix4d::Identity();         // 模型的平移变换

    void createScreen(                                                                                                                      // 创建窗口
        HINSTANCE hInstance,
        HINSTANCE hPrevInstance,
        PSTR lpCmdLine,
        INT nCmdShow,
        LPCWSTR windowName,             // 窗口名字
        INT windowWidth,                // 窗口宽度
        INT windowHeight                // 窗口高度
    );
    void loadObj(std::string objFilePath);                                                                                                  // 加载 .obj 文件
    void createCamera(Eigen::Vector3d eye, Eigen::Vector3d lookat, Eigen::Vector3d up, double fovy, double nearPlane, double farPlane);     // 创建相机

    void show();
    void shutDown();
}

void Rasterization::createScreen(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    PSTR lpCmdLine,
    INT nCmdShow,
    LPCWSTR windowName,             // 窗口名字
    INT windowWidth,                // 窗口宽度
    INT windowHeight                // 窗口高度
)
{
    m_screen.initScreen(
        hInstance,
        hPrevInstance,
        lpCmdLine,
        nCmdShow,
        WndProc,
        windowName,
        windowWidth,
        windowHeight
    );
    m_aspect = (float)windowHeight / (float)windowWidth;
}

void Rasterization::loadObj(std::string objFilePath)
{
    m_obj.loadObj(objFilePath);
}

void Rasterization::createCamera(Eigen::Vector3d eye, Eigen::Vector3d lookat, Eigen::Vector3d up, double fovy, double nearPlane, double farPlane)
{
    m_camera = Camera(eye, lookat, up, fovy, m_aspect, nearPlane, farPlane);
}

void Rasterization::show()
{
    m_pShader = new Shader(&m_obj, m_screen.width(), m_screen.height());
    m_screen.show(m_pShader, &m_camera);
}

void Rasterization::shutDown()
{
    if (m_pShader != nullptr)
    {
        delete m_pShader;
        m_pShader = nullptr;
    }
}

// 回调函数
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CLOSE:
        // 销毁窗口 但是不结束进程, 而是发送另一个消息 WM_DESTROY
        DestroyWindow(hwnd);
        break;
    case WM_DESTROY:
        // 发送 退出 消息, 发送完此消息后在 while(GetMessage(&message, NULL, 0, 0)) 循环里获得的就是 false
        PostQuitMessage(0);
        break;
    case WM_KEYDOWN:
        // wParam 中保存的是虚拟键盘值
        switch (wParam)
        {
        case VK_ESCAPE:
            // 销毁窗口 但是不结束进程, 而是发送另一个消息 WM_DESTROY
            DestroyWindow(hwnd);
            break;
        }
        break;
    case WM_LBUTTONDOWN:
        Rasterization::m_LisDown = true;
        GetCursorPos(Rasterization::m_lastPoint);
        break;
    case WM_LBUTTONUP:
        Rasterization::m_LisDown = false;
        break;
    case WM_MOUSEMOVE:
        if (Rasterization::m_LisDown)
        {
            GetCursorPos(Rasterization::m_point);
            double angle = 0.0;
            Eigen::Vector3d n;
            if (GetKeyState(VK_CONTROL) & 0X8000)
            {
                // 按住 ctrl 时 垂直旋转
                n = Rasterization::m_camera.XAxis();
                angle = (Rasterization::m_point->y - Rasterization::m_lastPoint->y) * Rasterization::PI / 180.0;
            }
            else
            {
                n = Rasterization::m_camera.YAxis();
                angle = (Rasterization::m_point->x - Rasterization::m_lastPoint->x) * Rasterization::PI / 180.0;
            }
            Rasterization::m_modelRotate = Rasterization::m_obj.rotate(angle, n) * Rasterization::m_modelRotate;

            Rasterization::m_lastPoint->x = Rasterization::m_point->x;
            Rasterization::m_lastPoint->y = Rasterization::m_point->y;
        }
        else if (Rasterization::m_RisDown)
        {
            GetCursorPos(Rasterization::m_point);
            double stepX = Rasterization::m_point->x - Rasterization::m_lastPoint->x;
            double stepY = Rasterization::m_point->y - Rasterization::m_lastPoint->y;
            Rasterization::m_modelTranslate = Rasterization::m_obj.translate(stepX, Rasterization::m_camera.XAxis()) * Rasterization::m_obj.translate(-stepY, Rasterization::m_camera.YAxis()) * Rasterization::m_modelTranslate;
            Rasterization::m_screen.setModelMatrix(Rasterization::m_modelMatrix);
            Rasterization::m_lastPoint->x = Rasterization::m_point->x;
            Rasterization::m_lastPoint->y = Rasterization::m_point->y;
        }
        Rasterization::m_modelMatrix = Rasterization::m_modelTranslate * Rasterization::m_modelRotate;
        Rasterization::m_screen.setModelMatrix(Rasterization::m_modelMatrix);
        break;
    case WM_RBUTTONDOWN:
        // 鼠标右键 移动对象
        Rasterization::m_RisDown = true;
        GetCursorPos(Rasterization::m_lastPoint);
        break;
    case WM_RBUTTONUP:
        Rasterization::m_RisDown = false;
        break;
    case WM_MOUSEWHEEL:
        if ((SHORT)HIWORD(wParam) > 0)
        {
            Rasterization::m_camera.changeFovy(-1.0f);
        }
        else
        {
            Rasterization::m_camera.changeFovy(1.0f);
        }
        break;
    default:
        break;
    }

    // DefWindowProc 用于处理 自定义的消息处理函数 未处理的 消息
    return DefWindowProc(hwnd, message, wParam, lParam);
}

#endif // !____RASTERIZATION_H____
