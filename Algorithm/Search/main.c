#include"Sequential.h"

int main() {
	struct sstable *stable = (struct sstable *) malloc(sizeof(struct sstable));
	stable->table = (struct elem*) malloc(MAX * sizeof(struct elem));
	stable->len = 0;

	const char *path = "./data.txt";
	ReadFile(stable, path);
	Show(FindByID(stable, "2010"));
	Show(FindByName(stable, "luosongchao"));
	return 0;
}
