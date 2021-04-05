#ifndef IPP_SMALL_FUNCTIONS_H
#define IPP_SMALL_FUNCTIONS_H

#include "structs.h"
#include "memory_handling.h"

int compare_strings(void const*, void const*);
int compare_numbers(void const*, void const*);
int compare_arr_of_strings(void const*, void const*);
int compare_arr_of_point_nums(void const*, void const*);
int compare_rows(void const*, void const*);

void sort_every_line(Lines*);
void sort_by_strings(Lines*);
void sort_by_numbers(Lines*);

bool equal_lines(Line*, Line*);
bool ignore_line(Line*);

Line* find_first_proper_line(Lines*, int*);
void add_row(Output*, Row*);
void process_all_lines(Lines*, Output*);

void print_error(int);
void print_solution(Output*);

#endif //IPP_SMALL_FUNCTIONS_H
