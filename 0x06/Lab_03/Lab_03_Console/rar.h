//
// Created by vladislav on 19.10.2019.
//

#ifndef RAR_H
#define RAR_H

#include "compressor_interface.h"

void rar_init(compressor_t* c, int cr);
void rar_free(compressor_t* c);

#endif //RAR_H
