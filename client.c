#include "csapp.h"

int main(int argc, char **argv)
{
	int clientfd;
	char *host, *port, buf[MAXLINE];
	rio_t rio;

	// 서버와의 연결 수립
	if (argc != 3) {
		fprintf(stderr, "usage: %s <host> <port>\n", argv[0]);
		exit(0);
	}
	host = argv[1];
	port = argv[2];

	// 클라이언트의 식별자를 엶
	// Open_clientfd : 서버와 연결을 설정하는 함수
	// open_clientfd 함수를 사용해서 소켓을 clientfd로 만듦
	clientfd = Open_clientfd(host, port);
	// clientfd에 rio 주소를 연결
	Rio_readinitb(&rio, clientfd);

	// 텍스트 줄을 반복적해서 읽는 루프
	while (Fgets(buf, MAXLINE, stdin) != NULL) {

		// 표준 입력 스트림을 사용하여 buf를 strlen(buf)만큼 복사해서 넣고
		Rio_writen(clientfd, buf, strlen(buf));
		// rio에 있는 값을 buf에 MAXLINE만큼 복사해서 넣음
		Rio_readlineb(&rio, buf, MAXLINE);
		// 표준 출력 스트림에 buf를 넣음
		Fputs(buf, stdout);
	}
	// 메모리 누수를 막기 위해 clientfd(클라이언트의 식별자)를 닫음
	Close(clientfd);
	// 함수 밖으로 나감
	exit(0);
}
