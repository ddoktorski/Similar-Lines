#include "parser.h"
#include "memory_handling.h"

void upper_to_lower(int *letter) {
    if (UPPER_A <= *letter && *letter <= UPPER_Z)
        *letter += LOWER_TO_UPPER;
}

int skip_line() {
    int c;
    do {
        c = getchar();
    } while (c != NEW_LINE && c != EOF);
    return c;
}

int skip_whitespaces() {
    int c;
    do {
        c = getchar();
    } while (c != NEW_LINE && c != EOF && (c == SPACE || (WHITESPACE_MIN <= c && c <= WHITESPACE_MAX)));

    if (c != NEW_LINE && c != EOF)
        ungetc(c, stdin);
    return c;
}

// before reading line
// checks if the line is comment or EOF
// if not then puts the char back to stdin by function ungetc
void check_first_element(Line *l, bool *end_of_file, bool *end_of_line) {
    int first_element = getchar();

    if (first_element == HASH) {
        l->comment = true;
        *end_of_line = true;
        if (skip_line() == EOF)
            *end_of_file = true;
    }
    else if(first_element == EOF)
        *end_of_file = true;
    else
        ungetc(first_element, stdin);
}

// reads string until first whitespace character
// new string is stored in s
// *error becomes true if there is illegal character in the string
void read_string(String *s, bool *error, bool *end_of_file, bool *end_of_line) {
    int c;

    while (((c = getchar()) != SPACE) && (WHITESPACE_MIN > c || c > WHITESPACE_MAX) && (c != EOF)) {
        if (ASCII_MIN > c || c > ASCII_MAX) {
            *error = true;
            if (skip_line() == EOF)
                *end_of_file = true;
            return;
        }
        verify_string_length(s);
        // every string is saved with lower letters, so if c is upper letter we change it to lower
        upper_to_lower(&c);
        s->arr[s->length.arr_len++] = (char) c;
    }
    // checks last loaded element
    *end_of_line = (c == NEW_LINE) ? true : false;
    *end_of_file = (c == EOF) ? true: false;
}

// decides if string s needs to be added to array of strings or array of numbers in line l
void process_string(Line *l, String *s) {
    // base of number, -1 means it is not a number
    int base = check_if_number(s);

    if (base == - 1)
        add_string(l, s);
    else
        add_number(l, s, base);
}

// reads strings and numbers and adds them to the line until new line or EOF
void read_line(Line *l, bool *end_of_file) {
    new_line(l);
    bool end_of_line = false;
    bool error = false;
    check_first_element(l, end_of_file, &end_of_line);

    while (!end_of_line && !(*end_of_file)) {
        int first = skip_whitespaces();

        if (first == NEW_LINE)
            end_of_line = true;
        else if (first == EOF)
            *end_of_file = true;
        else {
            String temp_string;
            new_string(&temp_string);
            read_string(&temp_string, &error, end_of_file, &end_of_line);

            if (error) {
                l->error = true;
                free_string(&temp_string);
                end_of_line = true;
            }
            else {
                // in order to mark the end of string
                temp_string.arr[temp_string.length.arr_len] = '\0';

                process_string(l, &temp_string);
            }
        }
    }
}

// reads all lines until EOF
void read_lines(Lines *all_lines) {
    bool end_of_file = false;

    while (!end_of_file) {
        verify_lines_length(all_lines);
        read_line(&all_lines->arr[all_lines->length.arr_len], &end_of_file);

        // number of line is length of all lines plus 1
        all_lines->arr[all_lines->length.arr_len].number = all_lines->length.arr_len + 1;
        all_lines->length.arr_len++;
    }
}

// adds number with the base (int base) which is in the string s to the array of numbers in line l
// functions stroull and strtold convert string to number
void add_number(Line *l, String *s, int base) {
    if (l->point_nums.arr == NULL)
        create_point_nums(l);

    verify_point_nums_length(l);
    long double new_value;

    if (base == HEX_BASE || base == OCTAL_BASE || base == DECIMAL_BASE) {
        new_value = (long double) strtoull(s->arr, NULL, base);
        // strtoull returns ULLONG_MAX also when the number is greater than ULLONG_MAX
        // check_if_out_of_range verifies if the number is really ULLONG_MAX
        if (new_value == ULLONG_MAX) {
            if (check_if_out_of_range(s, base)) {
                add_string(l, s);
                return;
            }
        }
    }
    else // base == 1 means convert to long double
        new_value = strtold(s->arr, NULL);

    // if the number is integer not included in allowed range then add it as string
    if (base != 1 && (LLONG_MIN > new_value || new_value > ULLONG_MAX)) {
        add_string(l, s);
        return;
    }

    l->point_nums.arr[l->point_nums.length.arr_len++] = new_value;
    free_string(s);
}

