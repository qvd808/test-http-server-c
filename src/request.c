#include "request.h"

Map parse_header(char *str) {
    int end = 0;
    while (*(str + end) != '\0') {
        if (*(str + end) == ':') {
            break;
        }
        end += 1;
    }
    Map res;
    res.key = malloc(end + 1);
    res.value = malloc(strlen(str) - end);

    memcpy(res.key, str, end + 1);
    res.key[end] = '\0';
    memcpy(res.value, str + (end + 1), strlen(str) - end);
    res.value[strlen(str) - end - 1] = '\0';

    return res;
}

int parse_request(char *request, struct Request *req)
{

    // Let assume first line is method, and the rest is header

    Vectorchar res = split_string(request, '\n');
    Map *arr = malloc(1);
    int len = 0;
    for (int i = 1; i < res.len; i++)
    {
        if (strlen(res.arr[i]) > 1)
        {
            arr = realloc(arr, sizeof(Map) * (len + 1));
            
            Map key_value = parse_header(res.arr[i]);
            arr[len].key = key_value.key;
            arr[len].value = key_value.value;

            len += 1;
        }
    }

    // for (int i = 0; i < len; i+=1) {

    //     printf("The key is:%s\n", arr[i].key);
    //     printf("The value is:%s\n", arr[i].value);
    // }

    req->header = malloc(sizeof(Header));
    req->header->header_vec = arr;
    req->header->len = len;
    req->method = malloc(strlen(res.arr[0]));
    memcpy(req->method, res.arr[0], strlen(res.arr[0]));

    print_vec_char(res);
    free_vec_char(&res);

    return 0;
}

void free_request(struct Request *req) {
    // if (req->body != NULL) {
    //     free(req->body);
    // }

    if (req->method != NULL) {
    free(req->method);
    }

    if (req->header->header_vec != NULL) {
        for (int i; i < req->header->len; i++) {
            printf("%s\n", req->header->header_vec[i].key);

            free(req->header->header_vec[i].key);
            free(req->header->header_vec[i].value);
        }
        free(req->header->header_vec);
    }
}