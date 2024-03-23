#ifndef __POSIFIXNOTATION__H__
#define __POSIFIXNOTATION__H__

#include "StackWithLinkedList.h"
#include <stdio.h>
#include <assert.h>
#include <math.h>

int ConvertCharToInt(char* position, int* pi);	//���ַ���ת��Ϊ����
bool Priority(char operator1, char operator2);	//�ж������������ȼ�
void Calculate(const char operator, Node* const calculateStack);
int PostfixNotation(const char* infix);


#endif // 