// adds string s to array of strings in the line l
void add_string(Line *l, String *s) {
    if (l->strings.arr == NULL)
        create_strings(l);

    verify_arr_of_strings_length(l);
    l->strings.arr[l->strings.length.arr_len].length.arr_len = s->length.arr_len;
    l->strings.arr[l->strings.length.arr_len++].arr = s->arr;
}

// if string is a number returns its base (base of float is 1), otherwise returns -1
int check_if_number(String *s) {
    if (check_if_inf(s))
        return 1;

    if (s->length.arr_len > 0) {
        if (s->arr[0] == DIGIT_MIN) {
            if (s->length.arr_len > 1 && s->arr[1] == LOWER_X && check_if_hex(s))
                return HEX_BASE;
            else if (check_if_octal(s))
                return OCTAL_BASE;
            else if (check_if_decimal(s))
                return DECIMAL_BASE;
            else if (check_if_float(s))
                return 1;
        }
        else if (DIGIT_MIN < s->arr[0] && s->arr[0] <= DIGIT_MAX) {
            if (check_if_decimal(s))
                return DECIMAL_BASE;
            else if (check_if_float(s))
                return 1;
        }
        else if (check_if_float(s))
            return 1;
    }

    return -1;
}

bool check_if_decimal(String *s) {
    int start_index = (s->arr[0] == MINUS) ? 1 : 0;

    for (int i = start_index; i < s->length.arr_len; ++i) {
        if (DIGIT_MIN > s->arr[i] || s->arr[i] > DIGIT_MAX)
            return false;
    }

    return true;
}

bool check_if_octal(String *s) {
    for (int i = 1; i < s->length.arr_len; ++i) {
        if (DIGIT_MIN > s->arr[i] || s->arr[i] > DIGIT_7)
            return false;
    }

    return true;
}

bool check_if_hex(String *s) {
    for (int i = 2; i < s->length.arr_len; ++i) {
        if (!(DIGIT_MIN <= s->arr[i] && s->arr[i] <= DIGIT_MAX)
            && !(LOWER_A <= s->arr[i] && s->arr[i] <= LOWER_F))
            return false;
    }
    return true;
}

bool check_if_float(String *s) {
    bool is_e = false;
    bool is_dot = false;
    int start_index = 0;

    if (s->arr[0] == MINUS || s->arr[0] == PLUS) {
        if (s->length.arr_len == 1)
            return false;
        start_index = 1;
    }

    if (s->arr[start_index] == DOT &&
        (s->length.arr_len == start_index + 1 || s->arr[start_index + 1] == LOWER_E)) return false;

    for (int i = start_index; i < s->length.arr_len; ++i) {
        if (s->arr[i] == MINUS || s->arr[i] == PLUS) {
            if (s->arr[i - 1] != LOWER_E || i == s->length.arr_len - 1)
                return false;
        }
        else if (s->arr[i] == LOWER_E) {
            if (is_e || i == start_index || i == s->length.arr_len - 1)
                return false;
            is_e = true;
        } else if (s->arr[i] == DOT) {
            if (is_dot || is_e)
                return false;
            is_dot = true;
        } else {
            if (DIGIT_MIN > s->arr[i] || s->arr[i] > DIGIT_MAX)
                return false;
        }
    }
    return true;
}

bool check_if_inf(String *s) {
    if (s->length.arr_len == 3)
        return strcmp(s->arr, INF) == 0;
    else if (s->length.arr_len == 4)
        return strcmp(s->arr, INF_PLUS) == 0 || strcmp(s->arr, INF_MINUS) == 0;

    return false;
}

bool check_if_out_of_range(String *s, int base) {
    if (base == DECIMAL_BASE)
        return strcmp(s->arr, ULL_DECIMAL_MAX);
    else if (base == OCTAL_BASE)
        return strcmp(s->arr, ULL_OCTAL_MAX);
    else if (base == HEX_BASE)
        return strcmp(s->arr, ULL_HEX_MAX);

    return false;
}

