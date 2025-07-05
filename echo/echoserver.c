#include "csapp.h"

void echo(int connfd);

/*
에코 서버 메인
*/
int main(int argc, char **argv)
{

    int listenfd, connfd;
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;

    char client_hostname[MAXLINE], client_port[MAXLINE];

    // 제대로 입력값을 받았는지 예외 처리
    if (argc != 2)
    {
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        exit(0);
    }

    // 실행 시 포트 번호를 인자로 받아 해당 포트로 서버 소켓을 엽니다(Open_listenfd)
    listenfd = Open_listenfd(argv[1]);

    // 무한 루프를 돌며 클라이언트의 연결 요청 기다림
    while (1)
    {

        //클라이언트 주소 정보를 저장할 struct sockaddr_storage의 크기(바이트 수)를 clientlen에 저장하는 것
        clientlen = sizeof(struct sockaddr_storage);
        
        // 클라이언트가 접속하면(Accept)
        connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
        
        //클라이언트의 주소(clientaddr)와 포트(client_port)를 정보를 문자열로 변환
        Getnameinfo((SA *)&clientaddr, clientlen, client_hostname, MAXLINE, client_port, MAXLINE, 0);

        // 클라이언트의 주소와 포트 정보를 출력
        printf("Connected to (%s, %s)\n", client_hostname, client_port);

        // 연결된 소켓을 echo(connfd) 함수에 넘겨,
        // 클라이언트가 보낸 데이터를 그대로 다시 돌려보냄
        echo(connfd);

        //클라이언트와의 통신이 끝나면 소켓을 닫음
        Close(connfd);
    }
    exit(0);
}