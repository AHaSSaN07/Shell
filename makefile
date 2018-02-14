all: shell.c
	gcc -o shell shell.c main.c
clean:
	rm shell