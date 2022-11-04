
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
    Rasterization::create_camera(Point3(2.0, 45.0, 100.0), Point3(2.0, 45.0, 0.0), GQYMath::vec3(0.0, 1.0, 0.0), 75.0, 1.0, 1000.0);
    Rasterization::load_obj("../obj/tails/tails.obj");
    Rasterization::create_light(GQYMath::vec3(0.2, 0.2, 0.2), GQYMath::vec3(-1.0, -1.0, -1.0), GQYMath::vec3(0.8, 0.8, 0.8));

    Rasterization::show();
    Rasterization::shutDown();

    return 0;
}