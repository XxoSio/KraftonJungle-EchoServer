#include "csapp.h"

void echo(int connfd)
{
	size_t n;
	char buf[MAXLINE];
	rio_t rio;

	// open한 식별자마다 한번 호출
	// 식별자 connfd를 주소 rio에 위치한 읽기 버퍼와 연결
	Rio_readinitb(&rio, connfd);

	// rio에서 얻은 값을 buf에 복사
	while((n = Rio_readlineb(&rio, buf, MAXLINE)) != 0) {
		printf("server received %d bytes\n", (int)n);
		// buf의 값을 connfd에 복사
		Rio_writen(connfd, buf, n);
	}
}
