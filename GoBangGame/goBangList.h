#pragma once

#include <Windows.h>
#include <stdlib.h>

typedef struct node
{
	int x;
	int y;
	int color;
	struct node *next;
}gbNode;

gbNode *add1(gbNode *list, int x, int y, int color);

gbNode *add(gbNode *pNode, int x, int y, int color);