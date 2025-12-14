#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#include "execute.h"
#include "redirection.h"
#include "builtin.h"
/*
- Implementation:
  - Parent calls fork().                                yep
  - Child calls execvp(argv[0], argv).                  yep
  - Parent waits for foreground jobs using waitpid().   yep
  - Parent does not wait for background jobs.           yep
- If execvp() fails, print an error using perror().     yep
*/

int execute_command(char** argv, char* redirOpp, char* redirFile, FILE* logfile, char* line){
    if (argv[0] == NULL){
        //idk what this is yet
        return 1;
    }

    int x = builtin(argv);
    // if x != 0 argv is a built in code and can stop
    if (x != 0){
        // 2 is a special break number quits the program
        return 2;
    }

    if (redirOpp != NULL && strcmp(redirOpp, "pipe") == 0){
        runpipe(argv);
        return 2;
    }

    // this section should be in builtin.c
    /*if (strcmp(argv[0], "cd") == 0){
        const char *path = (argv[1] ? argv[1] : getenv("HOME"));

        if (chdir(path) != 0){
            perror("cd");
        }
        return 1;
    }*/

    pid_t pid = fork();

    if (pid < 0){
        perror("fork");
        return 1;
    }
    int isbackground = 0;
    for (int i = 0; argv[i] != NULL; i++){
        if (strcmp(argv[i], "&") == 0){
            isbackground = 1;
            argv[i] = NULL;
            break;
        }
    }
    if (pid == 0){
        // child
        signal(SIGINT, SIG_DFL); 
        if (redirOpp != NULL && strcmp(redirOpp, "pipe") != 0){
            redirection(argv, redirOpp, redirFile);
        }
        execvp(argv[0], argv);
        perror("execvp");
        exit(1);
    }

    int status = 0;
    int exit_code = 0;

    if (isbackground == 0){
        waitpid(pid, &status, 0);
    }

    if (WIFEXITED(status)) {
        exit_code = WEXITSTATUS(status);
    } else if (WIFSIGNALED(status)) {
        exit_code = 128 + WTERMSIG(status);
    }

    char logbuf[1024];
    int len = snprintf(logbuf, sizeof(logbuf), 
        "PID=%d CMD=\"%s\" EXIT=%d\n", pid, line, exit_code);

    int fd = fileno(logfile);
    write(fd, logbuf, len);


    return 1;
}