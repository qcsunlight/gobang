#include <tchar.h>  
#include <stdio.h>  

#include "winMsgProc.h"  

#define LEFT_SIDE 20  
#define TOP_SIDE 10  

// ��ʶ���״̬��ö����  
typedef enum
{
	Nothing = 0,    // �����״̬  
	LBtnDown = 1,   // ������������  
	RBtnDown = 2,   // ����Ҽ�������
} BUTON_STATUS;

// �����ڲ�����갴��ʱ, ���ָ���λ��  
static POINT g_pntL = { 0, 0 };

// ����������״̬  
static BUTON_STATUS g_bsL = Nothing;

/**
* ���ƴ��庯��
* ������hdc, ��ͼ�豸�����ľ��
*/
void WINAPI OnRedrawWindow(HDC hdc)
{
	
}

/**
* ����������������Ϣ
* ������hWnd, ���ھ��
*       x, ���ָ��λ��x����
*       y, ���ָ��λ��y����
*       nMark, ��ϼ�״̬
*/
void WINAPI OnMouseLButtonDown(HWND hWnd, int x, int y, int nMark)
{
	g_pntL.x = x;
	g_pntL.y = y;
	g_bsL = LBtnDown;
	RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE);
}
/**
* ��������Ҽ�������Ϣ
* ������hWnd, ���ھ��
*       x, ���ָ��λ��x����
*       y, ���ָ��λ��y����
*/
void WINAPI OnMouseLButtonDown(HWND hWnd, int x, int y)
{
	g_pntL.x = x;
	g_pntL.y = y;
	g_bsL = RBtnDown;
	RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE);
}
