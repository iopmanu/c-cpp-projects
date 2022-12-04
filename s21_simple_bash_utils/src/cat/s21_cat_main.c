// Copyright 2022 mablever

#include <stdio.h>

#include "./s21_cat_lib.h"

int main(int argc, char *argv[]) {
    enum CAT code = CAT_SUCCES;
    int options = 0;
    int nonoptions_part = 0;

    code = cat_get_param(argc, argv, &nonoptions_part, &options);
    checking_conflict(&options);

    if (code == CAT_SUCCES) {
        while ((nonoptions_part++ < argc) && (code == CAT_SUCCES)) {
            FILE *file = NULL;
            char *filename = argv[nonoptions_part - 1];

            code = open_file(filename, &file);

            if (code == CAT_SUCCES) {
                cat_file(file, stdout, options);
            }
        }
    }

    if (code != CAT_SUCCES) {
        catperror(code);
    }

    return code;
}
