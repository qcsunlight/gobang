#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include "Console.h"
#include "goBangList.h"


// 全局变量
POINT po = { -50, -50 };
POINT luoPo = {-1,-1};
void onRedraw(HDC);
typedef enum {
	Nothing = 0,
	Ldown = 1,
	Rdown = 2
}BUTON_STATUS;
static BUTON_STATUS bs = Nothing;
int gobang[15][15] = { Nothing };
bool judge();
void view();
gbNode *gblist;
void win_or_lose(int data[15][15], int x, int y);
void winjudge(int, int);
// 全局变量

BOOLEAN InitWindowClass(HINSTANCE hInstance, int nCmdShow);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc = NULL;
	RECT clientRect;
	PAINTSTRUCT ps;
	//ps.hdc = hdc;
	//ps.fErase = true;
	//ps.rcPaint = rcp;
	HPEN hp;
	HBRUSH hb;
	RECT *lp = NULL;
	WORD x=50, y=50;
	int flag = 1;
	int clienthight,clientwidth,goBangwidth;

	switch (message)
	{
	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);
		GetClientRect(hWnd, &clientRect);
		/*if ((clientRect.right - clientRect.left) < 300 || (clientRect.bottom - clientRect.top) < 300)\
		{
			MessageBox(hWnd, L"窗口尺寸太小", L"错误", 0);
			break;
		}*/

		hp = (HPEN)GetStockObject(BLACK_PEN);
		hb = CreateSolidBrush(RGB(255, 202, 0));
		SelectObject(hdc, hp);
		Rectangle(hdc, clientRect.left + 10, clientRect.top + 10, clientRect.right - 10, clientRect.bottom - 10);
		MoveToEx(hdc, (clientRect.left + clientRect.right) * 3 / 4, clientRect.top + 10, NULL);
		LineTo(hdc, (clientRect.left + clientRect.right) * 3 / 4, clientRect.bottom - 10);
		SelectObject(hdc, hb);
		Rectangle(hdc, clientRect.left + 16, clientRect.top + 16, (clientRect.left + clientRect.right) * 3 / 4 - 6, clientRect.bottom - 16);
		hb = CreateSolidBrush(RGB(201, 218, 248));
		SelectObject(hdc, hb);
		Rectangle(hdc, (clientRect.left + clientRect.right) * 3 / 4 + 6, clientRect.top + 16, clientRect.right - 16, clientRect.bottom - 16);

		clientwidth = ((clientRect.left + clientRect.right) * 3 / 4 - 6) - (clientRect.left + 16);
		clienthight = (clientRect.bottom - 16) - (clientRect.top + 16);
		goBangwidth = 40;
		for (int i = 0; i < 15; i++)
		{
			MoveToEx(hdc, clientRect.left+36, clientRect.top+36+i*goBangwidth, NULL);
			LineTo(hdc, clientRect.left + 36 + 14*goBangwidth, clientRect.top + 36 + i*goBangwidth);
			MoveToEx(hdc, clientRect.left + 36 + i*goBangwidth, clientRect.top + 36, NULL);
			LineTo(hdc, clientRect.left + 36 + i*goBangwidth, clientRect.top + 37 + 14 * goBangwidth);
		}
		hb = (HBRUSH)GetStockObject(BLACK_BRUSH);
		SelectObject(hdc, hb);
		Ellipse(hdc, (clientRect.left + 36 + 3 * goBangwidth - 5), (clientRect.top + 36 + 3 * goBangwidth)-5, clientRect.left + 36 + 3 * goBangwidth + 5, clientRect.top + 36 + 3 * goBangwidth +5);
		Ellipse(hdc, (clientRect.left + 36 + 3 * goBangwidth - 5), (clientRect.top + 36 + 11 * goBangwidth) - 5, clientRect.left + 36 + 3 * goBangwidth + 5, clientRect.top + 36 + 11 * goBangwidth + 5);
		Ellipse(hdc, (clientRect.left + 36 + 11 * goBangwidth - 5), (clientRect.top + 36 + 3 * goBangwidth) - 5, clientRect.left + 36 + 11 * goBangwidth + 5, clientRect.top + 36 + 3 * goBangwidth + 5);
		Ellipse(hdc, (clientRect.left + 36 + 11 * goBangwidth - 5), (clientRect.top + 36 + 11 * goBangwidth) - 5, clientRect.left + 36 + 11 * goBangwidth + 5, clientRect.top + 36 + 11 * goBangwidth + 5);
		onRedraw(hdc);

		/*CreateConsole();
		for (int i = 0; i < 15; i++)
		{
			for (int j = 0; j < 15; j++)
			{
				printf("%d ", gobang[i][j]);
			}
			printf("\n");
		}

		printf("\n******************************\n\n");

		printf("%d  %d\n", luoPo.x, luoPo.y);*/

		EndPaint(hWnd, &ps);
	}
	break;
	case WM_LBUTTONDOWN:
	{
		if (bs == Ldown)
		{
			MessageBox(NULL, L"白棋已下，现在轮到黑棋下！",L"错误", 0);
			break;
		}
		/*if (gobang[luoPo.y][luoPo.x] != 0)
		{
			MessageBox(NULL, L"此位置已经落子，请重新选择位置！", L"错误", 0);
			break;
		}*/
		po.x = (LONG)LOWORD(lParam);
		po.y = (LONG)HIWORD(lParam);
		
		if (!judge())
			break;
		bs = Ldown;
		gblist = add(gblist, luoPo.x, luoPo.y, bs);
		RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE);
		//view();
	}
	break;
	case WM_RBUTTONDOWN:
	{
		if (bs == Rdown)
		{
			MessageBox(NULL, L"黑棋已下，现在轮到白棋下！",L"错误", 0);
			break;
		}
		/*if (gobang[luoPo.y][luoPo.x] != 0)
		{
			MessageBox(NULL, L"此位置已经落子，请重新选择位置！", L"错误", 0);
			break;
		}*/
		po.x = (LONG)LOWORD(lParam);
		po.y = (LONG)HIWORD(lParam);
		
		if (!judge())
			break;
		bs = Rdown;
		gblist = add(gblist, luoPo.x, luoPo.y, bs);
		RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE);
		//view();
		
		/*x = LOWORD(lParam);
		y = HIWORD(lParam);
		hdc = GetDC(hWnd);
		hb = (HBRUSH)GetStockObject(WHITE_BRUSH);
		SelectObject(hdc, hb);
		Ellipse(hdc, x-20,y-20,x+20,y+20);
		ReleaseDC(hWnd, hdc);
		ValidateRect(hWnd, NULL);*/
	}
	break;
	case WM_SIZE:
		RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		FreeConsole();
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}

	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG msg;
	if (!InitWindowClass(hInstance, nCmdShow))
	{
		MessageBox(NULL, L"创建窗口失败！", _T("创建窗口"), NULL);
		return 1;
	}
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return(int)msg.wParam;
}
BOOLEAN InitWindowClass(HINSTANCE hInstance, int nCmdShow)
{
	WNDCLASSEX wc;
	HWND hWnd;
	TCHAR szWindowClass[] = L"goBang";
	TCHAR szTitle[] = L"五子棋";
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = szWindowClass;
	wc.hIconSm = LoadIcon(wc.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

	if (!RegisterClassEx(&wc))
		return FALSE;
	hWnd = CreateWindow(
		szWindowClass,
		szTitle,
		//WS_MINIMIZEBOX | WS_BORDER | WS_SYSMENU,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		852, 680,
		NULL,
		NULL,
		hInstance,
		NULL
		);

	if (!hWnd)
		return FALSE;

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}
void onRedraw(HDC hdc)
{
	/*if (bs == Nothing);
	return;*/
	gbNode *p;
	for (p = gblist; p != NULL; p = p->next)
	{
		if (p->color == Ldown)
		{
			HBRUSH hb = (HBRUSH)GetStockObject(WHITE_BRUSH);
			SelectObject(hdc, hb);
			Ellipse(hdc, p->x * 40 + 36 - 18, p->y * 40 + 36 - 18, p->x * 40 + 36 + 18, p->y * 40 + 36 + 18);
			
		}
		if (p->color == Rdown)
		{
			//wuli_to_luoji(po, luoPo);			
			HBRUSH hb = (HBRUSH)GetStockObject(BLACK_BRUSH);
			SelectObject(hdc, hb);
			Ellipse(hdc, p->x * 40 + 36 - 18, p->y * 40 + 36 - 18, p->x * 40 + 36 + 18, p->y * 40 + 36 + 18);
			//gobang[luoPo.y][luoPo.x] = p->color;
		}
		gobang[p->y][p->x] = p->color;
		win_or_lose(gobang, p->y, p->x);
	}	
}
bool judge()
{
	int xn, yn;
	if ((po.x - 36) % 40 > 20)
	{
		xn = (po.x - 36) / 40 + 1;
	}
	else
	{
		xn = (po.x - 36) / 40;
	}
	if ((po.y - 36) % 40 > 20)
	{
		yn = (po.y - 36) / 40 + 1;
	}
	else
	{
		yn = (po.y - 36) / 40;
	}
	if (xn < 0 || xn>14 || yn < 0 || yn>14)
	{
		MessageBox(NULL, L"无效下棋,请在区域网格内下棋!", L"错误", 0);
		return false;
	}
	if (gobang[yn][xn] != 0)
	{
		MessageBox(NULL, L"此位置已经落子，请重新选择位置！", L"错误", 0);
		return false;
	}
	po.x = xn * 40 + 36;
	po.y = yn * 40 + 36;
	luoPo.x = xn;
	luoPo.y = yn;
	
	return true;
	//view();
}
void view()
{
	CreateConsole();
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			printf("%d ", gobang[i][j]);
		}
		printf("\n");
	}

	printf("\n******************************\n\n");

	printf("%d  %d\n", luoPo.x, luoPo.y);
	//FreeConsole();
	printf("\n******************************\n\n");
	printf("luoPo的坐标及颜色标记！\n");
	printf("\t[%d, %d]\t %d \n", luoPo.x, luoPo.y,bs);
	printf("\n******************************\n\n");

	gbNode *pt;
	for (pt = gblist; pt != NULL; pt = pt->next)
	{
		printf("[%d, %d]  %d\n", pt->x, pt->y, pt->color);
	}
}

