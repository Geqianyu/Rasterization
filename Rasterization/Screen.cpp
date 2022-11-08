#include <vector>
#include <ctime>
#include <cmath>

#include "Screen.h"

Screen::Screen()
{
    m_width = 0;
    m_height = 0;
}

Screen::~Screen()
{
    DestroyWindow(m_hwnd);
    DeleteDC(m_hdc);
    DeleteDC(m_hdcMemory);
}

void Screen::initScreen(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    PSTR lpCmdLine,
    INT nCmdShow,
    WNDPROC callBackFunction,
    LPCWSTR windowName,
    INT windowWidth,
    INT windowHeight)
{
    // 保存客户区大小
    m_width = windowWidth;
    m_height = windowHeight;

    // 计算指定客户区大小的窗口需要多大尺寸
    RECT windowRect;
    windowRect.left = 0;
    windowRect.top = 0;
    windowRect.right = windowWidth;
    windowRect.bottom = windowHeight;
    AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, FALSE);

    // 设置窗口类
    m_wndClass.style = CS_HREDRAW | CS_VREDRAW;                           // 窗口样式
    m_wndClass.lpszClassName = TEXT("MyWindowClass");                     // 窗口类名
    m_wndClass.lpszMenuName = nullptr;                                    // 窗口菜单: 无
    m_wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);       // 窗口背景颜色
    m_wndClass.lpfnWndProc = callBackFunction;                            // 窗口消息处理函数
    m_wndClass.cbClsExtra = 0;                                            // 窗口类扩展: 无
    m_wndClass.cbWndExtra = 0;                                            // 窗口实例扩展: 无
    m_wndClass.hInstance = hInstance;                                     // 窗口句柄
    m_wndClass.hIcon = LoadIcon(nullptr, IDI_APPLICATION);                // 窗口最小化图标，使用缺省图标
    m_wndClass.hCursor = LoadCursor(nullptr, IDC_ARROW);                  // 窗口采用箭头光标
    if (!RegisterClass(&m_wndClass))
    {
        // 如果注册窗口类失败，则给出提示
        MessageBox(NULL, TEXT("窗口注册失败"), TEXT("错误"), MB_OK | MB_ICONERROR);
        exit(-1);
    }

    // 创建窗口
    m_hwnd = CreateWindow(
        TEXT("MyWindowClass"),                          // 窗口类名
        windowName,                                     // 窗口标题名
        WS_OVERLAPPEDWINDOW,                            // 窗口的风格
        CW_USEDEFAULT,                                  // 窗口初始化的 x 坐标, 使用默认值
        CW_USEDEFAULT,                                  // 窗口初始化的 y 坐标, 使用默认值
        windowRect.right - windowRect.left,             // 窗口的宽度
        windowRect.bottom - windowRect.top,             // 窗口的高度
        nullptr,                                        // 父窗口, 无
        nullptr,                                        // 子窗口, 无
        hInstance,                                      // 该窗口应用程序的实例句柄
        nullptr
    );

    // 获得句柄
    m_hdc = GetDC(m_hwnd);
    m_hdcMemory = CreateCompatibleDC(m_hdc);
}

void Screen::show(Shader* pShader, Camera* pCamera, Light* pLight, GQYMath::mat4& _translate)
{
    // 显示窗口
    ShowWindow(m_hwnd, SW_SHOWNORMAL);

    // 从消息队列中获取消息
    while (GetMessage(&m_message, NULL, 0, 0))
    {
        BYTE* frameBuffer = pShader->shading(*pCamera, *pLight, _translate);
        draw(frameBuffer);
        // 将 虚拟键 消息 转为 字符 消息
        TranslateMessage(&m_message);

        // 将 消息 分发到 回调函数
        DispatchMessage(&m_message);
    }
}

void Screen::draw(BYTE* frameBuffer)
{
    HBITMAP hBmpMemory = CreateCompatibleBitmap(m_hdc, m_width, m_height);
    HBITMAP hPrevBmp = (HBITMAP)SelectObject(m_hdcMemory, hBmpMemory);

    // 填写BITMAPINFO结构
    BITMAPINFO bmpInfo;
    ZeroMemory(&bmpInfo, sizeof(BITMAPINFO));
    bmpInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmpInfo.bmiHeader.biWidth = m_width;
    bmpInfo.bmiHeader.biHeight = m_height;
    bmpInfo.bmiHeader.biPlanes = 1;
    bmpInfo.bmiHeader.biBitCount = 24;
    bmpInfo.bmiHeader.biCompression = BI_RGB;
    bmpInfo.bmiHeader.biSizeImage = 0;

    SetDIBits(m_hdcMemory, hBmpMemory, 0, m_height, frameBuffer, (BITMAPINFO*)&bmpInfo, DIB_RGB_COLORS);
    BitBlt(m_hdc, 0, 0, m_width, m_height, m_hdcMemory, 0, 0, SRCCOPY);
    DeleteObject(hBmpMemory);
    DeleteObject(hPrevBmp);
}