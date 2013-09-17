#include"block.h"

int main() {

	//块表初始化
	struct tblock *blocks = (struct tblock *) malloc(sizeof(struct tblock));
	int num = 3;
	blocks->bnum = num;	//块个数
	blocks->blockArray = (struct block *) malloc(sizeof(struct block) * num);

	//索引表初始化
	struct index *indexTable = (struct index *) malloc(sizeof(struct index));
	indexTable->size = num;
	indexTable->bindex = (struct block *) malloc(sizeof(struct block) * num);

	//初始数据
	int array[] = { 22, 12, 13, 8, 9, 20, 33, 38, 44, 48, 24, 60, 86, 74, 79 };
	int blen[] = { 6, 6, 3 };
	int length = sizeof(array) / sizeof(array[0]);

	//初始化索引块
	InitBlock(blocks, num, blen, array, length);

	//初始化索引表
	InitIndex(blocks, indexTable);

	int value = 76;

	//查找索引表
	struct block *choosen = FindIndex(indexTable, value);

	//查找块表
	if (FindBlock(choosen, value) == 1) {
		printf("find\n");
	} else {
		printf("not exsit!\n");
	}
	return 1;
}
