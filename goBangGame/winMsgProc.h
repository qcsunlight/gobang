#pragma once  
#include <Windows.h>  

// 处理绘图消息  
void WINAPI OnRedraw(HDC hdc);

// 处理鼠标指针移动消息  
void WINAPI OnMouseMove(HWND hWnd, int x, int y);

// 处理鼠标左键按下消息  
void WINAPI OnMouseLButtonDown(HWND hWnd, int x, int y);

// 处理鼠标右键按下消息  
void WINAPI OnMouseRButtonDown(HWND hWnd, int x, int y);
