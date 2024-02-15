#ifndef REQUEST_H
#define REQUEST_H

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include "vector.h"

typedef struct Header {
    Map *header_vec;
    int len;
} Header;

struct Request {
    char *method;
    Header *header; 
    char* body;
};
int parse_request(char *request, struct Request *req);
void free_request(struct Request *req);

#endif 