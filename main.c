#include "memory_handling.h"
#include "parser.h"
#include "functions.h"

int main(void) {
    Lines all_lines;
    create_lines(&all_lines);
    read_lines(&all_lines);

    // sorts every single line by its strings and numbers
    sort_every_line(&all_lines);

    // sorts all lines comparing arrays of strings
    sort_by_strings(&all_lines);

    // sorts all lines comparing arrays of numbers
    sort_by_numbers(&all_lines);

    Output output;
    create_output(&output);

    // processes sorted lines in order to extract solution
    process_all_lines(&all_lines, &output);
    print_solution(&output);

    free_output(&output);
    free_lines(&all_lines);

    return 0;
}



