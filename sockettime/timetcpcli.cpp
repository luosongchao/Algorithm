/*

 * timetcpcli.c
 *
 *  Created on: 2013年9月6日
 *      Author: luosongchao


#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include <string>
#include <cstdio>
#include <arpa/inet.h>

using namespace std;
#define MAXLINE 4096

int main(int argc, char **argv) {
	int sockfd, n;
	char recv[MAXLINE];
	struct sockaddr_in servaddr;
	if (argc != 2) {
		cout << "usage:a.out <IP>" << endl;
		return -1;
	}

	//创建socket
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
		cout << "create socket error!" << endl;
		return -1;
	}

	//初始化服务器端口信息
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(50000);

	//inet_pton将点分十进制的IP地址，转换为数值，头文件<arpa/inet.h>
	if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0) {
		cout << "inet_pton error!" << endl;
		return -1;
	}

	//客户端连接服务器
	if (connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0) {
		cout << "connect error!" << endl;
		return -1;
	}

	//读取服务器端发送的数据
	while ((n = read(sockfd, recv, MAXLINE)) > 0) {
		recv[n] = 0;

		//这里使用fputs输出到stdout，需要添加头文件<cstdio>
		if (fputs(recv, stdout) == EOF) {
			cout << "fputs error!" << endl;
		}
	}
}

*/
