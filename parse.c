#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parse.h"

char* read_line(){
    char* line = NULL;
    size_t size = 0;

    ssize_t len = getline(&line, &size, stdin);

    if (len == -1) {
        free(line);
        return NULL;
        perror("get line in parse");
    }
    return line;
}
char** parse_line(char* line){
    
}