//
// Created by vladislav on 19.10.2019.
//

#ifndef ZIP_H
#define ZIP_H

#include "compressor_interface.h"

void zip_init(compressor_t* c, int cr);
void zip_free(compressor_t* c);

#endif //RAR_H
