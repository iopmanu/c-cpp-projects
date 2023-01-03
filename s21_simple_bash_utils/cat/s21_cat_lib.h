// Copyright 2022 mablever

#ifndef SRC_S21_CAT_LIB_H_
#define SRC_S21_CAT_LIB_H_

#include <stdio.h>
// exceptions
#include <assert.h>
// using getopt
#include <getopt.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
// file info
#include <sys/stat.h>
// usint int8_t
#include <inttypes.h>

enum CAT {
    CAT_SUCCES = 0,
    CAT_NULLPTR = 1,
    CAT_INVALIDMODE = 2,
    CAT_DIRERROR = 3,
    CAT_INCORRECT_INPUT = 4,
    CAT_FILEERR = 5
};

enum CAT_FLAGS {
    NUM_NONBLANK = 01,
    NUM_ALL = 02,
    PRINT_NON_PRINTS = 04,
    PRINT_END_LINES = 010,
    PRINT_TABS = 020,
    SQUEEZE_BLANK = 040
};

// Using this structure in long_opt
/* struct option {
    const char *name;
    int has_arg;
    int *flag;
    int val;
}
*/

// This function to parse options of the command line
enum CAT cat_get_param(int argc, char **argv, int *optind_index, int *flags);
// This function for checking validity of file parametrs
enum CAT open_file(const char *filename, FILE **current_file);
// This function to output error to the stderr
void catperror(enum CAT errcode);
// This function is for file proccessing
void cat_file(FILE *current_file, FILE *out, const int flags);
// This function for previous symbols caching
void new_cache(int symbol, int *current_cache);
// This function is for checking -n -b at the same time and turning off -n if
// it's true
void checking_conflict(int *options);
// This function is for proessing -v option
void proccessing_v_options_part(char symbol, FILE *out);

#endif  // SRC_S21_CAT_LIB_H_
