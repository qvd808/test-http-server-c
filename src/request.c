#include "request.h"
#include "vector.h"



int parse_request(char *request, struct Request req)
{

    Vectorchar res = split_string(request, '\n');
    
    print_vec(res);
    free_vec(&res);
    
    return 0;
}
