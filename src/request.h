#ifndef REQUEST_H
#define REQUEST_H

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

struct Header {
    char* key;
    char* value;
};

struct Request {
    char *method;
    struct Header *header;
    char* body;
};
int parse_request(char *request, struct Request req);


#endif 