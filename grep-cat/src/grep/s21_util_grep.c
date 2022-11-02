#include "s21_util_grep.h"

enum GREP grep_get_param(int argc, char **argv, int *optind_index,
                         options_t *options) {
    assert(argv != NULL);
    enum GREP status = GREP_SUCCES;
    if (argv == NULL || *argv == NULL) {
        status = GREP_NULLPTR;
    }

    const char *possible_options = "e:ivclnhsf:o";
    int8_t getopt_value = 0;

    while (((getopt_value = getopt(argc, argv, possible_options)) != -1) &&
           (status == GREP_SUCCES)) {
        switch (getopt_value) {
            case 'e':
                options->opt |= PATTERN;
                add_pattern(options, optarg);
                break;
            case 'i':
                options->opt |= IGNORE_UPPER_LOWER;
                break;
            case 'v':
                options->opt |= INVERT;
                break;
            case 'c':
                options->opt |= COUNT_OF_LINES_ONLY;
                break;
            case 'l':
                options->opt |= MATCHING_FILES_ONLY;
                break;
            case 'n':
                options->opt |= PRECEDE_LINE_WITH_NUMBER;
                break;
            case 'h':
                options->opt |= WITHOUT_FILENAME_PRECEDING;
                break;
            case 's':
                options->opt |= SUPPRESS_ERROR_MESSAGE;
                break;
            case 'o':
                options->opt |= MATCHED_PARTS_MATCHING_LINE;
                break;
            case 'f':
                // status = get_regular_from_another_file(options, optarg);
                break;
            case '?':
            case ':':
            default:
                if (optopt != 0) status = GREP_INVALIDMODE;
                break;
        }
    }

    if (strcmp(options->patterns, "\0") == 0 && optind < argc) {
        add_pattern(options, argv[optind++]);
    }

    *optind_index = optind;

    return status;
}

void add_pattern(options_t *options, char *source) {
    // assert(source != NULL);
    if (source != NULL) {
        size_t current_pattern_size = strlen(options->patterns);
        size_t source_size = strlen(source);

        if (current_pattern_size + source_size < MAX_PATTERN_SIZE) {
            sprintf((options->patterns) + current_pattern_size, ("%s"), source);
        }
    }
}

void checking_conflict(options_t *options, int files_quantity) {
    if (options->opt & MATCHING_FILES_ONLY) {
        options->opt &= ~(COUNT_OF_LINES_ONLY);
        options->opt &= ~(MATCHED_PARTS_MATCHING_LINE);
        options->opt &= ~(PRECEDE_LINE_WITH_NUMBER);
        options->opt &= ~(WITHOUT_FILENAME_PRECEDING);
    } else if (options->opt & COUNT_OF_LINES_ONLY) {
        options->opt = COUNT_OF_LINES_ONLY;
        // options->opt &= ~(MATCHED_PARTS_MATCHING_LINE);
        // options->opt &= ~(PRECEDE_LINE_WITH_NUMBER);
    }
    if (files_quantity == 1) {
        options->opt |= WITHOUT_FILENAME_PRECEDING;
    }
}

void grep_perror(enum GREP errcode, int8_t s_option) {
    const char *restrict error = " ";

    switch (errcode) {
        case GREP_SUCCES:
            error = "Succes";
            break;
        case GREP_INVALIDMODE:
            error = "Invalid option mode";
            break;
        case GREP_DIRERROR:
            error = "Error with file opening";
            break;
        case GREP_NULLPTR:
            error = "NULL pointer error";
            break;
        case GREP_INCORRECT_INPUT:
            error = "Incorrect input";
            break;
        case GREP_FILEERR:
            if ((s_option & SUPPRESS_ERROR_MESSAGE) == 0) {
                error = "Invalid file parametr";
            }
            break;
        case GREP_REGERR:
            error = "Invalid regular expression";
            break;

        default:
            error = "Unknown error";
            break;
    }

    fprintf(stderr, "Code : %s\n", error);
}

enum GREP open_file(const char *filename, FILE **current_file) {
    assert(filename != NULL);
    enum GREP fopen_status = GREP_SUCCES;
    if (filename == NULL) {
        fopen_status = GREP_NULLPTR;
    }

    // Struct to collect file info
    struct stat info;
    int stat_code = stat(filename, &info);

    // S_ISDIR - macro which returns non-zero if the file is a directory
    if (stat_code == 0 && S_ISDIR(info.st_mode)) {
        fopen_status = GREP_DIRERROR;
    } else if (stat_code == 0 && S_ISREG(info.st_mode)) {
        *current_file = fopen(filename, "r");
        if (*current_file == NULL) {
            fopen_status = GREP_FILEERR;
        }
    } else {
        fopen_status = GREP_FILEERR;
    }

