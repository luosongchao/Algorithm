#include"Sequential.h"
#include<fcntl.h>
#include<unistd.h>

/**
 * 顺序查找
 */
struct elem *FindByID(struct sstable *stable, const char *id) {
	struct elem* val = NULL;
	int i = 0;
	for (i = 0; i < stable->len; i++) {
		if (strcmp(stable->table[i].id, id) == 0) {
			val = &(stable->table[i]);
		}
	}
	return val;
}

struct elem *FindByName(struct sstable *stable, const char *name) {
	struct elem* val = NULL;
	int i = 0;
	for (i = 0; i < stable->len; i++) {
		if (strcmp(stable->table[i].name, name) == 0) {
			val = &stable->table[i];
		}
	}
	return val;
}

/**
 * fopen/fclose 是对文件流进行操作
 * 	open/close/create等是系统调用，操作的是文件描述符
 */
void ReadFile(struct sstable *stable, const char *path) {
	FILE *file = fopen(path, "r");
	char buf[MAX];

	if (file != NULL) {
		while (!feof(file)) {
			fgets(buf, MAX, file);	//读取文件的一行

			char *args[5];	//定义了5个字符串元素的数组
			int i = 0;
			for (; i < 5; i++) {
				args[i] = (char *) malloc(20);	//数组中每个元素分配空间
			}

			Split(args, buf, "\t\t");
			AssignStruct(args, stable);
			for (; i < 5; i++) {
				free(args[i]);	//释放数组中每个元素的空间
			}
		}
	}
	fclose(file);
}

void Show(struct elem *val) {
	if (val != NULL) {
		printf("id\t\tname\t\tage\t\tsex\t\tloc\n");
		printf("%s\t\t%s\t\t%s\t\t%s\t\t%s\n", val->id, val->name, val->age,
				val->sex, val->loc);
	} else {
		printf("can't find...");
	}
}

/**
 * 字符串分割函数
 */
void Split(char *args[], char *s, char *delim) {
	char *p;
	p = strtok(s, delim);
	int i = 0;
	while (p) {
		strcpy(args[i++], p);	//strcpy 进行字符串复制
		p = strtok(NULL, delim);
	}
}

void AssignStruct(char *args[], struct sstable *stable) {
	struct elem *val = &stable->table[stable->len++];
	val->id = args[0];
	val->name = args[1];
	val->age = args[2];
	val->sex = args[3];
	val->loc = args[4];
}
