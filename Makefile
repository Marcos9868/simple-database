main: main.c
	$(CC) main.c structs/input_buffer.c -o main -Wall -Wextra -pedantic -std=c99

