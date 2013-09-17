/*
#include <unistd.h>
#include <cstdio>
#include <cstring>
#include <string>

#include <ctime>
#include<iostream>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<arpa/inet.h>

using namespace std;
#define MAXLINE 4096
#define LISTENQ 1024

int main() {
	int listenfd, connfd;
	struct sockaddr_in servaddr;	//头文件<netinet/in.h>
	struct sockaddr_in client;
	socklen_t len;
	char buf[MAXLINE];
	time_t ticks;

	//建立一个socket
	listenfd = socket(AF_INET, SOCK_STREAM, 0);	//头文件<sys/socket.h>
	if (listenfd < 0) {
		cout << "create socket error!" << endl;
		return -1;
	}

	//初始化服务器端口信息
	memset(&servaddr, 0, sizeof(servaddr));	//头文件<string.h>
	memset(&client, 0, sizeof(client));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(30000);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	//socket绑定本地端口
	bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));

	//服务器监听客户端请求
	listen(listenfd, LISTENQ);	//listen 设置监听socket以及监听数量

	while (true) {
		//接受客户端连接请求
		//connfd = accept(listenfd, (struct sockaddr *) NULL, NULL);
		len = sizeof(client);
		connfd = accept(listenfd, (struct sockaddr *) &client, &len);
		if (connfd == -1) {
			cout << "accept error!" << endl;
			continue;
		}
		//获取已连接客户端端口信息
		char buff[1024];
		inet_ntop(AF_INET, &client.sin_addr, buff, sizeof(buff));
		int port = ntohs(client.sin_port);
		cout << "accept client...address:" << buff << "  port:" << port << endl;

		ticks = time(NULL);
		snprintf(buf, sizeof(buf), "%.24s\r\n", ctime(&ticks));

		//服务器端向客户端发送数据
		write(connfd, buf, strlen(buf));
		close(connfd);
	}

}
*/
