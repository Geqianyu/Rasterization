
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
    Rasterization::createCamera(Eigen::Vector3d(4.6, 47.6, 75.0), Eigen::Vector3d(4.6, 47.6, 0.0), Eigen::Vector3d(0.0, 1.0, 0.0), 90.0, 1.0, 150.0);
    Rasterization::loadObj("../obj/tails/tails.obj");
    Rasterization::createLight(Eigen::Vector3d(0.4, 0.4, 0.4), Eigen::Vector3d(-1.0, -1.0, -1.0), Eigen::Vector3d(0.6, 0.6, 0.6));

    Rasterization::show();
    Rasterization::shutDown();

    return 0;
}