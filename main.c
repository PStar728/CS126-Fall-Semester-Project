#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include "parse.h"
#include "execute.h"
#include "builtin.h"
#include "signals.h"


/*2.1 Shell Main Loop
- Display a prompt exactly as: myshell>  (myshell, >, space).   yep
- Read input using fgets().                                     yep
- Ignore empty lines.                                           yep
- Parse the input into tokens using dynamic memory (malloc).    yep
- Execute the command.                                          yep... i think
- Exit the shell when the user types exit or quit.              yep
*/           
int main(){

    signal(SIGINT, SIG_IGN);
    signal(SIGCHLD, sigchldHandler);

    while (1){
        printf("myshell> ");
        char* line;
        fgets(line, sizeof(line), stdin);
        while (line == NULL){
            fgets(line, sizeof(line), stdin);
        }


        //added declarations for the redirections
        char* redirFile = NULL;
        //parses lines into tokens
        char** tokens  = parse_line(line, &redirFile);
        // executes tokens          i have no idea what that output is yet
        int x = execute_command(tokens, &redirFile);
        if (x == 2){
            break;
        }

        // everything should be done up to 2.4... i think next work on
        // I/O Redirection using >< all on 2.4 under assignment prompt




    }





    return 0;
}