#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]){

    while (argv[0] != "quit" || argv[0] != "exit"){

        if (argv[0] == "pwd"){
            char cwd[1024];
            if (getcwd(cwd, sizeof(cwd)) != NULL) {
                printf("Current working dir: %s\n", cwd);
            } else {
                perror("getcwd() error");
            }
        }

    }





    return 0;
}