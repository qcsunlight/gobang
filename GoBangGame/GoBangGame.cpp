// GoBangGame.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "GoBangGame.h"

#define MAX_LOADSTRING 100
#define dbang 15 //���ӵİ뾶��С
#define dge 40 //���߳�
#define width 24*dge //���ڿ��
#define height 17.5*dge //���ڸ߶�

//��ʶ���״̬��ö����
typedef enum
{
	Nothing = 0,
	BtnDown = 1,
} BUTON_STATUS;

// �������λ�õĽṹ��, ��x, y����������
static POINT g_pntMouse = { 0, 0 };

// ����������״̬
static BUTON_STATUS g_bsL = Nothing;

// ȫ�ֱ���: 

HCURSOR hCursor;
HBRUSH hb;
HPEN hp;

HINSTANCE hInst;								// ��ǰʵ��
TCHAR szTitle[MAX_LOADSTRING];					// �������ı�
TCHAR szWindowClass[MAX_LOADSTRING];			// ����������

// �˴���ģ���а����ĺ�����ǰ������: 
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

/**
* ���ƴ��庯��
* ������hDC, ��ͼ�豸�����ľ��
*/
void WINAPI OnRedrawWindow(HDC hdc, int x, int y)
{
	
	// ������ָ���ƶ�ʱ, ��ϼ�״̬
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
* �������ָ���ƶ���Ϣ
* ������hWnd, ���ھ��
*	     x, ���ָ��λ��x����
*	     y, ���ָ��λ��y����
*	     nMark, ��ϼ�״̬
*/
void WINAPI OnMouseMove(HWND hWnd, int x, int y)
{
	g_pntMouse.x = x;
	g_pntMouse.y = y;
	RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE);
}
/**
* ����������������Ϣ
* ������hWnd, ���ھ��
*	     x, ���ָ��λ��x����
*	     y, ���ָ��λ��y����
*	     nMark, ��ϼ�״̬
*/
void WINAPI OnMouseLButtonDown(HWND hWnd, int x, int y)
{
	x = g_pntMouse.x;
	y = g_pntMouse.y;
	g_bsL = BtnDown;
	RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE);
}
/**
* ��������Ҽ�������Ϣ
* ������hWnd, ���ھ��
*	     x, ���ָ��λ��x����
*	     y, ���ָ��λ��y����
*	     nMark, ��ϼ�״̬
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

 	// TODO:  �ڴ˷��ô��롣
	MSG msg;
	HACCEL hAccelTable;

	// ��ʼ��ȫ���ַ���
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_GOBANGGAME, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ִ��Ӧ�ó����ʼ��: 
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_GOBANGGAME));

	// ����Ϣѭ��: 
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
//  ����:  MyRegisterClass()
//
//  Ŀ��:  ע�ᴰ���ࡣ
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
//   ����:  InitInstance(HINSTANCE, int)
//
//   Ŀ��:  ����ʵ�����������������
//
//   ע��: 
//
//        �ڴ˺����У�������ȫ�ֱ����б���ʵ�������
//        ��������ʾ�����򴰿ڡ�
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // ��ʵ������洢��ȫ�ֱ�����

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
//  ����:  WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  Ŀ��:    ���������ڵ���Ϣ��
//
//  WM_COMMAND	- ����Ӧ�ó���˵�
//  WM_PAINT	- ����������
//  WM_DESTROY	- �����˳���Ϣ������
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
		// �����˵�ѡ��: 
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
	case WM_MOUSEMOVE: // ��������ƶ���Ϣ
		// ���Կ�����lParam�ĵ�4λ(һ��short int)Ϊ���ָ���x���꣬��4λΪy����
		// wParamΪ����¼�����ʱ����ϼ�״̬
		OnMouseMove(hWnd, LOWORD(lParam), HIWORD(lParam));
		break;
	case WM_LBUTTONDOWN: // ����������������Ϣ
		OnMouseLButtonDown(hWnd, g_pntMouse.x, g_pntMouse.y);
		break;
	case WM_RBUTTONDOWN: // ����������������Ϣ
		OnMouseRButtonDown(hWnd, g_pntMouse.x, g_pntMouse.y);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO:  �ڴ���������ͼ����...	
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

// �����ڡ������Ϣ�������
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
