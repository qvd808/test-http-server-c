#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

void error(char *msg)
{
    perror(msg);
    exit(1);
}

#define PORT 80
#define SERVER "www.google.com"

int main()
{
    // if (argc < 3)
    // {
    //     fprintf(stderr, "usage %s hostname port\n", argv[0]);
    //     exit(0);
    // }
    // int portno = atoi(argv[2]);
    struct sockaddr_in server;

    char *message;
    char server_reply[2000];

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        error("Could not create the socket");
    }
    server.sin_addr.s_addr = inet_addr("172.217.13.206");
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);

    if (connect(sockfd, (struct sockaddr *) &server, sizeof(server)) < 0) {
        error("Connect failed");
    }

    printf("Connected\n");

    message = "GET / HTTP/1.1\r\nHost: www.google.com\r\nConnection: close\r\n\r\n";
    if (send(sockfd, message, strlen(message), 0) < 0) {
        error("Send failed");
    }

    printf("Data send\n");

    if (recv(sockfd, server_reply, 2000, 0) < 0) {
        error("Recv failed\n");
    }

    printf("Reply received");

    printf("%s\n", server_reply);

    close(sockfd);
    return 0;
}
