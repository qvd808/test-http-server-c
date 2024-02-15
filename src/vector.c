#include "vector.h"

void init(Vectorchar *vec, char **arr, int len) {

    vec->arr = arr;
    vec->len = len;
}

void print_vec(Vectorchar vec) {

    for (int i = 0; i < vec.len; i++) {
        printf("%s\n", vec.arr[i]);
    }
}