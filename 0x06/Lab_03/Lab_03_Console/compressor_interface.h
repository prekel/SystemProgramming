//
// Created by vladislav on 19.10.2019.
//

#ifndef COMPRESSOR_INTERFACE_H
#define COMPRESSOR_INTERFACE_H

typedef struct compressor_t
{
    // `public` interface
    void (* compress)(struct compressor_t*, void* data);

    void (* uncompress)(struct compressor_t*, void* data);

    void (* status)(struct compressor_t*);

    // `private` part
    void* impl_;
} compressor_t;


#endif //COMPRESSOR_INTERFACE_H
