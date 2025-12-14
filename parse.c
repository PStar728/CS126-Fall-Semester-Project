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
char** parse_line(char* line, char** redirOpp, char** redirFile){
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
    // Find any pipe or redirection operator and extract filename/operator.
    *redirOpp = NULL;
    *redirFile = NULL;
    for (int i = 0; tokens[i] != NULL; i++){
        if (strcmp(tokens[i], "|") == 0){
            // mark that there is a pipe; keep tokens intact so runpipe can find it
            *redirOpp = "pipe";
            break;
        }
        if (strcmp(tokens[i], "<") == 0 || strcmp(tokens[i], ">") == 0 || strcmp(tokens[i], ">>") == 0){
            // operator is tokens[i], filename should be tokens[i+1]
            *redirOpp = tokens[i];
            if (tokens[i+1] != NULL){
                *redirFile = tokens[i+1];
            } else {
                *redirFile = NULL;
            }
            // remove operator and filename by shifting later tokens left
            int j = i;
            while (tokens[j+2] != NULL){
                tokens[j] = tokens[j+2];
                j++;
            }
            // terminate the array at the new end
            tokens[j] = NULL;
            break;
        }
    }
    return tokens;
}