void win_or_lose(int data[15][15], int x, int y)
{
	int index, count = 1;
	index = data[x][y];
	//东西搜索
	for (int i = 1; i < 5; i++)
	{
		//west
		if (index == data[x - i][y]&&(x-i)>=0)
			count++;
		if (index == data[x + i][y]&&(x+i)>=0)
			count++;
		winjudge(index, count);
	}
	//上下搜索
	count = 1;
	for (int i = 1; i < 5; i++)
	{
		//west
		if (index == data[x][y-i] && (y - i) >= 0)
			count++;
		if (index == data[x][y+i] && (y + i) >= 0)
			count++;
		winjudge(index, count);
	}

	//左上右下搜索
	count = 1;
	for (int i = 1; i < 5; i++)
	{
		//west
		if (index == data[x - i][y - i] && (y - i) >= 0 && (x - i) >= 0)
			count++;
		if (index == data[x + i][y + i] && (y + i) >= 0 && (x + i) >= 0)
			count++;
		winjudge(index, count);
	}

	//左下右上搜索
	count = 1;
	for (int i = 1; i < 5; i++)
	{
		//west
		if (index == data[x - i][y + i] && (y + i) >= 0 && (x - i) >= 0)
			count++;
		if (index == data[x + i][y - i] && (y - i) >= 0 && (x + i) >= 0)
			count++;
		winjudge(index, count);
	}
}
void winjudge(int index, int count)
{
	if (count == 5)
	{
		if (index == 1)
		{
			MessageBox(NULL, L"白棋赢!", L"结果", 0);
			return;
		}
		if (index == 2)
		{
			MessageBox(NULL, L"黑棋赢!", L"结果", 0);
			return;
		}
	}
}

