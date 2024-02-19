#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <signal.h>

void error(char *msg)
{
    perror(msg);
    exit(1);
}

#define PORT 8000
#define BUFFER_LENGTH 256

char *get_file(char *request)
{

    int end, start, i;
    end = 4;
    start = 4;
    i = 4;

    while (*(request + i) != ' ')
    {
        end += 1;
        i += 1;
    }
    char *file = malloc(end - start + 1);
    memcpy(file, request + start, end - start);
    file[end - start] = '\0';

    return file;
}

void process_respond(char **reply, char *file)
{
    char *mine_type = strchr(file, '.');
    int lent = 18;
    // printf("%s\n", mine_type);
    // printf("%s\n", file);
    *reply = (char *)malloc(18);
    // bzero(*reply, 18);
    strcat(*reply, "HTTP/1.1 200 OK\n");

    if (!mine_type)
    {
        *reply = (char *)realloc(*reply, lent + strlen("Content-Type: text/html\n\n"));
        strcat(*reply, "Content-Type: text/html\n\n");
    }
    else if (strcmp(mine_type, ".html") == 0)
    {
        *reply = (char *)realloc(*reply, lent + strlen("Content-Type: text/html\n\n"));
        strcat(*reply, "Content-Type: text/html\n\n");
    }
    else if (strcmp(mine_type, ".js") == 0)
    {
        *reply = (char *)realloc(*reply, lent + strlen("Content-Type: text/javascript\n\n"));
        strcat(*reply, "Content-Type: text/javascript\n\n");
    }
    else if (strcmp(mine_type, ".png") == 0)
    {
        *reply = (char *)realloc(*reply, lent + strlen("Content-Type: image/png\n\n"));
        strcat(*reply, "Content-Type: image/png\n\n");
    }
    else if (strcmp(mine_type, ".gif") == 0)
    {
        *reply = (char *)realloc(*reply, lent + strlen("Content-Type: image/gif\n\n"));
        strcat(*reply, "Content-Type: image/gif\n\n");
    }
    else if (strcmp(mine_type, ".svg") == 0)
    {
        *reply = (char *)realloc(*reply, lent + strlen("Content-Type: image/svg+xml\n\n"));
        strcat(*reply, "Content-Type: image/svg+xml\n\n");
    }

    else if (strcmp(mine_type, ".css") == 0)
    {
        *reply = (char *)realloc(*reply, lent + strlen("Content-Type: text/css\n\n"));
        strcat(*reply, "Content-Type: text/css\n\n");
    }

    else if (strcmp(mine_type, ".jpg") == 0)
    {
        *reply = (char *)realloc(*reply, lent + strlen("Content-Type: image/jpeg\n\n"));
        strcat(*reply, "Content-Type: image/jpeg\n\n");
    }
    else
    {
        *reply = (char *)realloc(*reply, lent + strlen("Content-Type: text/html\n\n"));
        strcat(*reply, "Content-Type: text/html\n\n");
    }
}

int read_file_to_buffer(char *file, char **buffer, int *size_of_buffer)
{

    FILE *fptr;
    char public_dir[256] = "./public";
    if (strcmp(file, "/") == 0)
    {
        fptr = fopen("./public/index.html", "r");
    }
    else
    {
        strcat(public_dir, file);
        fptr = fopen(public_dir, "r");
    }

    if (!fptr)
    {
        return -1;
    }

    fseek(fptr, 0L, SEEK_END);
    *size_of_buffer = ftell(fptr);
    fseek(fptr, 0L, SEEK_SET);
    *buffer = (char *)malloc(*size_of_buffer);

    fread(*buffer, *size_of_buffer, 1, fptr);

    fclose(fptr);
    return 0;

    // What happened if we send a file that is too large?
}

void handle_sigint(int sig)
{
    exit(-1);
    printf("Server setting down\n");
}

int main(int argc, char *argv[])
{
    signal(SIGINT, handle_sigint);
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

        char *buffer_file;
        int size_of_buffer = 0;

        char *reply;
        process_respond(&reply, file);

        int n = read_file_to_buffer(file, &buffer_file, &size_of_buffer);
        printf("%s\n", reply);
        if (write(new_sockfd, reply, strlen(reply)) < 0)
        {
            error("Can not write to the socket");
        }
        pid_t pid = fork();

        if (pid == 0)
        {

            if (n == 0)
            {
                if (write(new_sockfd, buffer_file, size_of_buffer) < 0)
                {
                    error("Can not write to the socket");
                }
            }
            exit(EXIT_SUCCESS);
        }
        else if (pid < 0)
        {
            exit(EXIT_FAILURE);
        }
        else
        {
            wait(pid);
            if (buffer_file)
                free(buffer_file);
            if (file)
                free(file);
            if (reply)
                free(reply);
        }

        if (close(new_sockfd) < 0)
        { // After close socket will have somtime before it unbind from a port
            error("Can not close listening socket");
        }
    }

    // safe_exit:
    if (close(sockfd) < 0)
    {
        error("Can not close socket");
    }

    return 0;
}