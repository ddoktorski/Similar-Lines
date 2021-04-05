#ifndef IPP_SMALL_STRUCTS_H
#define IPP_SMALL_STRUCTS_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct Capacity;
struct String;
struct Strings;
struct LongDoubles;
struct Line;
struct Lines;
struct Output;
struct Row;

// auxiliary struct to store length of array and allocated length
typedef struct Capacity {
    int arr_len;
    int allocated_len;
} Capacity;

// struct to store single string
typedef struct String {
    char *arr;
    Capacity length;
} String;

// struct to store array of strings
typedef struct Strings {
    String *arr;
    Capacity length;
} Strings;

// struct to store array of long doubles
typedef struct LongDoubles {
    long double *arr;
    Capacity length;
} LongDoubles;

typedef struct Line {
    int number;
    Strings strings;
    LongDoubles point_nums;
    bool error;
    bool comment;
} Line;

// struct to store array of lines
typedef struct Lines {
    Line *arr;
    Capacity length;
} Lines;

// auxiliary struct to store array of ints
typedef struct Row {
    int *arr;
    Capacity length;
} Row;

typedef struct Output {
    int **solution;
    Capacity length;
} Output;

#endif //IPP_SMALL_STRUCTS_H
