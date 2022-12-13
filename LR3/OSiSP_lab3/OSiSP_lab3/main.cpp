#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <windowsx.h>
#include <anotherdrawingdll.h> 

#pragma comment(lib, "anotherdrawingdll.lib")

#define RADIUS 75

struct Point
{
    int x;
    int y;
};

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void WM_DESTROY_Handler();
void WM_PAINT_Handler(HWND hwnd);
void WM_LBUTTONUP_Handler(HWND hwnd, WPARAM wParam, LPARAM lParam);

Point* point = NULL;

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    const wchar_t CLASS_NAME[] = L"WinAPIPracticeClass";
    WNDCLASS wc = { };
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(0, CLASS_NAME, L"WinAPIPractice", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        NULL, NULL, hInstance, NULL);

    if (hwnd == NULL)
        return EXIT_FAILURE;

    ShowWindow(hwnd, nCmdShow);

    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    if (point != NULL)
        delete(point);

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_DESTROY:
            WM_DESTROY_Handler();
            break;

        case WM_PAINT:
            WM_PAINT_Handler(hwnd);
            break;

        case WM_LBUTTONUP:
            WM_LBUTTONUP_Handler(hwnd, wParam, lParam);
            break;

        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return 0;
}

void WM_DESTROY_Handler()
{
    PostQuitMessage(0);
}

void WM_PAINT_Handler(HWND hwnd)
{
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hwnd, &ps);

    if (point != NULL)
    {
        draw(hdc, point->x, point->y, RADIUS);
        
        delete(point);
        point = NULL;
    }

    EndPaint(hwnd, &ps);
}

void WM_LBUTTONUP_Handler(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
    point = new Point();
    point->x = GET_X_LPARAM(lParam);
    point->y = GET_Y_LPARAM(lParam);

    InvalidateRect(hwnd, NULL, true);
}
