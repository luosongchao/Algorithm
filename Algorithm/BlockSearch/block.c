#include "block.h"
/**
 *	初始化块表和索引表
 *	bnums 	为块表中的块数
 *	blen[]所有块的长度数组
 *	array[]待搜索元素
 *	length 待搜索元素个数
 */
void InitBlock(struct tblock *blocks, int bnums, int blen[], int array[],
		int length) {
	int i = 0;
	int cur = 0;
	for (; i < bnums; i++) {
		blocks->blockArray[i].len = blen[i];
		blocks->blockArray[i].btable = (int *) malloc(blen[i] * sizeof(int));

		//求块中最大元素位置
		int j = 0;
		int max = 0;
		int mindex = 0;
		for (; j < blen[i] && cur < length; j++) {
			blocks->blockArray[i].btable[j] = array[cur];
			if (array[cur] > max) {
				max = array[cur];
				mindex = cur;
			}
			cur++;
		}
		blocks->blockArray[i].maxvalue = array[mindex];
	}
}

//初始化索引表
void InitIndex(struct tblock *blocks, struct index *indexTable) {
	int *indexArray = (int *) malloc(blocks->bnum * sizeof(int));
	int *array = (int *) malloc(blocks->bnum * sizeof(int));
	int i = 0;
	for (; i < blocks->bnum; i++) {
		array[i] = blocks->blockArray[i].maxvalue;
	}

	//冒泡排序，其中indexArray记录，原数值在排序后数组中的顺序
	Bubble(indexArray, array, blocks->bnum);

	//索引表按照从小大到的顺序建立索引
	i = 0;
	for (; i < indexTable->size; i++) {
		indexTable->bindex[i] = blocks->blockArray[indexArray[i]];
	}
}

//冒泡排序
void Bubble(int indexArray[], int array[], int length) {

	int *temp = (int *) malloc(length * sizeof(int));
	memcpy(temp, array, length * sizeof(int));
	int i = length - 1;

	//记录交换顺序
	for (; i >= 0; i--) {
		indexArray[i] = i;
	}

	i = length - 1;
	//冒泡排序
	for (; i >= 0; i--) {
		int j = 0;
		for (; j < i; j++) {
			if (temp[j] > temp[j + 1]) {
				Swap(&temp[j], &temp[j + 1]);
				Swap(&indexArray[j], &indexArray[j + 1]);
			}
		}
	}
	free(temp);
	temp = NULL;
}

//C语言中交换两整数的位置，使用指针，C语言中没有引用
void Swap(int *a, int *b) {
	int temp = 0;
	temp = *a;
	*a = *b;
	*b = temp;
}

//查询索引表,二分查找
struct block *FindIndex(struct index *indexTable, int value) {
	int low = 0;
	int high = indexTable->size - 1;
	int mid = 0;
	while (low <= high) {
		mid = (low + high) / 2;
		if (indexTable->bindex[mid].maxvalue == value) {
			break;
		} else if (indexTable->bindex[mid].maxvalue > value) {
			high = mid - 1;
		} else {
			low = mid + 1;
		}
	}

	int num = 0;
	if (indexTable->bindex[mid].maxvalue == value) {
		num = mid;
	} else if (indexTable->bindex[mid].maxvalue < value
			&& mid < indexTable->size - 1) {
		num = mid + 1;
	} else {
		num = indexTable->size - 1;
	}
	printf("块号为：%d\n", num);
	return &indexTable->bindex[num];

}

//查询块表
int FindBlock(struct block *elem, int value) {
	int i = 0;
	int exsitValue = 0;
	for (; i < elem->len; i++) {
		if (elem->btable[i] == value) {
			exsitValue = value;
			break;
		}
	}
	return (exsitValue == value) ? 1 : -1;
}

