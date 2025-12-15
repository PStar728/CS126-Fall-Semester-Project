-Mini Linux Shell : Contributors -> Frankie Gonzalez, Finnian Meyer, & Samuel Gadde

-CS-12600-001 Fall Semester 2025

-Build Instructions:
Compile with the Linux directory with the source code files, and type: 
'gcc *.c -o myshell' or 'make'

-Run Instructions:
Use the command line, and type: "./myshell"

-Dependencies: 
Linux OS, GCC compiler, standard C libraries

-Incomplete Features: 
You can only pipe one command into another, any more pipes will not work. 
While testing, encountered a bug that will add 'exit' or 'quit' into the prompt and make it unable to exit.Unable to recreate it after figuring this out. 
Does not include the helpful linux feature of pressing the up arrow and getting to view your previously typed command.
-Sample Commands:
ls
cd /home/yourdirectoryname
echo "Hello World!"
One Pipe -> echo | ls -l 
redirect -> echo hello > out.txt 
exit or quit to end 
