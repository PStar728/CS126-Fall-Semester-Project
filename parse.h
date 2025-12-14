#ifndef PARSE_H
#define PARSE_H

char* read_line();
char** parse_line(char* line, char** redirOp, char** redirFile);

#endif