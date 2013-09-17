/*
 * timetcpcli.c
 *
 *  Created on: 2013年9月6日
 *      Author: luosongchao
 */

#include <arpa/inet.h>
#include <libio.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>

using namespace std;
#define MAXLINE 4096
void ClientEcho(int sockfd);

int main(int argc, char **argv) {
	int sockfd;
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
	ClientEcho(sockfd);
	close(sockfd);
	exit(0);
}

//客户端处理函数
void ClientEcho(int sockfd) {
	char buf[MAXLINE];
	int maxfdpl;		//指定待测试的描述字的个数，它的值是待测试的最大描述字加1

	/**
	 * select描述字集，典型的是一个整数数组，每个整数中的每一位对应一个描述字
	 * 举例来说，假设使用一个32位整数，那么该数组的第一个元素对应于描述字0-31，第二个对应于
	 * 32-63，以此类推。
	 */
	fd_set rset;

	//描述字集中任何与未就绪的描述字对应的位返回时均清0，为此每次重新调用
	//select函数时，我们都得再次把所有描述字集中所关心的位设置为1
	for (;;) {
		FD_ZERO(&rset);		//描述字集初始化，必不可少（自动变量）
		FD_SET(sockfd, &rset);

		//fileno()函数，将标准I/O文件指针转换为对应的描述字
		FD_SET(fileno(stdin), &rset);
		maxfdpl = max(fileno(stdin), sockfd) + 1;

		/**
		 * 进程受阻于select调用，等待可能多个套接口中的任一个变成可读
		 * 		select函数最后一个参数是时间：它告知内核等待所指定的描述字中任一个
		 * 就绪可花多长时间。
		 *
		 * 		调用select，指定所关心的描述字的值，函数返回结果指哪些描述字已就绪
		 * 函数返回后，我们使用FD_ISSET宏测试fd_set中描述字。
		 *
		 * 		select函数返回值：
		 * 		  就绪描述字的正数目，0超时，-1出错
		 */
		int ready = select(maxfdpl, &rset, NULL, NULL, NULL);
		cout << "ready count:" << ready << endl;

		//stdin就绪
		if (FD_ISSET(fileno(stdin),&rset)) {
			if (fgets(buf, MAXLINE, stdin) == NULL) {
				return;
			}
			write(sockfd, buf, strlen(buf));
		}

		memset(buf, 0, MAXLINE);

		//socket 就绪
		if (FD_ISSET(sockfd,&rset)) {
			if (read(sockfd, buf, MAXLINE) == 0) {
				cout << "server terminated prematurely!" << endl;
				return;
			}
			cout << "client get:" << buf << endl;
		}
	}
}

