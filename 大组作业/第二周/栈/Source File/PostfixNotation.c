//��ջʵ�ֺ�׺���ʽ�ļ������׺���ʽת���ɺ�׺���ʽ,ֻ��������
#include "PostfixNotation.h"


int ConvertCharToInt(char* position, int* const pi)	//���ַ���ת��Ϊ����
{
	int ret = 0;
	char ch = *position;
	while ('0' <= ch && ch <= '9') {
		ret = ret * 10 + ch - '0';
		position++;
		ch = *position;
		(*pi)++;
	}
	return ret;
}

//operator1��operator2�߻���ȷ���true
bool Priority(char operator1, char operator2)	//�ж������������ȼ�
{
	switch (operator1) {
	case '(':
	case ')':
		return true;
	case '*':
	case '/':
		if (operator2 == '(' || operator2 == ')') {
			return false;
		}
		else {
			return true;
		}
	case '+':
	case '-':	//ͬ����ʱ��ǰ�����ȼ���
		//if (operator2 == '+' || operator2 == '-') {
		//	return true;
		//}
		return false;
	}
	printf("error in label");
	exit(EXIT_FAILURE);
}

void Calculate(const char operator, Node* const calculateStack)
{
	int num1 = l_TopAndPop(calculateStack);
	int num2 = l_TopAndPop(calculateStack);
	switch (operator) {
	case '+':
		l_Push(num2 + num1, calculateStack);
		break;
	case '-':
		l_Push(num2 - num1, calculateStack);
		break;
	case '*':
		l_Push(num2 * num1, calculateStack);
		break;
	case '/':
		l_Push(num2 / num1, calculateStack);
		break;
	}
}

int PostfixNotation(const char* infix)
{
	Node* convertStack = l_CreateStack();	//����ת����ջ
	Node* calculateStack = l_CreateStack();	//������������ջ
	int i = 0;
	for (char ch = *(infix + i); ch != '\0'; i++, ch = *(infix + i)) {
		if (ch == ' ') {	//��ȥ�ո�
			continue;
		}
		else if ('0' <= ch && ch <= '9') {	//��Ϊ����
			//�������ַ�ת��Ϊ����,�������ջ
			l_Push(ConvertCharToInt(infix + i, &i) , calculateStack);
			i--;	//�������Ѿ��������������ַ����������ȥ����ѭ����ӵ�һ��
		}
		else if (ch == ')') {
			while (!l_IsEmpty(convertStack) && l_Top(convertStack) != '(') {
				Calculate(l_TopAndPop(convertStack), calculateStack);	//����������������
			}
			if (l_IsEmpty(convertStack)) {	//��Ϊ����û��'('��������Ŵ����쳣�˳�
				printf("error in label");
				exit(EXIT_FAILURE);

			}
			else {	//��ǰ����'('����������������
				l_Pop(convertStack);
			}
		}
		else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '(') {	//��Ϊ�������
			if (l_IsEmpty(convertStack)) {
				l_Push(ch, convertStack);
			}
			else if (Priority(ch, l_Top(convertStack))) {	//��ջ�����ȼ��ͣ���ջ
				l_Push(ch, convertStack);
			}
			else {	//��֮����������ջ����
				//ע������Ҫ���ж��Ƿ�Ϊ�գ�������Ƚ��з���ջ����������Ϊ�վͻᱨ��
				while (!l_IsEmpty(convertStack) && l_Top(convertStack) != '(') {
					Calculate(l_TopAndPop(convertStack), calculateStack);
				}
				l_Push(ch, convertStack);
			}
		}
		else {
			printf("error in label");
			exit(EXIT_FAILURE);
		}
	}
	while (!l_IsEmpty(convertStack)) {	//�����з��ŵ���
		Calculate(l_TopAndPop(convertStack), calculateStack);
	}
	int ret = calculateStack->m_Next->m_Data;	//���ؼ���ջ�����Ľ��
	convertStack = l_DisposeStack(convertStack);
	calculateStack = l_DisposeStack(calculateStack);
	return ret;
}