#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include "structs/input_buffer.h"
#include "commands/meta_command_result.h"
#include "enums/prepare_result_enum.h"
#include "enums/meta_command_result_enum.h"
#include "structs/statement.h"
#include "results/prepare_results.h" 

void print_prompt() {
  printf("db > ");
}

ssize_t getline(char **lineptr, size_t *n, FILE *stream);

void read_input(InputBuffer* input_buffer) {
  ssize_t bytes_read = getline(&(input_buffer->buffer), &(input_buffer->buffer_length), stdin);
  if (bytes_read <= 0) {
    printf("\nError reading input\n");
    exit(EXIT_FAILURE);
  }
  if (bytes_read == 1) {
    input_buffer->buffer[0] = '\0';
    input_buffer->input_length = 0;
    return;
  }
  input_buffer->input_length = bytes_read - 1;
  input_buffer->buffer[bytes_read - 1] = '\0';
}

void close_input_buffer(InputBuffer* input_buffer) {
  free(input_buffer->buffer);
  free(input_buffer);
}

int main(int argc, char* argv[]) {
  InputBuffer* input_buffer = new_input_buffer();
  
  while (true) {
    print_prompt();
    read_input(input_buffer);
    if (input_buffer->buffer[0] == '.') {
      switch (do_meta_command(input_buffer)) {
        case (META_COMMAND_SUCCESS):
          continue;
        case (META_COMMAND_UNRECOGNIZED_COMMAND):
          printf("Unrecognized command '%s'\n", input_buffer->buffer);
          continue;
      }
    }
    Statement statement;
    switch (prepare_statement(input_buffer, &statement)) {
      case (PREPARE_SUCCESS):
        break;
      case (PREPARE_UNRECOGNIZED_STATEMENT):
        printf("Unrecognized keyword at start of '%s'\n", input_buffer->buffer);
        continue;
    }
    execute_statement(&statement);
    printf("Executed.\n");
  }
  
  return 0;
}
