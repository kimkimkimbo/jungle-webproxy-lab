/*
 * adder.c - a minimal CGI program that adds two numbers together
 */
/* $begin adder */
#include "csapp.h"

//웹 브라우저에서 두 숫자를 더하는 CGI 

/*
웹서버(tiny)가 /cgi-bin/adder로 요청이 오면,
QUERY_STRING 환경변수로 전달된 두 숫자를 파싱해서 더한 결과를 HTML로 출력
*/


int main(void)
{
  // buf: QUERY_STRING 환경변수(예: "num1=3&num2=5")를 가리키는 포인터
  // p:   buf에서 '&' 문자의 위치를 가리키는 포인터
  // arg1, arg2: 각각 첫 번째, 두 번째 피연산자(문자열)
  // content: 최종적으로 출력할 HTML 컨텐츠
  int n1 = 0, n2 = 0; // n1, n2: 각각 정수로 변환된 피연산자
  char *buf, *p;
  char arg1[MAXLINE], arg2[MAXLINE], content[MAXLINE];

  // 1. 웹서버가 CGI로 실행할 때, QUERY_STRING 환경변수에 쿼리 문자열이 들어옴
  //    예: /cgi-bin/adder?3&5  → QUERY_STRING="3&5"
  //    getenv("QUERY_STRING")로 값을 읽어옴. 값이 없으면 이후 로직을 건너뜀
  if ((buf = getenv("QUERY_STRING")) != NULL)
  {
    // 2. buf에서 '&' 문자를 찾아 p가 그 위치를 가리키게 함
    //    예: buf="3&5" → p는 '&'를 가리킴
    p = strchr(buf, '&');

    // 3. '&'를 '\0'로 바꿔서 buf를 "3"으로 끊음
    //    p+1은 "5"를 가리킴
    *p = '\0';

    // 4. 첫 번째 피연산자(arg1)에 "3"을 복사, 두 번째 피연산자(arg2)에 "5"를 복사
    strcpy(arg1, buf);    // arg1 = "3"
    strcpy(arg2, p + 1);  // arg2 = "5"

    // 5. 문자열을 정수로 변환
    n1 = atoi(arg1);      // n1 = 3
    n2 = atoi(arg2);      // n2 = 5
  }

  // 6. HTML 컨텐츠를 한 줄씩 누적해서 만듦
  //    (아래 sprintf들은 모두 content에 이어붙이는 방식)

  // (불필요한 덮어쓰기지만, 예시로 남김)
  sprintf(content, "QUERY_STRING=%s", buf); // 실제로는 아래에서 덮어써짐

  // HTML 본문 시작
  sprintf(content, "Welcome to add com: ");
  sprintf(content, "%sTHE Internet addition portal.\r\n<p>", content);
  sprintf(content, "%sThe answer is: %d + %d = %d\r\n<p>",
          content, n1, n2, n1 + n2);
  sprintf(content, "%sThanks for visiting!\r\n", content);

  // 7. HTTP 응답 헤더 출력
  //    - Connection: close → 연결 종료 알림
  //    - Content-length: 본문 길이
  //    - Content-type: text/html → HTML임을 알림
  printf("Connection: close\r\n");
  printf("Content-length: %d\r\n", (int)strlen(content));
  printf("Content-type: text/html\r\n\r\n");

  // 8. HTML 본문 출력
  printf("%s", content);
  fflush(stdout); // 출력 버퍼를 즉시 비움(응답 전송)

  // 9. 프로그램 정상 종료
  exit(0);
}

/* $end adder */
