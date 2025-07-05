CC = gcc
CFLAGS = -g -Wall
LDFLAGS = -lpthread

all: echoserver echoclient

# 기존 대상
csapp.o: csapp.c csapp.h
	$(CC) $(CFLAGS) -c csapp.c

# echo 함수가 있는 echo.o
echo.o: echo.c csapp.h
	$(CC) $(CFLAGS) -c echo.c
echoserver.o: echoserver.c csapp.h
	$(CC) $(CFLAGS) -c echoserver.c
echoserver: echoserver.o echo.o csapp.o
	$(CC) $(CFLAGS) -o echoserver echoserver.o echo.o csapp.o $(LDFLAGS)
echoclient.o: echoclient.c csapp.h
	$(CC) $(CFLAGS) -c echoclient.c
echoclient: echoclient.o csapp.o
	$(CC) $(CFLAGS) -o echoclient echoclient.o csapp.o $(LDFLAGS)
clean:
	rm -f *~ *.o echoserver echoclient core *.tar *.zip *.gzip *.bzip *.gz