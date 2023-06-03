#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#define MAX 20
int main()
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr = { AF_INET, htons(1234), inet_addr("127.0.0.1") };
    while(connect(sock, (struct sockaddr *) &addr, sizeof(addr))) ;
    printf("\nClient is connected to Server\n");
    char msg[MAX];
    printf("\nEnter message to send : ");
    fgets(msg, MAX, stdin);
    msg[strlen(msg)-1] = '\0';
    char frame[MAX];
    int i = 0;
    int ack;
    while(i<strlen(msg))
    {
        int sendsize = 5;
        memset(frame, 0, MAX);
        strncpy(frame, msg+i, sendsize);
        if( sendsize > strlen(frame) )
            sendsize = strlen(frame);
        printf("\n\nSending packet = %s", frame);
        printf("\nSending window: ");
        printf("\n start seqno = %d", i);
        printf("\n end seqno = %d", i+sendsize-1);
        send(sock, frame, sendsize, 0);
        recv(sock, &ack, sizeof(ack), 0);
        printf("\nreceived ack no = %d ",ack);
        i = ack;
    }
    send(sock, "Exit", strlen("Exit"), 0);
    close(sock); printf("\n\n");
}
