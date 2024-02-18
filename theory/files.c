#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <errno.h>


int main() {
    FILE *fptr;
    fptr = fopen("./public/index.html", "r");

    char mystring[100];
    bzero(mystring, 100);

    fgets(mystring, 100, fptr);

    printf("%s\n", mystring);
}