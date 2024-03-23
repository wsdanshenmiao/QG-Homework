#ifndef __STACKWITHARRAY__H__
#define __STACKWITHARRAY__H__

#define EmptyTOS (-1)

#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

typedef struct Array Array;
inline bool a_IsEmpty(Array* stack);	//�ж�ջ���Ƿ�Ϊ��
inline bool a_IsFull(Array* stack);	//�ж�ջ���Ƿ���
Array* a_CreateStack(int num);	//����ջ
void a_MakeEmpty(Array* stack);	//���ջ������������Ԫ��
Array* a_DisposeStack(Array* stack);	//ɾ������ջ��
void a_Push(int data, Array* stack);	//Ԫ�ؽ�ջ
void a_Pop(Array* stack);	//Ԫ�س�ջ
int a_Top(Array* stack);	//����ջ��Ԫ��
int a_TopAndPop(Array* stack);	//����ջ��Ԫ�ز�����

#endif // !__STACKWITHARRAY__H__