    return fopen_status;
}

int reg_file_processing(options_t *opt, regex_t *reg) {
    assert(reg != NULL);
    assert(opt != NULL);
    int regcomp_flags = 0;

    if (opt->opt & IGNORE_UPPER_LOWER) {
        regcomp_flags |= REG_ICASE;
    }
    if (opt->opt & COUNT_OF_LINES_ONLY) {
        regcomp_flags |= REG_NOSUB;
    }

    return regcomp(reg, opt->patterns, regcomp_flags);
}

void grep_file_without_o(options_t *opt, regex_t *reg, FILE *file,
                         const char *filename) {
    if ((opt->opt & MATCHED_PARTS_MATCHING_LINE) == 0) {
        grep_config_t config = {0, 1, 0, '\n'};
        char *current_line = NULL;
        ssize_t quantity_of_counted = 0;

        while ((quantity_of_counted = getline(
                    &current_line, &(config.buffer_size), file)) != -1) {
            // function to find regular expression matching in file
            int is_reg = regexec(reg, current_line, 0, NULL, 0);
            int8_t is_matched = 0;
            if ((!(opt->opt & INVERT) && (is_reg == 0)) ||
                ((opt->opt & INVERT) && (is_reg != 0))) {
                is_matched = 1;
                config.match_count++;
            }

            if (!(opt->opt & MATCHED_PARTS_MATCHING_LINE) && is_matched) {
                output_matched_line(opt, filename, current_line, config, 0, 0);
            }

            config.current_line++;
        }

        if (opt->opt & COUNT_OF_LINES_ONLY) {
            if (!(opt->opt & WITHOUT_FILENAME_PRECEDING)) {
                printf("%s:", filename);
            }
            printf("%d\n", config.match_count);
        }

        if (opt->opt & MATCHING_FILES_ONLY) {
            printf("%s\n", filename);
        }

        if (current_line != NULL) {
            free(current_line);
        }
    }
}

void output_matched_line(options_t *opt, const char *filename, const char *line,
                         grep_config_t config, int n_start, int n_finish) {
    // assert(filename == NULL);
    if (filename == NULL) return;
    if (!(opt->opt & COUNT_OF_LINES_ONLY) && opt->opt & MATCHING_FILES_ONLY) {
        // printf("%s:", filename);
        return;
    }
    if (!(opt->opt & COUNT_OF_LINES_ONLY) &&
        !(opt->opt & WITHOUT_FILENAME_PRECEDING)) {
        printf("%s:", filename);
    }
    if (!(opt->opt & COUNT_OF_LINES_ONLY) &&
        opt->opt & PRECEDE_LINE_WITH_NUMBER) {
        printf("%d:", config.current_line);
    }
    if (!(opt->opt & COUNT_OF_LINES_ONLY) && n_start < n_finish &&
        n_finish != 0) {
        printf("%.*s\n", (n_finish - n_start), (line + n_start));
    } else if (!(opt->opt & COUNT_OF_LINES_ONLY)) {
        printf("%s", line);
    }
}

void matched_parts_matched_lines(options_t *opt, regex_t *reg, FILE *file,
                                 const char *filename) {
    assert(filename != NULL);
    regmatch_t match[1];
    char *current_line = NULL;
    grep_config_t config = {0, 1, 0, '\n'};

    while (getline(&current_line, &(config.buffer_size), file) != -1) {
        char *tmp = current_line;
        config.current_line++;
        while (regexec(reg, tmp, 1, match, 0) == 0) {
            int n_start = match[0].rm_so;
            int n_finish = match[0].rm_eo;
            output_matched_line(opt, filename, tmp, config, n_start, n_finish);
            tmp += n_finish;
        }
    }

    if (current_line != NULL) {
        free(current_line);
    }
}

enum GREP get_regular_from_another_file(options_t *options, char *filename) {
    assert(filename != NULL);
    FILE *file = NULL;
    char *current_line = NULL;
    grep_config_t config = {0, 1, 0, '\n'};
    int quantity_of_counted = 0;

    enum GREP file_code = open_file(filename, &file);
    if (file_code == GREP_SUCCES) {
        while ((quantity_of_counted = getline(
                    &current_line, &(config.buffer_size), file)) != -1) {
            char *line_end = current_line + quantity_of_counted - 1;
            if (*line_end == '\n') {
                *line_end = '\0';
            }
            add_pattern(options, current_line);
        }
    }

    return file_code;
}