#include "memory_handling.h"

int increase_length(int n) {
    return 2 * n + 1;
}

void initial_capacity(Capacity *c) {
    c->arr_len = 0;
    c->allocated_len = INITIAL_LENGTH;
}

void set_capacity_to_zero(Capacity *c) {
    c->arr_len = 0;
    c->allocated_len = 0;
}

void new_string(String *s) {
    s->arr = (char*)malloc(INITIAL_LENGTH * sizeof(char));
    if (s->arr == NULL)
        exit(1);
    initial_capacity(&s->length);
}

void create_strings(Line *l) {
    l->strings.arr = (String*)malloc(INITIAL_LENGTH * sizeof(String));
    if (l->strings.arr == NULL)
        exit(1);
    l->strings.length.allocated_len = INITIAL_LENGTH;
}

void create_point_nums(Line *l) {
    l->point_nums.arr = (long double*)malloc(INITIAL_LENGTH * sizeof(long double));
    if (l->point_nums.arr == NULL)
        exit(1);
    l->point_nums.length.allocated_len = INITIAL_LENGTH;
}

void create_output(Output *output) {
    output->solution = (int**)malloc(INITIAL_LENGTH * sizeof(int*));
    if (output->solution == NULL)
        exit(1);
    initial_capacity(&output->length);
}

void verify_output_length(Output *output) {
    if (output->length.arr_len == output->length.allocated_len) {
        output->length.allocated_len = increase_length(output->length.arr_len);
        output->solution = (int**)realloc(output->solution, output->length.allocated_len * sizeof(int*));

        if (output->solution == NULL)
            exit(1);
    }
}

void verify_string_length(String *s) {
    if (s->length.arr_len + 1 == s->length.allocated_len) {
        s->length.allocated_len = increase_length(s->length.arr_len);
        s->arr = (char*)realloc(s->arr, s->length.allocated_len * sizeof(char));

        if (s->arr == NULL)
            exit(1);
    }
}

void new_line(Line *l) {
    l->comment = false;
    l->error = false;
    l->strings.arr = NULL;
    l->point_nums.arr = NULL;
    set_capacity_to_zero(&l->strings.length);
    set_capacity_to_zero(&l->point_nums.length);
}

void new_row(Row *r) {
    r->arr = (int*)malloc(INITIAL_LENGTH * sizeof(int));
    initial_capacity(&r->length);
}

void verify_row_length(Row *r) {
    if (r->length.arr_len + 1 == r->length.allocated_len) {
        r->length.allocated_len = increase_length(r->length.arr_len);
        r->arr = (int*)realloc(r->arr, r->length.allocated_len * sizeof(int));

        if (r->arr == NULL)
            exit(1);
    }
}

void verify_arr_of_strings_length(Line *l) {
    if (l->strings.length.arr_len == l->strings.length.allocated_len) {
        l->strings.length.allocated_len = increase_length(l->strings.length.arr_len);;
        l->strings.arr = (String*)realloc(l->strings.arr, l->strings.length.allocated_len * sizeof(String));

        if (l->strings.arr == NULL)
            exit(1);
    }
}

void verify_point_nums_length(Line *l) {
    if (l->point_nums.length.arr_len == l->point_nums.length.allocated_len) {
        l->point_nums.length.allocated_len = increase_length(l->point_nums.length.arr_len);
        l->point_nums.arr = (long double*)realloc(l->point_nums.arr, l->point_nums.length.allocated_len * sizeof(long double));

        if (l->point_nums.arr == NULL)
            exit(1);
    }
}

void create_lines(Lines *all_lines) {
    all_lines->arr = (Line*)malloc(INITIAL_LENGTH * sizeof(Line));

    if (all_lines->arr == NULL)
        exit(1);

    initial_capacity(&all_lines->length);
}

void verify_lines_length(Lines *all_lines) {
    if (all_lines->length.arr_len == all_lines->length.allocated_len) {
        all_lines->length.allocated_len = increase_length(all_lines->length.arr_len);
        all_lines->arr = (Line*)realloc(all_lines->arr, all_lines->length.allocated_len * sizeof(Line));

        if (all_lines->arr == NULL)
            exit(1);
    }
}

void free_output(Output *output) {
    for (int i = 0; i < output->length.arr_len; ++i)
        free(output->solution[i]);
    free(output->solution);
}

void free_string(String *s) {
    free(s->arr);
    s->arr = NULL;
}

void free_line(Line *l) {
    for (int i = 0; i < l->strings.length.arr_len; ++i)
        free_string(&(l->strings.arr[i]));

    free(l->point_nums.arr);
    l->point_nums.arr = NULL;

    free(l->strings.arr);
    l->strings.arr = NULL;
}

void free_lines(Lines *all_lines) {
    for (int i = 0; i < all_lines->length.arr_len; ++i)
        free_line(&all_lines->arr[i]);
    free(all_lines->arr);
    all_lines->arr = NULL;
}
