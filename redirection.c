#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "redirection.h"

char* redirectionCheck(char** argv){
    for (int i = 0; argv[i] != NULL; i++){
        if (strcmp(argv[i], ">") == 0 ||
            strcmp(argv[i], "<") == 0 ||
            strcmp(argv[i], ">>") == 0){
            return argv[i++];
        }
        if (strcmp(argv[i], "|") == 0){
            return "pipe";
        }
    }
    return NULL;
}
void redirection(char** tokens, char** redirFile){
    int fd;
    for (int i = 0; tokens[i] != NULL; i++){
        if (strcmp(tokens[i], "<") == 0){
            fd = open(*redirFile, O_RDONLY);
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
    }
}
void runpipe(char** tokens){
    int fd[2];
    pipe(fd);
    int pipeindex;
    for (int i = 0; tokens[i] != NULL; i++){
        if (strcmp(tokens[i], "|") == 0){
            pipeindex = i;
            break;
        }
    }

    tokens[pipeindex] = NULL;
    char **leftcmd = tokens;
    char **rightcmd = &tokens[pipeindex + 1];

    pid_t left = fork();
    if (left == 0){
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);
        execvp(leftcmd[0], leftcmd);
    }
    pid_t right = fork();
    if (right == 0){
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
        close(fd[1]);
        execvp(rightcmd[0], rightcmd);
    }
    close(fd[0]);
    close(fd[1]);
    waitpid(left, NULL, 0);
    waitpid(right, NULL, 0);
}