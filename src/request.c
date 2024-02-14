#include "request.h"


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

int test_func(char * str) {
    printf("%s\n", str);
}