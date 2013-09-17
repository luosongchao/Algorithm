#include<stdlib.h>
#include<stdio.h>

int BSearch(int *array, int len, int select);
int compare(const void *a, const void *b);

int main() {
	int array[] = { 10, 12, 33, 43, 52, 32, 9, 10, 21 };
	int len = sizeof(array) / sizeof(array[0]);
	printf("%d\n", BSearch(array, len, 33));
	return 0;
}

/**
 * 二分查找
 */
int BSearch(int *array, int len, int select) {
	qsort(array, len, sizeof(array[0]), compare);	//排序
	int high = len - 1;
	int low = 0;
	int middle = 0;
	while (low <= high) {
		middle = (high + low) / 2;
		if (array[middle] == select) {
			break;
		} else if (array[middle] > select) {
			high = middle - 1;
		} else {
			low = middle + 1;
		}
	}
	printf("high:%d,low:%d,middle:%d\n", high, low, middle);
	return (array[middle] == select) ? array[middle] : -1;
}

int compare(const void *a, const void *b) {
	int *m = (int *) a;
	int *n = (int *) b;
	if (*m > *n) {
		return 1;
	} else {
		return -1;
	}
}
