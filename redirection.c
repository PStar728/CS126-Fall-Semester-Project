#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "redirection.h"

char* redirectionCheck(char** argv){
    for (int i = 0; argv[i] != NULL; i++){
        if (strcmp(argv[i], ">") == 0 ||
            strcmp(argv[i], "<") == 0 ||
            strcmp(argv[i], ">>") == 0){
            return argv[i++];
        }
        return NULL;
    }
}
redirection(char** tokens, char** redirFile){
    int fd;
    for (int i = 0; tokens[i] != NULL; i++){
        if (strcmp(tokens[i], "<") == 0){
            fd = open(redirFile, O_RDONLY);
            if (fd < 0) {
                perror(redirFile);
                exit(1);
            }
            dup2(fd, STDIN_FILENO);
        }
        if (strcmp(tokens[i], ">") == 0){
            fd = open(redirFile,
                O_WRONLY | O_CREAT | O_TRUNC,
                0644);

            if (fd < 0) {
                perror(redirFile);
                exit(1);
            }
            dup2(fd, STDOUT_FILENO);
        }
        if (strcmp(tokens[i], ">>") == 0){
            fd = open(redirFile,
                O_WRONLY | O_CREAT | O_APPEND,
                0644);

            if (fd < 0) {
                perror(redirFile);
                exit(1);
            }
            dup2(fd, STDOUT_FILENO);
        }
        return NULL;
    }
}