#include "goBangList.h"

gbNode *add1(gbNode *list, int x, int y, int color)
{
	gbNode *newNode;
	newNode = (gbNode*)malloc(sizeof(gbNode));
	if (newNode == NULL)
	{
		MessageBox(NULL, L"�����ڴ�������", L"����", 0);
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
	gbNode *pInsert; //Ҫ����Ľڵ�  
	gbNode *pMove; //��������Ľڵ�  
	pInsert = (gbNode*)malloc(sizeof(gbNode));
	if (pInsert == NULL) {
		MessageBox(NULL, L"�����ڴ�������", L"����", 0);
		return NULL;
	}

	memset(pInsert, 0, sizeof(gbNode));
	pInsert->x = x;
	pInsert->y = y;
	pInsert->color = color;
	pInsert->next = NULL;

	pMove = pNode;
	if (pNode == NULL) {
		//ע�ⲻҪ�����޸�pMoveָ���ָ�򣬳�ʼpMoveһ��Ҫָ��ͷ�ڵ�  
		pNode = pInsert;
		pMove = pNode;
	}
	else{
		//�����ҵ����һ���ڵ�  
		while (pMove->next != NULL) {
			pMove = pMove->next;
		}
		pMove->next = pInsert;
	}

	pInsert = (gbNode*)malloc(sizeof(gbNode));
	if (pInsert == NULL) {
		MessageBox(NULL, L"�����ڴ�������", L"����", 0);
		return NULL;
	}

	memset(pInsert, 0, sizeof(gbNode));
	pInsert->x = x;
	pInsert->y = y;
	pInsert->color = color;
	pInsert->next = NULL;
	return pNode;
}