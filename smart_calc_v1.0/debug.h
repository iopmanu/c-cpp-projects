#ifndef DEBUG_H_
#define DEBUG_H_

#define NDEBUG

#include "stack.h"
#include <assert.h>

/**
 * @brief This macro is for condition checking and return code of the error.
 * 
 */
#define CHECK(condition, code) \
    do {                       \
        if (condition) {       \
            return code;       \
        }                      \
    } while (0)

/**
 * @brief This function is for nullptr checking and return code of the error/poison ptr.
 * 
 */
#define CHECK_BAD_PTR(ptr, code) \
    do {                         \
        assert(ptr != NULL);     \
        if (ptr == NULL) {       \
            return code;         \
        }                        \
    } while (0)

#endif  // DEBUG_H_
