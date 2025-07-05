#include "csapp.h"
/*
echo.c의 echo(int connfd) 함수는 에코 서버의 핵심 함수, 
클라이언트와 연결된 소켓(connfd)에서 데이터를 읽어서 그대로 다시 돌려보내는 역할
*/
void echo(int connfd)
{
    size_t n;
    char buf[MAXLINE];
    rio_t rio;

    //Rio_readinitb로 robust I/O 버퍼를 초기화
    Rio_readinitb(&rio, connfd);

    //클라이언트가 보낸 데이터를 한 줄씩(Rio_readlineb) 읽기
    while ((n = Rio_readlineb(&rio, buf, MAXLINE)) != 0)
    //클라이언트가 연결을 끊을 때까지(읽을 데이터가 없을 때까지) 반복
    {
        //읽은 데이터의 바이트 수를 출력(printf)
        printf("server received %d bytes\n", (int)n);
        
        //읽은 데이터를 그대로 클라이언트에게 다시 전송(Rio_writen)
        Rio_writen(connfd, buf, n);
    }
}