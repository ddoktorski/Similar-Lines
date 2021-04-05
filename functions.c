#include "functions.h"
#include "memory_handling.h"

int compare_strings(void const *a, void const *b) {
    const String *A = a;
    const String *B = b;
    return strcmp(A->arr, B->arr);
}

int compare_numbers(void const *a, void const *b) {
    const long double *A = a;
    const long double *B = b;

    if (*A == *B) return 0;
    else if (*A < *B) return -1;
    return 1;
}

int compare_arr_of_strings(void const *a, void const *b) {
    const Line *A = a;
    const Line *B = b;
    if (A->strings.length.arr_len < B->strings.length.arr_len)
        return -1;
    else if (A->strings.length.arr_len > B->strings.length.arr_len)
        return 1;
    else {
        int result = 0;
        int i = 0;
        while (result == 0 && i < A->strings.length.arr_len) {
            result = strcmp(A->strings.arr[i].arr, B->strings.arr[i].arr);
            i++;
        }
        return result;
    }
}

int compare_arr_of_point_nums(void const *a, void const *b) {
    const Line *A = a;
    const Line *B = b;

    if (A->point_nums.length.arr_len < B->point_nums.length.arr_len)
        return -1;
    else if (A->point_nums.length.arr_len > B->point_nums.length.arr_len)
        return 1;
    else {
        int result = 0;
        int i = 0;
        while (result == 0 && i < A->point_nums.length.arr_len) {
            if (A->point_nums.arr[i] < B->point_nums.arr[i])
                result = -1;
            else if (A->point_nums.arr[i] > B->point_nums.arr[i])
                result = 1;
            i++;
        }
        return result;
    }
}

int compare_rows(void const *a, void const *b) {
    const int *A = *(const int **)a;
    const int *B = *(const int **)b;

    if (A[0] < B[0])
        return -1;
    return 1;
}

void sort_by_strings(Lines *all_lines) {
    qsort(all_lines->arr, all_lines->length.arr_len, sizeof(Line), compare_arr_of_strings);
}

void sort_by_numbers(Lines *all_lines) {
    qsort(all_lines->arr, all_lines->length.arr_len, sizeof(Line), compare_arr_of_point_nums);
}

void sort_every_line(Lines *all_lines) {
    for (int i = 0; i < all_lines->length.arr_len; ++i) {
        qsort(all_lines->arr[i].strings.arr, all_lines->arr[i].strings.length.arr_len, sizeof(String), compare_strings);
        qsort(all_lines->arr[i].point_nums.arr, all_lines->arr[i].point_nums.length.arr_len, sizeof(long double), compare_numbers);
    }
}

// adds new row to 2d array in output
void add_row(Output *output, Row *current) {
    current->arr[current->length.arr_len] = -1;
    output->solution[output->length.arr_len++] = current->arr;
}

// finds first non empty line or returns NULL
Line* find_first_proper_line(Lines *all_lines, int *i) {
    while (*i < all_lines->length.arr_len && ignore_line(&all_lines->arr[*i])) {
        (*i)++;
    }

    if (*i == all_lines->length.arr_len)
        return NULL;

    return &all_lines->arr[*i];
}

void process_all_lines(Lines *all_lines, Output *output) {
    Row current;
    new_row(&current);

    int i = 0;
    Line *last = find_first_proper_line(all_lines, &i);

    if (last == NULL) {
        free(current.arr);
        return;
    }

    for (i = 0; i < all_lines->length.arr_len; ++i) {
        if (all_lines->arr[i].error)
            print_error(all_lines->arr[i].number);
        else {
            if (!ignore_line(&all_lines->arr[i])) {
                    if (equal_lines(last, &all_lines->arr[i])) {
                        verify_row_length(&current);
                        current.arr[current.length.arr_len++] = all_lines->arr[i].number;
                    }
                    else {
                        verify_output_length(output);

                        // current row becomes a row in output
                        add_row(output, &current);

                        // reset row
                        int *new_row = (int*)malloc(10 * sizeof(int));
                        current.arr = new_row;
                        current.length.arr_len = 1;
                        current.length.allocated_len = 10;

                        // current line becomes last
                        last = &all_lines->arr[i];
                        current.arr[0] = last->number;
                    }
                }
            }
        }

    // if current row is not empty we need to add it to the output
    if (current.length.arr_len != 0) {
        verify_output_length(output);
        add_row(output, &current);
    }

    // sorts the output
    qsort(output->solution, output->length.arr_len, sizeof(int*), compare_rows);
}

bool equal_lines(Line *l1, Line *l2) {
    // compares lengths of arrays
    if ((l1->strings.length.arr_len != l2->strings.length.arr_len)
        || (l1->point_nums.length.arr_len != l2->point_nums.length.arr_len)) {
        return false;
    }

    // compares array of strings
    for (int i = 0; i < l1->strings.length.arr_len; ++i) {
        if (l1->strings.arr[i].length.arr_len != l2->strings.arr[i].length.arr_len)
            return false;
        if (strcmp(l1->strings.arr[i].arr, l2->strings.arr[i].arr) != 0) {
            return false;
        }
    }

    // compares array of long doubles
    for (int i = 0; i < l1->point_nums.length.arr_len; ++i) {
        if (l1->point_nums.arr[i] != l2->point_nums.arr[i])
            return false;
    }

    return true;
}

bool ignore_line(Line *l) {
    return l->comment || (l->strings.arr == NULL && l->point_nums.arr == NULL);
}

void print_solution(Output *output) {
    for (int i = 0; i < output->length.arr_len; ++i) {
        printf("%d", output->solution[i][0]);
        int j = 1;
        while (output->solution[i][j] != -1) {
            printf(" %d", output->solution[i][j]);
            j++;
        }
        printf("\n");
    }
}

void print_error(int x) {
    fprintf(stderr, "ERROR %d\n", x);
}

