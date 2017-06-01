// GoBangGame.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "GoBangGame.h"

#define MAX_LOADSTRING 100
#define dbang 15 //棋子的半径大小
#define dge 40 //棋格边长
#define width 24*dge //窗口宽度
#define height 17.5*dge //窗口高度

//标识鼠标状态的枚举量
typedef enum
{
	Nothing = 0,
	BtnDown = 1,
} BUTON_STATUS;

// 保存鼠标位置的结构体, 有x, y两个分量域
static POINT g_pntMouse = { 0, 0 };

// 保存鼠标操作状态
static BUTON_STATUS g_bsL = Nothing;

// 全局变量: 

HCURSOR hCursor;
HBRUSH hb;
HPEN hp;

HINSTANCE hInst;								// 当前实例
TCHAR szTitle[MAX_LOADSTRING];					// 标题栏文本
TCHAR szWindowClass[MAX_LOADSTRING];			// 主窗口类名

// 此代码模块中包含的函数的前向声明: 
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

/**
* 绘制窗体函数
* 参数：hDC, 绘图设备上下文句柄
*/
void WINAPI OnRedrawWindow(HDC hdc, int x, int y)
{
	
	// 输出鼠标指针移动时, 组合键状态
	if (g_bsL != 0)
	{
		if (g_bsL & MK_LBUTTON)
		{
			hb = (HBRUSH)GetStockObject(RGB(100, 100, 0));
			SelectObject(hdc, hb);
			Ellipse(hdc, x - dbang, y + dbang, x + dbang, y - dbang);
		}
		if (g_bsL & MK_RBUTTON)
		{
			hb = (HBRUSH)GetStockObject(BLACK_BRUSH);
			SelectObject(hdc, hb);
			Ellipse(hdc, x - dbang, y + dbang, x + dbang, y - dbang);
		}
	}
}
/**
* 处理鼠标指针移动消息
* 参数：hWnd, 窗口句柄
*	     x, 鼠标指针位置x坐标
*	     y, 鼠标指针位置y坐标
*	     nMark, 组合键状态
*/
void WINAPI OnMouseMove(HWND hWnd, int x, int y)
{
	g_pntMouse.x = x;
	g_pntMouse.y = y;
	RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE);
}
/**
* 处理鼠标左键按下消息
* 参数：hWnd, 窗口句柄
*	     x, 鼠标指针位置x坐标
*	     y, 鼠标指针位置y坐标
*	     nMark, 组合键状态
*/
void WINAPI OnMouseLButtonDown(HWND hWnd, int x, int y)
{
	x = g_pntMouse.x;
	y = g_pntMouse.y;
	g_bsL = BtnDown;
	RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE);
}
/**
* 处理鼠标右键按下消息
* 参数：hWnd, 窗口句柄
*	     x, 鼠标指针位置x坐标
*	     y, 鼠标指针位置y坐标
*	     nMark, 组合键状态
*/
void WINAPI OnMouseRButtonDown(HWND hWnd, int x, int y)
{
	x = g_pntMouse.x;
	y = g_pntMouse.y;
	g_bsL = BtnDown;
	//RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE);
}




int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO:  在此放置代码。
	MSG msg;
	HACCEL hAccelTable;

	// 初始化全局字符串
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_GOBANGGAME, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 执行应用程序初始化: 
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_GOBANGGAME));

	// 主消息循环: 
	while (GetMessage(&msg, NULL, 0, 0))
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
//  函数:  MyRegisterClass()
//
//  目的:  注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GOBANGGAME));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_GOBANGGAME);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   函数:  InitInstance(HINSTANCE, int)
//
//   目的:  保存实例句柄并创建主窗口
//
//   注释: 
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // 将实例句柄存储在全局变量中

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      200, 200, width, height, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  函数:  WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的:    处理主窗口的消息。
//
//  WM_COMMAND	- 处理应用程序菜单
//  WM_PAINT	- 绘制主窗口
//  WM_DESTROY	- 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// 分析菜单选择: 
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
		break;
	case WM_MOUSEMOVE: // 处理鼠标移动消息
		// 可以看到，lParam的低4位(一个short int)为鼠标指针的x坐标，高4位为y坐标
		// wParam为鼠标事件发生时的组合键状态
		OnMouseMove(hWnd, LOWORD(lParam), HIWORD(lParam));
		break;
	case WM_LBUTTONDOWN: // 处理鼠标左键按下消息
		OnMouseLButtonDown(hWnd, g_pntMouse.x, g_pntMouse.y);
		break;
	case WM_RBUTTONDOWN: // 处理鼠标左键按下消息
		OnMouseRButtonDown(hWnd, g_pntMouse.x, g_pntMouse.y);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO:  在此添加任意绘图代码...	
		hp = (HPEN)GetStockObject(BLACK_PEN);
		SelectObject(hdc, hp);
		for (int i = 0; i < 15; i++)
		{
			MoveToEx(hdc, dge, dge + i*dge, NULL);
			LineTo(hdc, 15 * dge, dge + i*dge);
			MoveToEx(hdc, dge + i*dge, dge, NULL);
			LineTo(hdc, dge + i*dge, 15 * dge);
		}
		MoveToEx(hdc, 17.5*dge, 0, NULL);
		LineTo(hdc, 17.5*dge, width);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// “关于”框的消息处理程序。
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