////GetWindowRect(hWnd, lp);
//hdc=BeginPaint(hWnd, &ps);
////hb = (HBRUSH)GetStockObject(WHITE_BRUSH);
//if (flag == 1)
//{
//	hb = (HBRUSH)GetStockObject(DKGRAY_BRUSH);
//	flag = 2;
//}
//if (flag == 2)
//{
//	hb = (HBRUSH)GetStockObject(WHITE_BRUSH);
//	flag = 1;
//}
//SelectObject(hdc, hb);
//Ellipse(hdc, 50, 50, 150, 150);
////EndPaint(hWnd, &ps);
////RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE);
////hdc = GetDC(hWnd);
//
//SelectObject(hdc, hb);
////setpoint(x, y, po);
//Ellipse(hdc, po.x - 20, po.y - 20, po.x + 20, po.y + 20);
//ReleaseDC(hWnd, hdc);


//clientwidth = ((clientRect.left + clientRect.right) * 3 / 4) - clientRect.left - 22;
//clienthight = (clientRect.bottom - clientRect.top) - 32;
//space = (clientwidth - clienthight) / 2;
//goBangbegin = clientRect.left + 16 + space;
//goBangend = goBangbegin + clienthight;
//goBangwidth = 40;//(goBangend - goBangbegin)/14;
//for (int i = 0; i < 15; i++)
//{
//	MoveToEx(hdc, goBangbegin, (clientRect.top + 20) + i * goBangwidth, NULL);
//	LineTo(hdc, goBangend, (clientRect.top + 20) + i * goBangwidth);
//	MoveToEx(hdc, goBangbegin + i * goBangwidth, clientRect.top + 20, NULL);
//	LineTo(hdc, goBangbegin + i * goBangwidth, clientRect.bottom - 20);
//}