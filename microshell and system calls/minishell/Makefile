minishell: main.c parser.o command_functions.o
	gcc -g -Wall main.c parser.o command_functions.o -o minishell

parser.o: parser.c parser.h
	gcc -g -c -Wall parser.c -o parser.o

command_functions.o: command_functions.c command_functions.h
	gcc -g -c -Wall command_functions.c -o command_functions.o

clean:
	rm -f *.o
	rm -f minishell