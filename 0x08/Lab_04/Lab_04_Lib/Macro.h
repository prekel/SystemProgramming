#ifndef MACRO_H
#define MACRO_H

#define SUCCESSFUL 0

#define FILE_UNSUCCESSFUL (-1)

#define BAD_VALUE (-2)

#define NOT_FOUND (-3)

#define BAD_ARGS (-4)

#define FILE_NOT_EXIST (-5)

#define CLOSE_UNSUCCESSFUL (-6)

#define BAD_META (-7)

#define RETURN_IF_NOT_SUCCESSFUL(f) do { \
    int tmp = (f); \
    if (tmp < SUCCESSFUL) \
    { \
        return tmp; \
    } \
} while (0)

#endif //MACRO_H
