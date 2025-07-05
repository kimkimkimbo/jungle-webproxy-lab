#include "csapp.h"

/*
사용자가 입력한 내용을 서버(에코 서버)에 보내고, 
서버가 다시 돌려주는(에코) 메시지를 받아서 화면에 출력
*/

int main(int argc, char **argv){

    int clientfd;
    char *host, *port, buf[MAXLINE];
    rio_t rio;

    //실행 시 서버의 호스트와 포트 번호를 인자로 받음
    //예외 처리 - 필수 입력 값 넣었는지 확인
    if (argc != 3){
        fprintf(stderr, "usage: %s <host> <port>\n", argv[0]);
        exit(0);
    }

    host = argv[1];
    port = argv[2];

    //서버에 연결(Open_clientfd)
    clientfd = Open_clientfd(host, port);
    //robust I/O 초기화(Rio_readinitb)
    Rio_readinitb(&rio, clientfd);

    //표준 입력(stdin)에서 한 줄을 읽음(Fgets)
    while (Fgets(buf, MAXLINE, stdin) != NULL)
    //입력이 끝날 때까지 반복
    {
        //읽은 내용을 서버로 전송(Rio_writen)
        Rio_writen(clientfd, buf, strlen(buf));
        //서버가 돌려준(에코) 메시지를 받음(Rio_readlineb)
        Rio_readlineb(&rio, buf, MAXLINE);
        //화면에 출력(Fputs)
        Fputs(buf, stdout);
    }

    //연결 종료 후 프로그램 종료
    Close(clientfd);
    exit(0);
    
}