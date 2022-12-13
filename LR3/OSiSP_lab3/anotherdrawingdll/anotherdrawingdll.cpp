#define BUILD_DLL

#include <math.h>
#include <random>
#include "anotherdrawingdll.h"

namespace add
{
    extern "C" __declspec(dllexport) void draw(HDC hdc, int x, int y, int radius)
    {
        HBRUSH brush = CreateSolidBrush(RGB(250, 250, 50));
        HPEN pen = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));

        HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);
        HPEN oldPen = (HPEN)SelectObject(hdc, pen);

        const int VECTECES_COUNT = 9 + 3;
        double angle = 2 * std::_Pi / VECTECES_COUNT;

        POINT* points = new POINT[VECTECES_COUNT];
        for (int i = 0; i < VECTECES_COUNT; ++i)
        {
            points[i].x = x + radius * sin(i * angle);
            points[i].y = y + radius * cos(i * angle);
        }

        Polygon(hdc, points, VECTECES_COUNT);
        delete(points);

        SelectObject(hdc, oldPen);
        SelectObject(hdc, oldBrush);
        DeleteObject(brush);
        DeleteObject(pen);
    }
}