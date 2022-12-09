#include "csapp.h"

void echo(int connfd);

int main(int argc, char **argv)
{
	int listenfd, connfd;
	socklen_t clientlen;
	struct sockaddr_storage clientaddr; /* Enough space for any address */
	char client_hostname[MAXLINE], client_port[MAXLINE];

	if (argc != 2) {
		fprintf(stderr, "usage: %s <port>\n", argv[0]);
		exit(0);
	}

	// 듣기 식별자를 엶
	// Open_listenfd : 연결 요청을 받을 준비가 된 듣기 식별자를 생성하는 함수
	// server 소켓을 listenfd로 만들어서 대기
	listenfd = Open_listenfd(argv[1]);

	// EOF가 들어오기 전까지 계속 돌음
	while (1) {
		// clientlen은 sockaddr_storage 구조체의 크기
		clientlen = sizeof(struct sockaddr_storage);
		// listenfd가 clientaddr를 만나면 accept가 되고,
		// 새로운 식별자를 connfd에 return
		connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
		
		// clientaddr, clientlen을 이용해, client_hostname, client_port를 만듦
		Getnameinfo((SA *) &clientaddr, clientlen, client_hostname, MAXLINE,
												client_port, MAXLINE, 0);
		// client_hostname, client_port 출력
		printf("Connected to (%s, %s)\n", client_hostname, client_port);
		// echo 함수에 connfd를 넣어서 돌림

		// 여기서 buf에 connfd를 복사함
		echo(connfd);
		// 닫음
		Close(connfd);
	}
exit(0);
}
