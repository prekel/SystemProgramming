//
// Created by vladislav on 19.10.2019.
//

#ifndef LOGGING_COMPRESSOR_H
#define LOGGING_COMPRESSOR_H

#include "compressor_interface.h"

typedef struct logging_compressor_t
{
    struct compressor_t base;

    void (* log)(struct logging_compressor_t* lc);

    void* impl_;
} logging_compressor_t;

#endif //LOGGING_COMPRESSOR_H
