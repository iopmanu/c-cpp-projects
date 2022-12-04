#include "s21_util_grep.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
    enum GREP code = GREP_SUCCES;
    options_t *options = calloc(1, sizeof(options_t));
    int nonoptions_part = 0;

    code = grep_get_param(argc, argv, &nonoptions_part, options);
    checking_conflict(options, argc - nonoptions_part);

    int regcomp_error = 0;
    regex_t regular;
    if (code == GREP_SUCCES) {
        regcomp_error = reg_file_processing(options, &regular);
    }

    if (regcomp_error != 0) {
        code = GREP_REGERR;
    }

    // printf("Here are patterns %s", options->patterns);

    if (code == GREP_SUCCES) {
        while ((nonoptions_part++ < argc) && (code == GREP_SUCCES)) {
            FILE *file = NULL;
            char *filename = argv[nonoptions_part - 1];

            code = open_file(filename, &file);

            if (code == GREP_SUCCES &&
                !(options->opt & MATCHED_PARTS_MATCHING_LINE)) {
                grep_file_without_o(options, &regular, file, filename);
                fclose(file);
            } else if (code == GREP_SUCCES &&
                       (options->opt & MATCHED_PARTS_MATCHING_LINE)) {
                matched_parts_matched_lines(options, &regular, file, filename);
                fclose(file);
            }
        }
    }

    if (code != GREP_SUCCES) {
        grep_perror(code, options->opt & SUPPRESS_ERROR_MESSAGE);
    }

    free(options);
    regfree(&regular);
    return code;
}