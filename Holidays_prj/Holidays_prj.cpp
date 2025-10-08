#define _CRT_SECURE_NO_WARNINGS

#include "framework.h"
#include "Holidays_prj.h"

#include <crtdbg.h>
#define _CRTDBG_MAP_ALLOC
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                    _In_opt_ HINSTANCE hPrevInstance,
                    _In_ LPWSTR    lpCmdLine,
                    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    ULONG_PTR Token;
    Gdiplus::GdiplusStartupInput StartupInput;
    Gdiplus::GdiplusStartup(&Token, &StartupInput, nullptr);

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_HOLIDAYSPRJ, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_HOLIDAYSPRJ));

    MSG msg;
    ULONGLONG LastTime = GetTickCount64();

    // 기본 메시지 루프입니다:
    while(true)
    {
        while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
                goto EXIT_LOOP;

            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        ULONGLONG CurrentTime = GetTickCount64();
        float DeltaTime = (CurrentTime - LastTime) / 1000.0f;
        LastTime = CurrentTime;
        GameManager::GetInstance().Tick(DeltaTime);
        InvalidateRect(GameManager::GetInstance().GetWindowHandle(), nullptr, FALSE);
    }
EXIT_LOOP:;
    Gdiplus::GdiplusShutdown(Token);
    return (int) msg.wParam;
}


ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_HOLIDAYSPRJ));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = nullptr;
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}


BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

    RECT rc = {
        0, 0,
        GameManager::ScreenWidth,
        GameManager::ScreenHeight
    };

    AdjustWindowRectEx(
        &rc,
        WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX & ~WS_THICKFRAME,
        FALSE,
        0
    );

    HWND hWnd = CreateWindowW(
        szWindowClass,
        L"Holiday Project",
        WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX & ~WS_THICKFRAME,
        // App Position
        GameManager::GetInstance().GetAppPosition().X,
        GameManager::GetInstance().GetAppPosition().Y,
        // Screen Size
        rc.right - rc.left,
        rc.bottom - rc.top,
        nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        MessageBox(
            NULL,
            L"윈도우 생성 실패",
            L"오류",
            MB_OK | MB_ICONERROR
        );
        return FALSE;
    }

    GameManager::GetInstance().SetWindowHandle(hWnd);
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
        GameManager::GetInstance().Initialize();
        SceneManager::GetInstance().Initialize();
        
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        SceneManager::GetInstance().Destroy();
        GameManager::GetInstance().Destroy();

        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);

            GameManager::GetInstance().Render();
            Gdiplus::Graphics GraphicsInstance(hdc);
            GraphicsInstance.DrawImage(
                GameManager::GetInstance().GetBackBuffer(),
                0, 0
            );

            EndPaint(hWnd, &ps);
        }
        break;
    case WM_ERASEBKGND:
        return 1;
    case WM_KEYUP:
        InputManager::GetInstance().HandleKeyState(wParam, false);
        break;
    case WM_KEYDOWN:
        if (wParam == VK_ESCAPE)
        {
            DestroyWindow(hWnd);
        }
        InputManager::GetInstance().HandleKeyState(wParam, true);
        break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
