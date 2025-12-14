#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "parse.h"
#include "redirection.h"

char* read_line(){  
    size_t size = 1024;
    char* line = malloc(size);

    if (!line) {
        perror("malloc");
        return NULL;
    }

    if (fgets(line, size, stdin) == NULL) {
        free(line);
        return NULL;
    }

    return line;
}
char** parse_line(char* line, char** redirFile){
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
    tokens[position] = NULL;
    *redirFile = redirectionCheck(tokens);
    return tokens;
}