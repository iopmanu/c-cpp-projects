#include "helper_parser.h"
#include "parser.h"

void writing_operator(token_t *current_source, char _operator, int *current, int shift) {
    current_source->is_number = false;
    current_source->operator= _operator;
    current_source->number = POISON_DOUBLE;

    (*current) += shift;
}

int8_t check_function(const char *string, const char *function, int *shift) {
    int length = 0, _check = true;

    while (_check && function[length] != '\0') {
        if (string[length] == '\0')
            _check = false;
        else if (function[length] != string[length])
            _check = false;
        length++;
    }

    if (_check && string[length] == '(') _check = 0;
    *shift = length;

    return _check;
}

int8_t string_to_double(const char *string, double *number, int *current) {
    while (string[*current] - '0' >= 0 && string[*current] - '0' <= 9) {
        *number = *number * 10 + (string[*current] - '0');
        (*current)++;
    }

    int i = 0;
    double und = 0;

    if (string[*current] == '.') {
        (*current)++;
        if (string[*current] - '0' < 0 || string[*current] - '0' > 9) return 1;

        do {
            und = und * 10 + (string[*current] - '0');
            (*current)++;
            i++;
        } while (string[*current] - '0' >= 0 && string[*current] - '0' <= 9);
    }

    for (; i > 0; i--, und /= 10)
        ;
    *number += und;

    return 0;
}