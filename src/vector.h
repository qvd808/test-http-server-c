#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>
#include <stdio.h>

#define Vector(TYPE) \
typedef struct {\
    TYPE **arr;\
    int len;\
} Vector##TYPE;

Vector(char);

void init(Vectorchar *vec, char **arr, int len);
void print_vec(Vectorchar vec);
void free_vec(Vectorchar *vec);
Vectorchar split_string(char *str, char c);

#endif 