#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>

#include "signals.h"

sigchldHandler(int sig){
    (void)sig;
    int status;

    while (waitpid(-1, &status, WNOHANG) > 0);
}