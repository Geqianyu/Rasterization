#ifndef _GQY_RASTERIZATION_H_
#define _GQY_RASTERIZATION_H_

#include <string>
#include <cmath>

#include "Math.h"
#include "Screen.h"
#include "Obj.h"
#include "Camera.h"
#include "Shader.h"
#include "Light.h"

/*
* 光栅化空间
*/

// 回调函数
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

namespace Rasterization
{
    Screen m_screen;                                                        // 显示窗口
    Camera m_camera;                                                        // 相机
    Obj m_obj;                                                              // 用于加载 .obj 文件
    Light m_light;                                                          // 光源
    Shader* m_pShader = nullptr;                                            // 着色器指针
    double m_aspect = 1.0;                                                  // 显示窗口的 宽高 比
    LPPOINT m_point = new POINT();                                          // 保存鼠标移动时的鼠标值

    void createScreen(                                                                                                                      // 创建窗口
        HINSTANCE hInstance,
        HINSTANCE hPrevInstance,
        PSTR lpCmdLine,
        INT nCmdShow,
        LPCWSTR windowName,             // 窗口名字
        INT windowWidth,                // 窗口宽度
        INT windowHeight                // 窗口高度
    );
    void load_obj(std::string _obj_file_path);                                                                                                  // 加载 .obj 文件
    void create_camera(Point3 _eye, Point3 _lookat, GQYMath::vec3 _up, double _fovy, double _near_plane, double _far_plane);     // 创建相机
    void create_light(GQYMath::vec3 _ambient, GQYMath::vec3 _direction, GQYMath::vec3 _emission);                                         // 创建光源

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

void Rasterization::load_obj(std::string _obj_file_path)
{
    m_obj.load_obj(_obj_file_path);
}

void Rasterization::create_camera(Point3 _eye, Point3 _lookat, GQYMath::vec3 _up, double _fovy, double _near_plane, double _far_plane)
{
    m_camera = Camera(_eye, _lookat, _up, _fovy, m_aspect, _near_plane, _far_plane);
}

void Rasterization::create_light(GQYMath::vec3 _ambient, GQYMath::vec3 _direction, GQYMath::vec3 _emission)
{
    m_light = Light(_ambient, _direction, _emission);
}

void Rasterization::show()
{
    m_pShader = new Shader(&m_obj, m_screen.width(), m_screen.height());
    m_screen.show(m_pShader, &m_camera, &m_light);
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
        case 87:
            // 按下 W 键，相机向前移动
            Rasterization::m_camera.move(MOVE_DIRECTION::FRONT);
            break;
        case 65:
            // 按下 A 键，相机向左移动
            Rasterization::m_camera.move(MOVE_DIRECTION::LEFT);
            break;
        case 83:
            // 按下 S 键，相机向后移动
            Rasterization::m_camera.move(MOVE_DIRECTION::BACK);
            break;
        case 68:
            // 按下 D 键，相机向右移动
            Rasterization::m_camera.move(MOVE_DIRECTION::RIGHT);
            break;
        }
        break;
    case WM_MOUSEMOVE:
        // 鼠标移动，调整摄像机的朝向
        GetCursorPos(Rasterization::m_point);
        Rasterization::m_camera.change_direction(Rasterization::m_point->x, Rasterization::m_point->y);
        break;
    case WM_MOUSEWHEEL:
        if ((SHORT)HIWORD(wParam) > 0)
        {
            Rasterization::m_camera.change_fovy(-1.0f);
        }
        else
        {
            Rasterization::m_camera.change_fovy(1.0f);
        }
        break;
    default:
        break;
    }

    // DefWindowProc 用于处理 自定义的消息处理函数 未处理的 消息
    return DefWindowProc(hwnd, message, wParam, lParam);
}

#endif // !_GQY_RASTERIZATION_H_
