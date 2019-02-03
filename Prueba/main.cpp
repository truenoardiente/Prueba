#include <windows.h>
#include <iostream>
#include "Prueba.h"

using namespace std;

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK DialogProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam);
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
    static HINSTANCE hInstance;
    static int veces=0;

    switch(msg)
    {
    case WM_CREATE:
        hInstance = ((LPCREATESTRUCT)lParam)->hInstance;
        return 0;
        break;
    case WM_COMMAND:
        switch(LOWORD(wParam))
        {
        case CM_DIALOGO:
            veces++;
            DialogBoxParam(hInstance, "DialogoPrueba", hwnd, DialogProc, veces);
            break;
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

BOOL CALLBACK DialogProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
    char texto[25];

    switch (msg)
    {
        case WM_INITDIALOG:
            sprintf(texto, "Veces invocado: %d", lParam);
            SetWindowText(GetDlgItem(hDlg, TEXTO), texto);
            return TRUE;
        case WM_COMMAND:
            EndDialog(hDlg, FALSE);
            return TRUE;
    }
    return TRUE;
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
