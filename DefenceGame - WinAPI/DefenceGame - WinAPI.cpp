﻿// DefenceGame - WinAPI.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "DefenceGame - WinAPI.h"
#include <tchar.h>

//custom header
#include "DefenceGame.h"

#define MAX_LOADSTRING 100
#define TIMER1 1001
#define TIMER2 1002

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

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_DEFENCEGAMEWINAPI, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DEFENCEGAMEWINAPI));

    MSG msg;

    // 기본 메시지 루프입니다:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DEFENCEGAMEWINAPI));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_DEFENCEGAMEWINAPI);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	const int ID_size = 15;
	static SIZE size;
	static DefenceGame game;
	static TCHAR name[5][ID_size] = { {0}, {0} , {0}, {0},{0} };
	static int score[5] = { 0,0,0,0,0 };
	static int ID_itr = 0;
	static int Screen_flag = 1;
	static RECT rectview;
	static RECT ID_rect;




    switch (message)
    {
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
	case WM_CREATE:
	{
		HANDLE hFile;
		GetClientRect(hWnd, &rectview);
		CreateCaret(hWnd, NULL, 5, 15);
		ShowCaret(hWnd);
	}
	break; 
	case WM_TIMER:
	{
		if (wParam == TIMER1)
		{
			game.Update(rectview);
			if (game.getHP() == 0)
			{
				Screen_flag = 3;
				KillTimer(hWnd,TIMER1);
				KillTimer(hWnd,TIMER2);
 				game.Save(name, score);
			}
		}
		else if (wParam == TIMER2)
			game.make_Enemy(rectview, 10);



		InvalidateRect(hWnd, NULL, true);
	}
	break;
	case WM_KEYDOWN:
	{
		if (Screen_flag == 1)
		{

			if (wParam == VK_BACK)
			{
				if (ID_itr >= 0)
				{
					game.set_ID()[ID_itr] = NULL;
					if (ID_itr > 0)
						ID_itr--;
				}
			}
			else if (wParam == VK_RETURN)
			{
				Screen_flag = 2;
				SetTimer(hWnd, TIMER1, 1, NULL);
				SetTimer(hWnd, TIMER2, 500, NULL);
				HideCaret(hWnd);
				DestroyCaret();

				game.make_Wall(rectview, 100, 50);
				game.make_Cannon(rectview, 50, 50);
			}
			else
			{
				if (ID_itr == 14)
					break;
				game.set_ID()[ID_itr] = wParam;
				ID_itr++;
			}
		}
		else if (Screen_flag == 2)
		{
			if (wParam == VK_LEFT)
				game.MoveCannon(false);
			else if (wParam == VK_RIGHT)
				game.MoveCannon(true);
			else if (wParam == VK_SPACE)
				game.ShootCannon(5);
		}
		else if (Screen_flag == 3)
		{
			if (wParam == VK_RETURN)
				exit(0);
		}

		InvalidateRect(hWnd, NULL, true);



	}
	break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
			if (Screen_flag == 1)
			{
				game.ID_Screen(hdc, rectview, size);
			}
			else if (Screen_flag == 2)
			{
				game.Game_Screen(hdc, rectview);
			}
			else if (Screen_flag == 3)
			{
				game.Record_Screen(hdc, rectview, name, score);
			}


            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
		KillTimer(hWnd, 1);
        PostQuitMessage(0);
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
