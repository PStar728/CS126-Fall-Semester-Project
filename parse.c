#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parse.h"

char* read_line(){
    //i dont think we need
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
    int bufsize = 64;
    int position = 0;
    char** tokens = malloc(sizeof(char*) * bufsize);

    if (!tokens){
        perror("malloc");
        return NULL;
    }
    char* token = strtok(line, " \t\n");
    
    while (token != NULL){
        tokens[position++] = token;
        
        if (position >= bufsize){
            bufsize *= 2;
            tokens = realloc(tokens, sizeof(char*) * bufsize);
        }

        token = strtok(NULL, " \t\n");
    }
    token[position] = NULL;
     return tokens;
}