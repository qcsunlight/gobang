#include "goBangList.h"

gbNode *add1(gbNode *list, int x, int y, int color)
{
	gbNode *newNode;
	newNode = (gbNode*)malloc(sizeof(gbNode));
	if (newNode == NULL)
	{
		MessageBox(NULL, L"链表内存分配错误！", L"错误", 0);
		exit(1);
	}
	newNode->x = x;
	newNode->y = y;
	newNode->color = color;
	newNode->next = list;
	return newNode;
}
gbNode *add(gbNode *pNode, int x, int y, int color)
{
	gbNode *pInsert; //要插入的节点  
	gbNode *pMove; //遍历链表的节点  
	pInsert = (gbNode*)malloc(sizeof(gbNode));
	if (pInsert == NULL) {
		MessageBox(NULL, L"链表内存分配错误！", L"错误", 0);
		return NULL;
	}

	memset(pInsert, 0, sizeof(gbNode));
	pInsert->x = x;
	pInsert->y = y;
	pInsert->color = color;
	pInsert->next = NULL;

	pMove = pNode;
	if (pNode == NULL) {
		//注意不要忘了修改pMove指针的指向，初始pMove一定要指向头节点  
		pNode = pInsert;
		pMove = pNode;
	}
	else{
		//遍历找到最后一个节点  
		while (pMove->next != NULL) {
			pMove = pMove->next;
		}
		pMove->next = pInsert;
	}

	pInsert = (gbNode*)malloc(sizeof(gbNode));
	if (pInsert == NULL) {
		MessageBox(NULL, L"链表内存分配错误！", L"错误", 0);
		return NULL;
	}

	memset(pInsert, 0, sizeof(gbNode));
	pInsert->x = x;
	pInsert->y = y;
	pInsert->color = color;
	pInsert->next = NULL;
	return pNode;
}