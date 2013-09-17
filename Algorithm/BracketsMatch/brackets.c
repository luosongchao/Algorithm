#include"brackets.h"

//入栈
int Push(struct stack *brackets, char elem) {
	int value = 0;
	if (brackets->capacity > brackets->length) {
		brackets->array[brackets->length++] = elem;
	} else {
		printf("stack full,auto increase...\n");
		//增加自动扩展stack
		value = -1;
	}
	return value;
}

//返回栈顶元素
char GetTop(struct stack *brackets) {
	if (brackets->length > 0) {
		return brackets->array[brackets->length - 1];
	} else {
		return '\0';
	}
}

//出栈
int Pop(struct stack *brackets) {
	int value = 0;
	if (brackets->length == 0) {
		printf("stack empty!");
		return -1;
	} else {
		value = (int) brackets->array[brackets->length - 1];
		brackets->array[brackets->length - 1] = '\0';	//删除栈顶
		brackets->length--;
	}
	return value;
}
