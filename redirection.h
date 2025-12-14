#ifndef REDIRECTION_H
#define REDIRECTION_H

char* redirectionCheck(char** argv);
void redirection(char** argv, char** redirFile);
void runpipe(char** argv);

#endif