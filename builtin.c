#include "builtin.h"
#include <stdio.h>

/*At least:
- exit or quit: terminate the shell (no fork).                          yep
- cd [path]:                                                            yep
  - Use chdir().                                                        yep
  - If no argument is provided, change to the HOME directory.           yep
- Built-ins must be executed in the parent process, not in a child.     yep (before fork)
*/

int builtin(char** argv){
    if (strcmp(argv[0], "cd") == 0){
        if (argv[1] == NULL){
            char* home = getenv("HOME");
            if (chdir(home) != 0){
                perror("chdir");
            }
            return 1;
        }
        if (chdir(argv[1]) != 0){
            perror("chdir");
        }
        // add code for implementing cd ?? might not have to is should be in execute...
        return 1;
    }
    else if (strcmp(argv[0], "exit") == 0){
        printf("exit");
        return 2;
    }
    else if (strcmp(argv[0], "quit") == 0){
        printf("quit");
        return 2;
    }
    else {
        return 0;
    }
}
