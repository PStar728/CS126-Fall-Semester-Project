#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>



#include "parse.h"
#include "execute.h"
#include "signals.h"

//

/*2.1 Shell Main Loop
- Display a prompt exactly as: myshell>  (myshell, >, space).   yep
- Read input using fgets().                                     yep
- Ignore empty lines.                                           yep
- Parse the input into tokens using dynamic memory (malloc).    yep
- Execute the command.                                          yep... i think
- Exit the shell when the user types exit or quit.              yep
*/           
int main(){
    FILE *logfile = fopen("myshell.log", "a");
    if (!logfile){
        perror("fopen");
        exit(1);
    }

    signal(SIGINT, SIG_IGN);
    signal(SIGCHLD, sigchldHandler);

    while (1){
        printf("myshell> ");
        char* line;
        line = read_line();
        while (line == NULL){
            line = read_line();
        }


        //added declarations for the redirections
        char* redirOpp = NULL;
        char* redirFile = NULL;
        //parses lines into tokens
        char** tokens  = parse_line(line, &redirOpp, &redirFile);
        // executes tokens
        int x = execute_command(tokens, redirOpp, redirFile, logfile, line);
        if (x == 2){
            break;
        }

        // everything should be done up to 2.4... i think next work on
        // I/O Redirection using >< all on 2.4 under assignment prompt




    }





    return 0;
}