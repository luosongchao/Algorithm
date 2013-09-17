#include"binary.h"

int main() {
	struct node *root = (struct node *) malloc(sizeof(struct node));
	char array[] = { 'D', 'B', 'C', 'A', 'G', 'E', 'F' };
	int len = sizeof(array) / sizeof(array[0]);

	InitTree(root, array, len);

	printf("先序输出DLR:\n");
	TraverseDLR(root);
	printf("\n\n");

	printf("中序输出LDR:\n");
	TraverseLDR(root);
	printf("\n\n");

	printf("后序输出LRD:\n");
	TraverseLRD(root);
	printf("\n\n");

	char elem = 'H';
	struct node *selected = FindNode(root, elem);
	if (selected->val == elem) {
		printf("find node:%c\n", selected->val);
	} else {
		printf("find node value '%c' not exsit!\n", elem);
	}

	return 1;
}
