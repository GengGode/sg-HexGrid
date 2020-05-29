#include "test.hpp"
#include <windows.h>
#include <d2d1.h>

ID2D1Factory *pD2DFactory = NULL;            // Direct2D factory
ID2D1HwndRenderTarget *pRenderTarget = NULL; // Render target
ID2D1SolidColorBrush *pBlackBrush = NULL;    // A black brush, reflect the line color

RECT rc;     // Render area
HWND g_Hwnd; // Window handle

int main()
{
    cout << "System On ..." << endl;
    Hex h(point2d(0, 0), 10);
    h.out();

    int k[] = {1, 2, 3, 4, 5};
    T t(k);


    return 0;
}