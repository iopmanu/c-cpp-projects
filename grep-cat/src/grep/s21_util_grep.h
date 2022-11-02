// Copyright 2022 mablever
#ifndef SRC_S21_GREP_LIB_H_
#define SRC_S21_CAT_LIB_H_
#include <stdio.h>
// exceptions
#include <assert.h>
// using getopt
#include <getopt.h>
// using calloc
#include <stdlib.h>
// using string functions to compare
#include <string.h>
//
#include <unistd.h>
// file info
#include <sys/stat.h>
// using different inttypes
#include <inttypes.h>
// regex processing
#include <regex.h>

#define NDEBUG  // off asserts

#define MAX_PATTERN_SIZE 512  // constant for pattern buffer size

// This enum for some error types which can be occured in grep
enum GREP {
    GREP_SUCCES = 0,           // absolutely succes
    GREP_NULLPTR = 1,          // for any nullptr
    GREP_INVALIDMODE = 2,      // for invalid option in command line
    GREP_DIRERROR = 3,         // for argue dir instead of file
    GREP_INCORRECT_INPUT = 4,  // for argc incorrect input
    GREP_FILEERR = 5,          // for any file errors
    GREP_REGERR = 6,           // for regular expressions errors
};

// This enum for all possible flags which can be used in grep
enum GREP_FLAGS {
    PATTERN = 01,                         // -e
    IGNORE_UPPER_LOWER = 02,              // -i
    INVERT = 04,                          // -v
    COUNT_OF_LINES_ONLY = 010,            // -c
    MATCHING_FILES_ONLY = 020,            // -l
    PRECEDE_LINE_WITH_NUMBER = 040,       // -n
    WITHOUT_FILENAME_PRECEDING = 0100,    // -h
    SUPPRESS_ERROR_MESSAGE = 0200,        // -s
    TAKE_REGEXES = 0400,                  // -f file
    MATCHED_PARTS_MATCHING_LINE = 01000,  // -o
};

// This structure to collect all possible command line information
typedef struct options_s {
    char patterns[MAX_PATTERN_SIZE];  // patterns buffer
    int16_t opt;                      // options from command line
} options_t;

// This structure to process any matches in file and collect term-symbol of this
// file
typedef struct grep_config_s {
    size_t buffer_size;  // current size of the expanding buffer
    int current_line;    // current processed line
    int match_count;     // current quantity of matches found
    char term_symbol;    // term symbol for this file
} grep_config_t;

// This function to get options from a command line
enum GREP grep_get_param(int argc, char **argv, int *optind_index,
                         options_t *options);
// This function to print any erros occured in process
void grep_perror(enum GREP errcode, int8_t s_option);
// This function to add patterns to the options structure
void add_pattern(options_t *options, char *source);
// This function to check any options conflicts
void checking_conflict(options_t *options, int files_quantity);
// This function for safety file openning and checking any errors
enum GREP open_file(const char *filename, FILE **current_file);
// This function for regular expressions preprocessing and recomp function
// calling
int reg_file_processing(options_t *opt, regex_t *reg);
// This function for output by options
void output_matched_line(options_t *opt, const char *filename, const char *line,
                         grep_config_t config, int n_start, int n_finish);
// This function for grep file processing
void grep_file_without_o(options_t *opt, regex_t *reg, FILE *file,
                         const char *filename);
// This function for processing -o option in grep
void matched_parts_matched_lines(options_t *opt, regex_t *reg, FILE *file,
                                 const char *filename);
// This function for taking regular expressions from another file
enum GREP get_regular_from_another_file(options_t *options, char *filename);
#endif  // SRC_S21_GREP_LIB_H_