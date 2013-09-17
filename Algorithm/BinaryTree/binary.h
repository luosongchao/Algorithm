#ifndef BINARY_H
#define BINARY_H

#include<stdlib.h>
#include<stdio.h>
#include<string.h>

/**
 * 实现一颗二叉查找树
 */
struct node {
	char val;
	struct node *lchild;
	struct node *rchild;
};

//初始化一颗二叉树
void InitTree(struct node *tree, char *array, int len);

//查找指定节点,不存在该值节点则返回叶子节点
struct node *FindNode(struct node *root, int value);

//返回二叉树的根节点
struct node *GetRoot(struct node *tree);

//遍历输出二叉树——中序
void TraverseLDR(struct node *tree);

//遍历输出二叉树——先序
void TraverseDLR(struct node *tree);

//遍历输出二叉树——后序
void TraverseLRD(struct node *tree);

#endif
