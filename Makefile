CC = gcc
CFLAGS = -Wall -Wextra -g

TARGET = myshell

OBJS = main.o \
       execute.o \
       builtin.o \
       redirection.o \
       parse.o \
       signals.o

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

main.o: main.c execute.h parse.h signals.h
	$(CC) $(CFLAGS) -c main.c

execute.o: execute.c execute.h builtin.h redirection.h
	$(CC) $(CFLAGS) -c execute.c

builtin.o: builtin.c builtin.h
	$(CC) $(CFLAGS) -c builtin.c

redirection.o: redirection.c redirection.h
	$(CC) $(CFLAGS) -c redirection.c

signals.o: signals.c signals.h
	$(CC) $(CFLAGS) -c signals.c

parse.o: parse.c parse.h redirection.h
	$(CC) $(CFLAGS) -c parse.c

clean:
	rm -f $(TARGET) *.o
