#ifndef PREPARE_RESULTS_H
#define PREPARE_RESULTS_H
#include "structs/input_buffer.h"
#include "structs/statement.h"
#include "enums/prepare_result_enum.h"

PrepareResult prepare_statement(InputBuffer* input_buffer, Statement* statement);
void execute_statement(Statement* statement);
#endif
