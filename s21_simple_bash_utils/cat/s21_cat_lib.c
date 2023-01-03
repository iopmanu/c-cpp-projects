// Copyright 2022 mablever

#include "./s21_cat_lib.h"

enum CAT cat_get_param(int argc, char **argv, int *optind_index, int *flags) {
    assert(argv != NULL);
    enum CAT status = CAT_SUCCES;
    if (argv == NULL || *argv == NULL) {
        status = CAT_NULLPTR;
    }
    /*if (argc <= 3) {
        status = CAT_INCORRECT_INPUT;
    }*/

    char *options = "bevEnstT";
    int getopt_value = 0;
    /* no_argument (or 0) if the option does not take an argument
     * If flag is NULL, then getopt_long() returns val */
    static struct option long_options[] = {
        {"number-nonblank", no_argument, NULL, 'b'},
        {"number", no_argument, NULL, 'n'},
        {"squeeze-blank", no_argument, NULL, 's'},
        {NULL, 0, NULL, 0}};

    // getopt_value == -1 => break, because there is no options more
    while (((getopt_value =
                 getopt_long(argc, argv, options, long_options, NULL)) != -1 &&
            status == CAT_SUCCES)) {
        switch (getopt_value) {
            case 'b':
                *flags |= NUM_NONBLANK;
                break;
            case 'e':
                *flags |= PRINT_NON_PRINTS | PRINT_END_LINES;
                break;
            case 'v':
                *flags |= PRINT_NON_PRINTS;
                break;
            case 'E':
                *flags |= PRINT_END_LINES;
                break;
            case 'n':
                *flags |= NUM_ALL;
                break;
            case 's':
                *flags |= SQUEEZE_BLANK;
                break;
            case 't':
                *flags |= PRINT_NON_PRINTS | PRINT_TABS;
                break;
            case 'T':
                *flags |= PRINT_TABS;
                break;
            default:
                if (optopt != 0) status = CAT_INVALIDMODE;
                break;
        }
    }

    *optind_index = optind;

    return status;
}

void catperror(enum CAT errcode) {
    // restrict is a service command in c
    const char *restrict error = NULL;

    switch (errcode) {
        case CAT_SUCCES:
            error = "Succes";
            break;
        case CAT_INVALIDMODE:
            error = "Invalid option mode";
            break;
        case CAT_DIRERROR:
            error = "Error with file opening";
            break;
        case CAT_NULLPTR:
            error = "NULL pointer error";
            break;
        case CAT_INCORRECT_INPUT:
            error = "Incorrect input";
            break;
        case CAT_FILEERR:
            error = "Invalid file parametr";
            break;

        default:
            error = "Unknown error";
            break;
    }

    fprintf(stderr, "Code : %s\n", error);
}

enum CAT open_file(const char *filename, FILE **current_file) {
    assert(filename != NULL);
    enum CAT fopen_status = CAT_SUCCES;
    if (filename == NULL) {
        fopen_status = CAT_NULLPTR;
    }

    // Struct to collect file info
    struct stat info;
    int stat_code = stat(filename, &info);

    // S_ISDIR - macro which returns non-zero if the file is a directory
    if (stat_code == 0 && S_ISDIR(info.st_mode)) {
        fopen_status = CAT_DIRERROR;
    } else if (stat_code == 0 && S_ISREG(info.st_mode)) {
        *current_file = fopen(filename, "r");
        if (*current_file == NULL) {
            fopen_status = CAT_FILEERR;
        }
    } else {
        fopen_status = CAT_FILEERR;
    }

    return fopen_status;
}

void cat_file(FILE *current_file, FILE *out, const int options) {
    int symbol;
    int cache[2] = {'\0', '\n'};
    int line_number = 1;

    while ((symbol = fgetc(current_file)) != EOF) {
        if ((options & SQUEEZE_BLANK) && (symbol == '\n') &&
            (cache[0] == '\n') && (cache[1] == '\n')) {
            new_cache(symbol, cache);
            // Skip any proccessing
            continue;
        }

        if ((options & NUM_ALL ||
             ((options & NUM_NONBLANK) && symbol != '\n')) &&
            cache[1] == '\n') {
            fprintf(out, "%6d\t", line_number++);
            new_cache(symbol, cache);
        }

        if (options & PRINT_END_LINES && symbol == '\n') {
            putc('$', out);
        }

        if (options & PRINT_NON_PRINTS) {
            // processing_v_options(symbol, out);
            proccessing_v_options_part(symbol, out);
            continue;
        }

        // if (options & PRINT_END_LINES && symbol == '\n') {
        //     putc('$', out);
        // }

        if (options & PRINT_TABS && symbol == '\t') {
            putc('^', out);
            symbol = 'I';
        }

        // printf("\nSymbol:%c\n", symbol);  -- debug
        putc(symbol, out);
        new_cache(symbol, cache);
    }
}

void new_cache(int symbol, int *current_cache) {
    assert(current_cache != NULL);
    current_cache[0] = current_cache[1];
    current_cache[1] = symbol;
}

void checking_conflict(int *options) {
    assert(options != NULL);
    if ((*options & NUM_NONBLANK) && (*options & NUM_ALL)) {
        *options &= ~NUM_ALL;
    }
}

void proccessing_v_options_part(char symbol, FILE *out) {
    if (symbol < -96) {
        fprintf(out, "M-^%c", symbol + 192);
    } else if (symbol < 0) {
        fprintf(out, "M-%c", symbol + 128);
    } else if (symbol == 9 || symbol == 10) {
        fprintf(out, "%c", symbol);
    } else if (symbol < 32 && symbol != '\n') {
        fprintf(out, "^%c", symbol + 64);
    } else if (symbol < 127) {
        fprintf(out, "%c", symbol);
    } else {
        fprintf(out, "^?");
    }
}

// End code
