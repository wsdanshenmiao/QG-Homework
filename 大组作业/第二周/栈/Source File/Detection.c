//��ջʵ��ƽ����ŵļ��
#include "StackWithLinkedList.h"
#include "Detection.h"

bool Detection(const char* pc)	//��ջʵ��ƽ����ŵļ��,����ȷ����true�����󷵻�false
{
	assert(pc);
	char* ch = pc;
	Node* stack = l_CreateStack();
	for (; *ch != '\0'; ch++) {
		switch (*ch) {
		case '[':
		case '{':
		case '(':
			l_Push(*ch, stack);	//���ŷ���ʱ��ջ
			break;
		case ']':
		case '}':
			//��շ�����ջ��ʱ�������򣬽�ջԪ�ص����������Ƕ�Ӧ�Ŀ��ŷ��ţ�����
			if (l_IsEmpty(stack)|| l_TopAndPop(stack) + 2 != *ch) {
				l_DisposeStack(stack);
				return false;
			}
			break;
		case ')':
			if (l_IsEmpty(stack) || l_TopAndPop(stack) + 1 != *ch) {
				l_DisposeStack(stack);
				return false;
			}
			break;
		}
	}
	if (l_IsEmpty(stack)) {	//���ļ�β�����ջ�ǿ��򱨴�
		l_DisposeStack(stack);
		return true;
	}
	else {
		l_DisposeStack(stack);
		return false;
	}
}
