#include"brackets.h"

#define SIZE 1024

int main() {
	struct stack *brackets = (struct stack *) malloc(sizeof(struct stack));
	brackets->capacity = SIZE;
	brackets->length = 0;
	brackets->array = (char *) malloc(sizeof(SIZE));

	char *string = (char *) malloc(sizeof(SIZE));
	printf("cin:");
	scanf("%s", string);
	int errorlen = 0;	//标记是否出现多个括号结尾符

	while (*string != '\0' && errorlen == 0) {
		switch (*string) {
		case '(':
		case '[':
		case '{':
			Push(brackets, *string);
			printf("push %c\n", *string);
			break;
		case ')':
			if (GetTop(brackets) == '(') {
				printf("pull '('\n");
				Pop(brackets);
			} else {
				errorlen++;
			}
			break;
		case ']':
			if (GetTop(brackets) == '[') {
				printf("pull '['\n");
				Pop(brackets);
			} else {
				errorlen++;
			}
			break;
		case '}':
			if (GetTop(brackets) == '{') {
				printf("pull '{'\n");
				Pop(brackets);
			} else {
				errorlen++;
			}
			break;
		default:
			break;
		}
		string++;
	}

	if (brackets->length == 0 && errorlen == 0) {
		printf("YES");
	} else {
		printf("NO");
	}

	char *array = (char *) malloc(10);
	while (*array != '\0') {
		printf("char:%c\n", *array++);
	}
	return 1;
}
