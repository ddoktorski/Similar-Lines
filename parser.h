#ifndef IPP_SMALL_PARSER_H
#define IPP_SMALL_PARSER_H

#include <limits.h>
#include "structs.h"

#define ASCII_MIN 33
#define ASCII_MAX 126

#define UPPER_A 65
#define UPPER_Z 90
#define LOWER_TO_UPPER 32

#define LOWER_A 97
#define LOWER_E 101
#define LOWER_F 102
#define LOWER_X 120

#define DOT 46
#define HASH 35

#define SPACE 32
#define NEW_LINE 10
#define WHITESPACE_MIN 9
#define WHITESPACE_MAX 13

#define MINUS 45
#define PLUS 43
#define DIGIT_MIN 48 // 0
#define DIGIT_MAX 57 // 9
#define DIGIT_7 55

#define HEX_BASE 16
#define DECIMAL_BASE 10
#define OCTAL_BASE 8

#define ULL_DECIMAL_MAX "18446744073709551615"
#define ULL_OCTAL_MAX "01777777777777777777777"
#define ULL_HEX_MAX "0xffffffffffffffff"

#define INF "inf"
#define INF_PLUS "+inf"
#define INF_MINUS "-inf"

void upper_to_lower(int*);
int skip_line(void);
int skip_whitespaces(void);

void check_first_element(Line*, bool *, bool*);
void read_string(String*, bool*, bool*, bool*);
void read_line(Line*, bool*);
void read_lines(Lines*);
void process_string(Line*, String*);

int check_if_number(String*);
bool check_if_inf(String*);
bool check_if_decimal(String*);
bool check_if_octal(String*);
bool check_if_hex(String*);
bool check_if_float(String*);
bool check_if_out_of_range(String*, int);

void add_number(Line*, String*, int);
void add_string(Line*, String*);

#endif //IPP_SMALL_PARSER_H