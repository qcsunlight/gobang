#pragma once  
#include <Windows.h>  

// �����ͼ��Ϣ  
void WINAPI OnRedraw(HDC hdc);

// �������ָ���ƶ���Ϣ  
void WINAPI OnMouseMove(HWND hWnd, int x, int y);

// ����������������Ϣ  
void WINAPI OnMouseLButtonDown(HWND hWnd, int x, int y);

// ��������Ҽ�������Ϣ  
void WINAPI OnMouseRButtonDown(HWND hWnd, int x, int y);
