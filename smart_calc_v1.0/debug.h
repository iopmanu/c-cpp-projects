#ifndef DEBUG_H_
#define DEBUG_H_

#include "stack.h"
#include <assert.h>

#define CHECK(condition, code) \
    do {                       \
        if (condition) {       \
            return code;       \
        }                      \
    } while (0)

#define CHECK_BAD_PTR(ptr, code) \
    do {                         \
        assert(ptr != NULL);     \
        if (ptr == NULL) {       \
            return code;         \
        }                        \
    } while (0)

#endif  // DEBUG_H_
