#include"binary.h"

/**
 * 实现一颗二叉查找树
 */

//初始化一颗二叉排序树
void InitTree(struct node *root, char *array, int len) {
	int i = 0;
	root->val = array[0];
	for (i = 1; i < len; i++) {
		struct node *p = root;
		struct node *find = FindNode(p, array[i]);	//找出该值需要插入的位置
		int value = strcmp(&find->val, &array[i]);
		if (value == 0) {
			continue;
		} else if (value > 0) {
			//新建一个节点，作为FindNode返回节点的lchild
			struct node *temp = (struct node *) malloc(sizeof(struct node));
			find->lchild = temp;
			temp->lchild = NULL;
			temp->rchild = NULL;
			temp->val = array[i];
		} else {
			//新建一个节点，作为FindNode返回节点的rchild
			struct node *temp = (struct node *) malloc(sizeof(struct node));
			find->rchild = temp;
			temp->lchild = NULL;
			temp->rchild = NULL;
			temp->val = array[i];
		}
	}
}

//查找指定节点，如果存在返回节点，否则返回叶子节点
struct node *FindNode(struct node *root, int value) {
	struct node *cur = root;
	struct node *parent = cur;

//叶子节点或者遇到相同的节点跳出while
	while (cur != NULL) {
		if (cur->val > value) {
			parent = cur;
			cur = cur->lchild;
		} else if (cur->val < value) {
			parent = cur;
			cur = cur->rchild;
		} else {
			break;
		}
	}

	//如果遇到相同的值，返回当前节点，否则返回父节点（叶子节点）
	if (cur != NULL) {
		return cur;
	} else {
		return parent;
	}
}

//返回二叉树的根节点
struct node *GetRoot(struct node *tree) {
	return tree;
}

//中序遍历
void TraverseLDR(struct node *tree) {
	struct node *p = tree;
	if (p->lchild != NULL) {
		TraverseLDR(p->lchild);
	}
	printf("%c\t", p->val);
	if (p->rchild != NULL) {
		TraverseLDR(p->rchild);
	}
}

//先序遍历
void TraverseDLR(struct node *tree) {
	struct node *p = tree;
	printf("%c\t", p->val);
	if (p->lchild != NULL) {
		TraverseDLR(p->lchild);
	}

	if (p->rchild != NULL) {
		TraverseDLR(p->rchild);
	}
}

//后序遍历
void TraverseLRD(struct node *tree) {
	struct node *p = tree;
	if (p->lchild != NULL) {
		TraverseLRD(p->lchild);
	}
	if (p->rchild != NULL) {
		TraverseLRD(p->rchild);
	}
	printf("%c\t", p->val);
}
