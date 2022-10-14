
#include <windows.h>

#include "Rasterization.h"

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow)
{
    Rasterization::createScreen(
        hInstance,
        hPrevInstance,
        lpCmdLine,
        nCmdShow,
        TEXT("Rasterization"),
        800,
        800
    );
    Rasterization::createCamera(Eigen::Vector3d(-500.2, 52.2, 1250.0), Eigen::Vector3d(-500.2, 52.2, 0.0), Eigen::Vector3d(0.0, 1.0, 0.0), 90.0, 10.0, 2400.0);
    Rasterization::loadObj("../obj/miku/miku.obj");
    Rasterization::createLight(Eigen::Vector3d(0.5, 0.5, 0.5), Eigen::Vector3d(-1.0, -1.0, -1.0), Eigen::Vector3d(0.5, 0.5, 0.5));

    Rasterization::show();
    Rasterization::shutDown();

    return 0;
}