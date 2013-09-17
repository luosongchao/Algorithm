#ifndef SEQUEENTIAL.H
#define SEQUEENTIAL.H
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define  MAX 1024

struct elem {
	char *id;
	char *name;
	char *age;
	char *sex;
	char *loc;
};

struct sstable {
	struct elem *table;
	int len;
};

struct elem *FindByName(struct sstable *table, const char *name);
struct elem *FindByID(struct sstable *table,const  char *id);
void ReadFile(struct sstable *stable, const char *path);
void Split(char *args[], char *s, char *delim);
void AssignStruct(char *args[], struct sstable *stable);
void Show(struct elem *find);
#endif
