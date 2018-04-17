/**
 * main.cpp
 * Генератор растровых изображений
 * Copyright (c) 2018 Lev Vorobjev
 */

#include <windows.h>
#include <tchar.h>
#include "rgb_draw_context.h"
#include "rand_bmp_generator.h"

#define WND_TITLE TEXT("Растровый генератор")
#define WND_MENU_NAME NULL
#define MSG_TITLE TEXT("RandBmp")
#define BUFFER_SIZE 512

#define WND_WIDTH  320
#define WND_HEIGHT 240

#define IDT_TIMER 4001

#define HANDLE_ERROR(lpszFunctionName, dwStatus) \
    _stprintf(lpszBuffer, TEXT("%s error.\nStatus code: %d"), \
        TEXT("lpszFunctionName"), dwStatus); \
    MessageBox(hWnd, lpszBuffer, MSG_TITLE, MB_OK | MB_ICONWARNING);

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
ATOM RegMyWindowClass(HINSTANCE, LPCTSTR);

int APIENTRY WinMain(HINSTANCE hInstance,
             HINSTANCE         hPrevInstance,
             LPSTR             lpCmdLine,
             int               nCmdShow) {
    LPCTSTR lpszClass = TEXT("RandBmp_Window");
    LPCTSTR lpszTitle = WND_TITLE;
    HWND hWnd;
    MSG msg = {0};
    BOOL status;

    if (!RegMyWindowClass(hInstance, lpszClass))
        return 1;

    hWnd = CreateWindow(lpszClass, lpszTitle, WS_OVERLAPPED | WS_SYSMENU,
        CW_USEDEFAULT, CW_USEDEFAULT, WND_WIDTH, WND_HEIGHT,
        NULL, NULL, hInstance, NULL);
    if(!hWnd) return 2;

    ShowWindow(hWnd, nCmdShow);

    while ((status = GetMessage(&msg, NULL, 0, 0 )) != 0) {
        if (status == -1) return 3;
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}

ATOM RegMyWindowClass(HINSTANCE hInst, LPCTSTR lpszClassName) {
    WNDCLASS wcWindowClass = {0};
    wcWindowClass.lpfnWndProc = (WNDPROC)WndProc;
    wcWindowClass.style = CS_HREDRAW|CS_VREDRAW;
    wcWindowClass.hInstance = hInst;
    wcWindowClass.lpszClassName = lpszClassName;
    wcWindowClass.lpszMenuName = WND_MENU_NAME;
    wcWindowClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wcWindowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcWindowClass.hbrBackground = (HBRUSH) ( COLOR_WINDOW + 1);
    wcWindowClass.cbClsExtra = 0;
    wcWindowClass.cbWndExtra = 0;
    return RegisterClass(&wcWindowClass);
}

void DrawBitmap(HDC hDC, int x, int y, HBITMAP hBitmap);

LRESULT CALLBACK WndProc(HWND hWnd, UINT message,
                         WPARAM wParam, LPARAM lParam) {
    HDC hdc;
    PAINTSTRUCT ps;

	static LPTSTR lpszBuffer;

    static BmpGenerator* generator;
    static DrawContext* render;

    const int nWidthBytes = ((((WND_WIDTH+7)/8)+1)/2)*2;
    static BITMAP bmp = { 0, WND_WIDTH, WND_HEIGHT, nWidthBytes, 1, 1, NULL };
    static HBITMAP hBmp;

    static DWORD dwTick = GetTickCount();

	switch (message) {
      case WM_CREATE:
		lpszBuffer = (LPTSTR)calloc(BUFFER_SIZE, sizeof(TCHAR));
        generator = new RandBmpGenerator(WND_WIDTH, WND_HEIGHT);
        render = new RgbDrawContext();
        generator->initialize();
        bmp.bmBits = (LPVOID)calloc(nWidthBytes*WND_HEIGHT, 1);
        render->draw(generator, &bmp);
        hBmp = CreateBitmapIndirect(&bmp);
        SetTimer(hWnd, IDT_TIMER, 2000, (TIMERPROC) NULL);
		break;
      case WM_TIMER:
      {
        DWORD dwNextTick;
        generator->step((double)((dwNextTick = GetTickCount()) - dwTick) / 100000.0);
        dwTick = dwNextTick;
        render->draw(generator, &bmp);
        SetBitmapBits(hBmp, nWidthBytes * WND_WIDTH, bmp.bmBits);
        InvalidateRect(hWnd, NULL, FALSE);
        break;
      }
      case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        DrawBitmap(hdc, 0, 0, hBmp);
        EndPaint(hWnd, &ps);
        break;
	  case WM_DESTROY:
        KillTimer(hWnd, IDT_TIMER);
        delete generator;
        free (bmp.bmBits);
        DeleteObject(hBmp);
        free (lpszBuffer);
		PostQuitMessage(0);
		break;
	  default:
        return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// ======================================================
// Рисование изображения типа bitmap
// http://frolov-lib.ru/books/bsp/v14/ch4_1.htm
// ======================================================
void DrawBitmap(HDC hDC, int x, int y, HBITMAP hBitmap)
{
  HBITMAP hOldbm;
  HDC hMemDC;
  BITMAP bm;
  POINT  ptSize, ptOrg;

  // Создаем контекст памяти, совместимый
  // с контекстом отображения
  hMemDC = CreateCompatibleDC(hDC);

  // Выбираем изображение bitmap в контекст памяти
  hOldbm = (HBITMAP)SelectObject(hMemDC, hBitmap);

  // Если не было ошибок, продолжаем работу
  if (hOldbm)
  {
    // Для контекста памяти устанавливаем тот же
    // режим отображения, что используется в
    // контексте отображения
    SetMapMode(hMemDC, GetMapMode(hDC));

    // Определяем размеры изображения
    GetObject(hBitmap, sizeof(BITMAP), (LPSTR)&bm);

    ptSize.x = bm.bmWidth;   // ширина
    ptSize.y = bm.bmHeight;  // высота

    // Преобразуем координаты устройства в логические
    // для устройства вывода
    DPtoLP(hDC, &ptSize, 1);

    ptOrg.x = 0;
    ptOrg.y = 0;

    // Преобразуем координаты устройства в логические
    // для контекста памяти
    DPtoLP(hMemDC, &ptOrg, 1);

    // Рисуем изображение bitmap
    BitBlt(hDC, x, y, ptSize.x, ptSize.y,
           hMemDC, ptOrg.x, ptOrg.y, SRCCOPY);

    // Восстанавливаем контекст памяти
    SelectObject(hMemDC, hOldbm);
  }

  // Удаляем контекст памяти
  DeleteDC(hMemDC);
}
