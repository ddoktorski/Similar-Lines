#ifndef IPP_SMALL_MEMORY_HANDLING_H
#define IPP_SMALL_MEMORY_HANDLING_H

#include "structs.h"

#define INITIAL_LENGTH 10

void initial_capacity(Capacity*);
void set_capacity_to_zero(Capacity*);

void create_lines(Lines*);
void create_strings(Line*);
void create_point_nums(Line*);
void create_output(Output*);
void new_line(Line*);
void new_string(String*);
void new_row(Row*);

void verify_string_length(String*);
void verify_row_length(Row*);
void verify_arr_of_strings_length(Line*);
void verify_lines_length(Lines*);
void verify_point_nums_length(Line*);
void verify_output_length(Output*);

void free_string(String*);
void free_line(Line*);
void free_lines(Lines*);
void free_output(Output*);

#endif //IPP_SMALL_MEMORY_HANDLING_H
