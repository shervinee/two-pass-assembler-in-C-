
#include <stdio.h>
#include <stdlib.h>
#include "P4Headers.h"
#include <string.h>

int main(int argc, char*argv[])
{
    char *errorS = {".err"}; // extension for error file
    char *symS = {".sym"}; // extension for symbol file
    char *objS = {".obj"}; // extension for object file
    if(argc != 2){
        fprintf(stderr,"Invalid usage format\n");
        exit(1);
    }
    return 0;
}