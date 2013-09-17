#ifndef BLOCK_H
#define BLOCK_H
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//块的定义
struct block {
	int len;	//块中元素个数
	int *btable;	//块中元素值
	int maxvalue;	//块中元素的最大值
};

//块表
struct tblock {
	int bnum;	//块个数
	struct block *blockArray;
};

//分块索引表的定义
struct index {
	int size;	//块的个数
	struct block *bindex;	//指向块的指针
};

//初始化块表
void InitBlock(struct tblock *blocks, int bnums, int blen[], int array[],
		int length);

//初始化索引表
void InitIndex(struct tblock *blocks, struct index *indexTable);

//冒泡排序
void Bubble(int indexArray[], int array[], int length);

//交换a和b的顺序
void Swap(int *a, int *b);

//查询索引表
struct block *FindIndex(struct index *indexTable, int value);

//查询块表
int FindBlock(struct block *elem, int value);

#endif
