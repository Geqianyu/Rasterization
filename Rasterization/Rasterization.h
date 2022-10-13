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
    Screen m_screen;
    Camera m_camera;
    Obj m_obj;
    Shader* m_pShader = nullptr;
    bool m_isDown = false;
    double m_aspect = 1.0;
    LPPOINT m_lastPoint = new POINT();
    LPPOINT m_point = new POINT();

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

    // void rotateMeshX(int x);
    // void rotateMeshY(int y);
    // void rotateMeshZ(int z);
    // void moveCameraX(float step);
    // void moveCameraY(float step);
    // void moveCameraZ(float step);
    void show();
    void shutDown();
    // bool canMoveCamera();
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

// void Rasterization::rotateMeshX(int x)
// {
//     m_scene.rotateMeshX(x);
// }
// 
// void Rasterization::rotateMeshY(int y)
// {
//     m_scene.rotateMeshY(y);
// }
// 
// void Rasterization::rotateMeshZ(int z)
// {
//     m_scene.rotateMeshZ(z);
// }
// 
// void Rasterization::moveCameraX(float step)
// {
//     m_scene.moveCameraX(0.08f * step);
// }
// 
// void Rasterization::moveCameraY(float step)
// {
//     m_scene.moveCameraY(0.08f * step);
// }
// 
// void Rasterization::moveCameraZ(float step)
// {
//     m_scene.moveCameraZ(0.08f * step);
// }

void Rasterization::show()
{
    m_pShader = new Shader(&m_obj, m_screen.width(), m_screen.height());
    BYTE* frameBuffer = m_pShader->shading(m_camera);
    m_screen.show(frameBuffer);
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
        // case WM_CHAR:
        //     if (GetKeyState(87) & 0X8000)
        //     {
        //         // 按下 W 键
        //         Rasterization::moveCameraY(1.0f);
        //     }
        //     else if (GetKeyState(83) & 0X8000)
        //     {
        //         // 按下 S 键
        //         Rasterization::moveCameraY(-1.0f);
        //     }
        //     else if (GetKeyState(65) & 0X8000)
        //     {
        //         // 按下 A 键
        //         Rasterization::moveCameraX(-1.0f);
        //     }
        //     else if (GetKeyState(68) & 0X8000)
        //     {
        //         // 按下 D 键
        //         Rasterization::moveCameraX(1.0f);
        //     }
        //     break;
        // case WM_LBUTTONDOWN:
        //     Rasterization::m_isDown = true;
        //     GetCursorPos(Rasterization::m_lastPoint);
        //     break;
        // case WM_LBUTTONUP:
        //     Rasterization::m_isDown = false;
        //     break;
        // case WM_MOUSEMOVE:
        //     if (Rasterization::m_isDown)
        //     {
        //         GetCursorPos(Rasterization::m_point);
        //         if (GetKeyState(VK_CONTROL) & 0X8000)
        //         {
        //             // 按住 ctrl 时 垂直旋转
        //             Rasterization::rotateMeshX(Rasterization::m_point->y - Rasterization::m_lastPoint->y);
        //         }
        //         else
        //         {
        //             Rasterization::rotateMeshY(Rasterization::m_point->x - Rasterization::m_lastPoint->x);
        //         }
        //         Rasterization::m_lastPoint->x = Rasterization::m_point->x;
        //         Rasterization::m_lastPoint->y = Rasterization::m_point->y;
        //     }
        //     break;
        // case WM_RBUTTONDOWN:
        //     // 鼠标右键 移动对象
        //     break;
        // case WM_MOUSEWHEEL:
        //     if ((SHORT)HIWORD(wParam) > 0)
        //     {
        //         if (Rasterization::canMoveCamera())
        //         {
        //             Rasterization::moveCameraZ(1.0f);
        //         }
        //     }
        //     else
        //     {
        //         Rasterization::moveCameraZ(-1.0f);
        //     }
        //     break;
    default:
        break;
    }

    // DefWindowProc 用于处理 自定义的消息处理函数 未处理的 消息
    return DefWindowProc(hwnd, message, wParam, lParam);
}

#endif // !____RASTERIZATION_H____
