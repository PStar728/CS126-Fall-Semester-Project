#ifndef REDIRECTION_H
#define REDIRECTION_H

char* redirectionCheck(char** argv);
void redirect(char** argv, char** redirFile);
void pipe(char** argv);

#endif