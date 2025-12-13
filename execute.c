#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#include "execute.h"
#include "builtin.h"
/*
- Implementation:
  - Parent calls fork().                                yep
  - Child calls execvp(argv[0], argv).                  yep
  - Parent waits for foreground jobs using waitpid().   yep
  - Parent does not wait for background jobs.           yep
- If execvp() fails, print an error using perror().     yep
*/

int execute_command(char** argv, char** redirFile){
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

    if (srtcmp(redirFile, "pipe") == 0){
        pipe(argv);
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
    if (pid == 0){
        // child
        signal(SIGINT, SIG_DFL); 
        if (redirFile != NULL){
            redirect(argv, &redirFile);
        }
        execvp(argv[0], argv);
        perror("execvp");
        exit(1);
    }

    int status;

    int isbackground = 0;
    for (int i = 0; argv[i] != NULL; i++){
        if (argv[i] == "&"){
            isbackground = 1;
        }
    }
    if (isbackground == 0){
        waitpid(pid, &status, 0);
    }

    return 1;
}