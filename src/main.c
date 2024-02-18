#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include "request.h"

void error(char *msg)
{
    perror(msg);
    exit(1);
}

#define PORT 8000
#define BUFFER_LENGTH 256

char* get_file(char * request) {
    
    int end, start, i;
    end = 5; start = 5; i = 5;
    
    while (*(request + i) != ' ') {
        end += 1;
        i += 1;
    }
    char *file = malloc(end - start + 1);
    memcpy(file, request + start, end - start + 1);
    file[end - start + 1] = '\0';

    return file;
}


int main(int argc, char* argv[])
{

    int sockfd, client_socketfd, client_len, portno;
    char buffer[BUFFER_LENGTH];
    struct sockaddr_in server_addr, client_addr; // server address

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        error("Error when creating socket");
    }

    bzero(&server_addr, sizeof(server_addr));
    portno = htons(atoi(argv[1]));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = portno;
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        error("Can not bind the address to the socket");
    }

    listen(sockfd, 5);

    client_len = sizeof(client_addr);

    while (1)
    {
        int new_sockfd = accept(sockfd, (struct sockaddr *)&client_addr, &client_len);
        if (new_sockfd < 0)
        {
            error("Error on accept");
        }

        bzero(&buffer, BUFFER_LENGTH);
        if (read(new_sockfd, &buffer, BUFFER_LENGTH) < 0)
        {
            error("Can't not read message");
        }
        char *file = get_file(buffer);        

        char *reply = 
        "HTTP/1.1 200 OK\n"
        "Content-Type: text/html\n"
        // "Content-Length: 14\n"
        // "Accept-Ranges: bytes\n"
        // "Connection: close\n"
        "\n";
        int original_length = strlen(reply);
        char test[1024];
        memcpy(test, reply, original_length);
        if (strcmp(file, "index.html") || strcmp(file, " ")) {
            FILE *fptr = fopen("./public/index.html", "r");
            fread(test + original_length, 1024 - original_length, 1, fptr);
            printf("%s\n", test);
        }

        if (write(new_sockfd, test, strlen(test)) < 0) {
            error("Can not write to the socket");
        }

        if (close(new_sockfd) < 0)
        { // After close socket will have somtime before it unbind from a port
            error("Can not close listening socket");
        }
        free(file);

    }

    if (close(sockfd) < 0)
    {
        error("Can not close socket");
    }


    return 0;
}