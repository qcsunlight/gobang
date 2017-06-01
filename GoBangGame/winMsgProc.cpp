#include <tchar.h>  
#include <stdio.h>  

#include "winMsgProc.h"  

#define LEFT_SIDE 20  
#define TOP_SIDE 10  

// 标识鼠标状态的枚举量  
typedef enum
{
	Nothing = 0,    // 鼠标无状态  
	LBtnDown = 1,   // 鼠标左键被按下  
	RBtnDown = 2,   // 鼠标右键被按下
} BUTON_STATUS;

// 保存在操作鼠标按键时, 鼠标指针的位置  
static POINT g_pntL = { 0, 0 };

// 保存鼠标操作状态  
static BUTON_STATUS g_bsL = Nothing;

/**
* 绘制窗体函数
* 参数：hdc, 绘图设备上下文句柄
*/
void WINAPI OnRedrawWindow(HDC hdc)
{
	
}

/**
* 处理鼠标左键按下消息
* 参数：hWnd, 窗口句柄
*       x, 鼠标指针位置x坐标
*       y, 鼠标指针位置y坐标
*       nMark, 组合键状态
*/
void WINAPI OnMouseLButtonDown(HWND hWnd, int x, int y, int nMark)
{
	g_pntL.x = x;
	g_pntL.y = y;
	g_bsL = LBtnDown;
	RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE);
}
/**
* 处理鼠标右键按下消息
* 参数：hWnd, 窗口句柄
*       x, 鼠标指针位置x坐标
*       y, 鼠标指针位置y坐标
*/
void WINAPI OnMouseLButtonDown(HWND hWnd, int x, int y)
{
	g_pntL.x = x;
	g_pntL.y = y;
	g_bsL = RBtnDown;
	RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE);
}
