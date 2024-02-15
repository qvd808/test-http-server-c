#include "vector.h"
#include <string.h>


///////// Character Implement
void init_char(Vectorchar *vec, char **arr, int len) {

    vec->arr = arr;
    vec->len = len;
}

void print_vec_char(Vectorchar vec) {

    for (int i = 0; i < vec.len; i++) {
        printf("%s\n", vec.arr[i]);
    }
}

void free_vec_char(Vectorchar *vec) {
    for (int i = 0; i < vec->len; i++) {
        free(vec->arr[i]);
    }

    free(vec->arr);
}

Vectorchar split_string(char *str, char c)
{
    int start = 0;
    int end = 0;

    char **arr;
    int len = 1;
    while (*(str + end) != '\0')
    {
        if (*(str + end) == c)
        {
            len++;
        }
        end += 1;
    }

    end = 0;
    arr = malloc(len * (sizeof(char *)));
    int index = 0;

    while (*(str + end) != '\0')
    {
        if (*(str + end) == c)
        {
            arr[index] = malloc(end - start + 1);
            memcpy(arr[index], str + start, end - start + 1);
            arr[index][end - start] = '\0';
            start = end + 1;
            index += 1;
        }

        end += 1;
    }

    arr[index] = malloc(end - start + 1);
    arr[index] = memcpy(arr[index], str + start, end - start + 1);

    Vectorchar res;
    init_char(&res, arr, len);

    return res;
}
///////// Map Implement

// void init_vec_map(VectorMap *vec, Map **arr, int len) {
//     vec->arr = arr;
//     vec->len = len;
// }

// void free_vec_map(VectorMap *vec) {
    
//     for (int i = 0; i < vec->len; i++) {
//         free(vec->arr[i]);
//     }

//     free(vec->arr);
// }