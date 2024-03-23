//ʹ������ʵ��ջ
#include "StackWithLinkedList.h"

inline bool l_IsEmpty(Node* stack)	//�ж�ջ�Ƿ�Ϊ��
{
	return stack->m_Next == NULL;
}

Node* l_CreateStack()	//����һ��ջ
{
	Node* stack = (Node*)malloc(sizeof(Node));
	if (!stack) {
		return NULL;
	}
	stack->m_Next = NULL;
	return stack;
}

void l_Push(int data, Node* stack)	//��ջ
{
	Node* tmp = (Node*)malloc(sizeof(Node));
	if (!tmp) {
		return;
	}
	tmp->m_Data = data;
	tmp->m_Next = stack->m_Next;
	stack->m_Next = tmp;
}

void l_Pop(Node* stack)	//��ջ
{
	assert(!l_IsEmpty(stack));
	Node* tmp = stack->m_Next;
	stack->m_Next = tmp->m_Next;
	free(tmp);
	tmp = NULL;
}

void l_MakeEmpty(Node* stack)	//���ջ��
{
	assert(stack);
	while (!l_IsEmpty(stack)) {
		l_Pop(stack);
	}
}

int l_Top(Node* stack)	//����ջ��
{
	assert(!l_IsEmpty(stack));
	return stack->m_Next->m_Data;
}

Node* l_DisposeStack(Node* stack)	//ɾ������ջ
{
	if (!l_IsEmpty(stack)) {
		l_MakeEmpty(stack);
	}
	free(stack);
	stack = NULL;
	return stack;
}

int l_TopAndPop(Node* stack)
{
	assert(!l_IsEmpty(stack));
	int data = stack->m_Next->m_Data;
	Node* tmp = stack->m_Next;
	stack->m_Next = tmp->m_Next;
	free(tmp);
	tmp = NULL;
	return data;
}