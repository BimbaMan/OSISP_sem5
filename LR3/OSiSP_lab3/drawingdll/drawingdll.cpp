#define BUILD_DLL

#include <math.h>
#include "drawingdll.h"

__declspec(dllexport) void draw(HDC hdc, int x, int y, int radius) //публичная функция
{
    HBRUSH brush = CreateSolidBrush(RGB(240, 20, 20));
    HPEN pen = CreatePen(PS_SOLID, 5, RGB(180, 15, 15));

    HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);
    HPEN oldPen = (HPEN)SelectObject(hdc, pen);

    const int VECTECES_COUNT = 8;
    double angle = 2 * 3.14159265358979323846 / VECTECES_COUNT;

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