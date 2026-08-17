#include "meta_command_result.h"
#include "structs/input_buffer.h"
#include <string.h>
#include <stdlib.h>
MetaCommandResult do_meta_command(InputBuffer* input_buffer) {
  if (strcmp(input_buffer->buffer, ".exit") == 0) {
    exit(EXIT_SUCCESS);
  } else {
    return META_COMMAND_UNRECOGNIZED_COMMAND;
  }
}
