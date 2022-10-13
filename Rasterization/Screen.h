﻿#ifndef ____SCREEN_H____
#define ____SCREEN_H____

#include <windows.h>
#include <Eigen/Dense>
#include <Eigen/Core>

/*
* 屏幕类，最终图像会显示在屏幕上
*/
class Screen
{
private:
    // 变量
    HWND m_hwnd;                      // 窗口句柄
    HDC m_hdc;                        // 句柄
    HDC m_hdcMemory;                  // 内存句柄
    MSG m_message;                    // 消息队列
    WNDCLASS m_wndClass;              // 声明一个窗口类
    int m_width = 0;                  // 窗口宽度
    int m_height = 0;                 // 窗口高度

private:
    void draw(BYTE* frameBuffer);

public:
    // 公有函数
    Screen();
    ~Screen();

    void initScreen(
        HINSTANCE hInstance,
        HINSTANCE hPrevInstance,
        PSTR lpCmdLine,
        INT nCmdShow,
        WNDPROC callBackFunction,       // 回到函数
        LPCWSTR windowName,             // 窗口名字
        INT windowWidth,                // 窗口宽度
        INT windowHeight                // 窗口高度
    );                                  // 初始化窗口
    void show(BYTE* frameBuffer);       // 显示窗口
    int width();
    int height();
};

#endif // !____SCREEN_H____

