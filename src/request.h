#ifndef REQUEST_H
#define REQUEST_H

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include "vector.h"

struct Request {
    char *method;
    Map *vec; 
    char* body;
};
int parse_request(char *request, struct Request req);


#endif 