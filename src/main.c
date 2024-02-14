#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

void error(char *msg)
{
    perror(msg);
    exit(1);
}

#define PORT 8000
#define BUFFER_LENGTH 256

struct Header {
    char* key;
    char* value;
};

struct VectorString {
    char** arr;
    int len;
};

struct VectorString split_string(char *str, char c) {
    int start = 0;
    int end = 0;
    
    char** arr;
    int len = 1;
    while (*(str + end) != '\0') {
        if ( *(str + end) == c) {
            len++;
        }
        end += 1;
    }
    
    end = 0;
    arr = malloc(len * (sizeof(char *)));
    int index = 0;

    while (*(str + end) != '\0') {
        if ( *(str + end) == c) {
            arr[index] = malloc(end - start + 1); 
            memcpy(arr[index], str + start, end - start + 1 );
            arr[index][end - start] = '\0';
            start = end + 1;
            index += 1;
        }

        end += 1;
    }

    arr[index] = malloc(end - start + 1);
    arr[index] = memcpy(arr[index], str + start, end - start + 1);

    struct VectorString res;
    res.arr = arr;
    res.len = len;

    return res; 
}

int parse_request(char *request) {
    
    struct VectorString res = split_string(request, '\n');
    for (int i = 0; i < res.len - 1; i++) {
        printf("%s\n", res.arr[i]);
    }

    for (int i = 0; i < res.len; i++) {
        free(res.arr[i]);
    }
    free(res.arr);
    
    return 0;
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

    // while (1)
    // {
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
        
        if (parse_request(buffer) < 0) {
            error("Can't not parse");
        }
        char* reply = "HTTP/1.0 200 OK";
        if (write(new_sockfd, reply, strlen(reply)) < 0) {
            error("Can not write to the socket");
        }
        // printf("%s", buffer);

        if (close(new_sockfd) < 0)
        { // After close socket will have somtime before it unbind from a port
            error("Can not close listening socket");
        }
    // }

    if (close(sockfd) < 0)
    {
        error("Can not close socket");
    }

    return 0;
}