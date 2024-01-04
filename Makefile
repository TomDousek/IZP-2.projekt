CC= gcc
CFLAGS= -std=c11 -Wall -Wextra -Werror
maze:maze.c
	$(CC) $(CFLAGS) maze.c -o maze -g
