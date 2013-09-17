#include<iostream>
#include<cstdlib>
#include<string.h>
using namespace std;
using std::string;

/**
 * 史上最长最醒目的队名 返回比赛首页Problem Description
 Jack所在的班级决定组团报名参加FZU校赛。为了体现班级的团结和睦，班长决定用班级所有人的名字连起来组成一个
 史上最长最醒目的队名。因为听说在分数相同的情况下，队名字典序小的会排在更前面，班长还希望连成的史上最长队名
 拥有最小的字典序。Input 输入数据第一行包含一个整数T，表示测试数据的组数。对于每组测试数据：
 	 第一行为一个整数(10000>=n>0)，表示班级成员数。 接下来n行为班级每个人的名字。
 	 名字由小写字母组成,每个人名字长度均相同。Output 对于每组测试数据，输出一行，
 	 表示连接成的史上最长队名。
 Sample Input
 1
 3
 jim
 tom
 joe

 Sample Output
 jimjoetom
 */
void SortDictionary(string *array, int row, int col, string *result);
void Sort(string *array, int col, string *result);
int compare(const void *a, const void *b);

int main() {
	int row;
	int col;
	//cout << "row:";
	cin >> row;
	//cout << "col:";
	cin >> col;
	string *array = new string[row * col];
	//string (*parray)[col] = (string (*)[col])array;	//一维数组转换二维数组
	int i = 0;
	for (; i < row; i++) {
		int j = 0;
		for (; j < col; j++) {
			//cout << "array[" << i << "][" << j << "]=";
			cin >> *(array + i * col + j);
		}
	}

	string *result = new string[row];
	SortDictionary(array, row, col, result);

	i = 0;
	for (; i < row; i++) {
		//cout << "result[" << i << "]=" << result[i] << endl;
		cout << result[i] << endl;
	}
}

/**
 * 二维数组按组进行字典排序
 */
void SortDictionary(string *array, int row, int col, string *result) {
	int i = 0;
	for (; i < row; i++) {
		string *value = new string();
		Sort(array + i * col, col, value);
		//cout << *value << endl;
		result[i] = *value;
	}
}

/**
 * string数组字典排序
 */
void Sort(string *array, int col, string *value) {
	string *p = array;
	qsort(p, col, sizeof(string), compare);
	string temp = "";
	int i = 0;
	for (; i < col; i++) {
		//cout << "string[" << i << "]=" << array[i] << "\n";
		temp += array[i];
	}
	*value = temp;
}

/**
 * 比较函数
 */
int compare(const void *a, const void *b) {
	string *aa = (string *) a;
	string *bb = (string *) b;
	const char * achr = (*aa).c_str();
	const char *bchr = (*bb).c_str();
	return strcmp(achr, bchr);
}
