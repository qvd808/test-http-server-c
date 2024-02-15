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

int parse_request(char *request, struct Request req)
{

    // Let assume first line is method, and the rest is header

    Vectorchar res = split_string(request, '\n');
    for (int i = 1; i < res.len - 2; i++)
    {
        if (strlen(res.arr[i]) >= 1)
        {
            Map key_value = parse_header(res.arr[i]);
            printf("The key is:%s\n", key_value.key);
            printf("The value is:%s\n", key_value.value);
            free(key_value.key);
            free(key_value.value);
        }
    }

    print_vec_char(res);
    free_vec_char(&res);

    return 0;
}
