#include <csignal>

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
#include<cstdlib>
#include<signal.h>
#include<sys/wait.h>

using namespace std;
#define MAXLINE 4096
#define LISTENQ 1024

void ServEcho(int connfd, struct sockaddr_in client);
void Signal(int singno);

int main() {
	int listenfd, connfd;
	struct sockaddr_in servaddr;	//头文件<netinet/in.h>
	struct sockaddr_in client;
	socklen_t len;
	pid_t child;

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
	servaddr.sin_port = htons(50000);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	//socket绑定本地端口
	bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));

	//服务器监听客户端请求
	listen(listenfd, LISTENQ);	//listen 设置监听socket以及监听数量

	//sigchild信号处理，防止客户端断开出现僵死进程
	signal(SIGCHLD, &Signal);

	while (true) {
		//接受客户端连接请求
		//connfd = accept(listenfd, (struct sockaddr *) NULL, NULL);
		len = sizeof(client);
		connfd = accept(listenfd, (struct sockaddr *) &client, &len);

		if (connfd == -1) {
			cout << "accept error!" << endl;
			continue;
		} else {
			//fork进程
			if ((child = fork()) == -1) {
				cout << "fork error!" << endl;
				continue;
			} else if (child == 0) {			//fork子进程

				//子进程，关闭监听套接字
				close(listenfd);
				ServEcho(connfd, client);
				close(connfd);
				exit(0);
			}
		}
		//父进程，关闭连接套接字
		close(connfd);
	}

}

/**
 *  服务器端处理
 */
void ServEcho(int connfd, struct sockaddr_in client) {

	//获取已连接客户端端口信息
	char buff[1024];
	inet_ntop(AF_INET, &client.sin_addr, buff, sizeof(buff));
	int port = ntohs(client.sin_port);
	cout << "accept client...address:" << buff << "  port:" << port << endl;

	time_t ticks;
	char buf[MAXLINE];

	while (true) {
		ticks = time(NULL);
		snprintf(buf, sizeof(buf), "%.24s\r\n", ctime(&ticks));

		int len;
		//服务器端向客户端发送数据
		memset(buff, 0, sizeof(buff));
		if ((len = read(connfd, buff, sizeof(buff))) == -1) {
			cout << "read error!" << endl;
			close(connfd);
			exit(0);
		} else if (len == 0) {
			cout << "client EOF!" << endl;
			break;
		}
		cout << "client send :" << buff << endl;

		write(connfd, buff, strlen(buff));		//回送客户发送信息

		//write(connfd,buf,strlen(buf));		//回送服务器时间信息
	}
}

/**
 * SIGCHLD信号是由内核在任何一个进程终止时发给它的父进程的一个信号
 * SIGCHLD缺省情况下被忽略
 * 这里设置signal处理函数，使得fork的子进程，wait他们，防止其变成僵死进程耗尽进程资源
 */
void Signal(int signo) {
	pid_t pid;
	int stat;
	while ((pid = waitpid(-1, &stat, WNOHANG)) > 0) {
		cout << "child " << pid << " terminated!" << endl;
	}
	return;
}
