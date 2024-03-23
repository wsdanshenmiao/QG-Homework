#include "StackWithArray.h"

struct Array
{
	int m_Capacity;	//���������
	int m_Top;	//ָ��ջ��
	int* m_Array;	//ջ
};

inline bool a_IsEmpty(Array* stack)	//�ж�ջ���Ƿ�Ϊ��
{
	return stack->m_Top == EmptyTOS;
}

inline bool a_IsFull(Array* stack)	//�ж�ջ���Ƿ���
{
	return stack->m_Top + 1 == stack->m_Capacity;
}

Array* a_CreateStack(int num)	//����ջ
{
	Array* stack = (Array*)malloc(sizeof(Array));
	if (stack == NULL) {
		return NULL;
	}
	stack->m_Array = (int*)malloc(sizeof(int) * num);
	if (stack == NULL) {
		return NULL;
	}
	stack->m_Capacity = num;
	stack->m_Top = EmptyTOS;
	return stack;
}

void a_MakeEmpty(Array* stack)	//���ջ������������Ԫ��
{
	assert(stack);
	stack->m_Top = EmptyTOS;
}

Array* a_DisposeStack(Array* stack)	//ɾ������ջ��
{
	assert(stack);
	free(stack->m_Array);
	stack->m_Array = NULL;
	free(stack);
	stack = NULL;
	return stack;
}

void a_Push(int data, Array* stack)	//Ԫ�ؽ�ջ
{
	if (a_IsFull(stack)) {
		return;
	}
	else {
		stack->m_Array[++stack->m_Top] = data;
	}
}

void a_Pop(Array* stack)	//Ԫ�س�ջ
{
	if (a_IsEmpty(stack)) {
		return;
	}
	else {
		stack->m_Top--;
	}
}

int a_Top(Array* stack)	//����ջ��Ԫ��
{
	assert(!a_IsEmpty(stack));
	return stack->m_Array[stack->m_Top];
}

int a_TopAndPop(Array* stack)	//����ջ��Ԫ�ز�����
{
	assert(!a_IsEmpty(stack));
	return stack->m_Array[stack->m_Top--];
}