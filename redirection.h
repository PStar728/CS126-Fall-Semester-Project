#ifndef REDIRECTION_H
#define REDIRECTION_H

char* redirectionCheck(char** argv);
void redirection(char** argv, const char* redirOpp, const char* redirFile);
void runpipe(char** argv);

#endif