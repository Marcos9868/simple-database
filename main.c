#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include "structs/input_buffer.h"

void print_prompt() {
  printf("db > ");
}

ssize_t getline(char **lineptr, size_t *n, FILE *stream);

void read_input(InputBuffer* input_buffer) {
  ssize_t bytes_read = getline(&(input_buffer->buffer), &(input_buffer->buffer_length), stdin);
  if (bytes_read <= 0) {
    char enter = putchar(10);
    printf("Error reading input%s", &enter);
    exit(EXIT_FAILURE);
  }
  input_buffer->input_length = bytes_read - 1;
  input_buffer->buffer[bytes_read - 1] = 0;
}

void close_input_buffer(InputBuffer* input_buffer) {
  free(input_buffer->buffer);
  free(input_buffer);
}

int main(int argc, char* argv[]) {
  char enter = putchar(10);
  InputBuffer* input_buffer = new_input_buffer();
  while (true) {
    print_prompt();
    read_input(input_buffer);

    if (strcmp(input_buffer->buffer, ".exit") == 0) {
      close_input_buffer(input_buffer);
      exit(EXIT_SUCCESS);
    } else {
      printf("Unrecognized command '%s'%s", input_buffer->buffer, &enter);
    }
  }
  return 0;
}
