#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>
#include <stdio.h>

#define Vector(TYPE) \
typedef struct {\
    TYPE **arr;\
    int len;\
} Vector##TYPE;

typedef struct Map {
    char* key;
    char* value;
} Map;


Vector(char);
Vector(Map);

void init_vec_map(VectorMap *vec, Map **arr, int len);
void free_vec_map(VectorMap *vec);

void init_char(Vectorchar *vec, char **arr, int len);
void print_vec_char(Vectorchar vec);
void free_vec_char(Vectorchar *vec);
Vectorchar split_string(char *str, char c);

#endif 