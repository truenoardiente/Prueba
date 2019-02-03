#include <windows.h>
#include "Prueba.h"

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

//void InsertarMenu(HWND hwnd);

int WINAPI WinMain(HINSTANCE  hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
    HWND hwnd;
    MSG mensaje;
    WNDCLASSEX wincl;
    HMENU hMenu;

    wincl.hInstance = hInstance;
    wincl.lpszClassName = "NUESTRA_CLASE";
    wincl.lpfnWndProc = WindowProcedure;
    wincl.style = CS_DBLCLKS;
    wincl.cbSize = sizeof(WNDCLASSEX);

    wincl.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor(NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;
    wincl.cbClsExtra = 0;
    wincl.cbWndExtra = 0;
    wincl.hbrBackground = (HBRUSH)COLOR_BACKGROUND;

    if(!RegisterClassEx(&wincl))return 0;

    hwnd = CreateWindowEx(
            0,
            "NUESTRA_CLASE",
            "Ejemplo",
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            544,
            375,
            HWND_DESKTOP,
            NULL,
            hInstance,
            NULL
    );

    hMenu = LoadMenu(hInstance,  "Menu");
    SetMenu(hwnd, hMenu);
    ShowWindow(hwnd, SW_SHOWDEFAULT);

    while(true == GetMessage(&mensaje, 0, 0, 0))
    {
        TranslateMessage(&mensaje);
        DispatchMessage(&mensaje);
    }

    return mensaje.wParam;
}

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
    case WM_COMMAND:
        switch(LOWORD(wParam))
        {
        case CM_PRUEBA:
            MessageBox(hwnd, "Comando: Prueba", "Mensaje de menú", MB_OK);
            break;
        case CM_SALIR:
            MessageBox(hwnd, "Comando: Salir", "Mensaje de menú", MB_OK);
            PostQuitMessage(0);
            break;
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

/*void InsertarMenu(HWND hwnd)
{
    HMENU hMenu1, hMenu2;

    hMenu1 = CreateMenu();
    hMenu2 = CreateMenu();
    AppendMenu(hMenu2, MF_STRING, CM_PRUEBA, "&Prueba");
    AppendMenu(hMenu2, MF_SEPARATOR, 0, NULL);
    AppendMenu(hMenu2, MF_STRING, CM_SALIR, "&Salir");

    AppendMenu(hMenu1, MF_STRING | MF_POPUP, (UINT)hMenu2, "&Principal");
    SetMenu(hwnd, hMenu1);
}
*/
