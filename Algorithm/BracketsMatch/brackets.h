#ifndef BRACKETS_H
#define BRACKETS_H
#include<stdio.h>
#include<stdlib.h>

struct stack {
	int capacity;
	int length;
	char *array;
};

//出栈顶
int Pop(struct stack *brackets);

//返回栈顶元素
char GetTop(struct stack *brackets);

//入栈
int Push(struct stack *brackets, char elem);

#endif
