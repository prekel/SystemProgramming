//
// Created by vladislav on 19.10.2019.
//

#include <assert.h>
#include <stdio.h>
#include <malloc.h>

#include "rar.h"
#include "compressor_interface.h"

typedef struct
{
    int compressed_ratio;
    int error;
    int time_to_finish;
} rar_impl_t;

////////////////////////////////////////////////////////////////////////////////

// Удобный макрос для повторяющегося кода
#define PREPARE_IMPL(c) \
  assert(c); \
  assert(c->impl_); \
  rar_impl_t* impl = (rar_impl_t*)c->impl_;

////////////////////////////////////////////////////////////////////////////////

static void compress(compressor_t* c, void* data)
{
    PREPARE_IMPL(c)
    printf("RAR: compressor working. Compressed ratio: %d\n",
           impl->compressed_ratio);
}

////////////////////////////////////////////////////////////////////////////////

static void uncompress(compressor_t* c, void* data)
{
    PREPARE_IMPL(c)
    printf("RAR: uncompressor working. Will be finished in %d.\n",
           impl->time_to_finish);
}

////////////////////////////////////////////////////////////////////////////////

static void status(compressor_t* c)
{
    PREPARE_IMPL(c)
    printf("Compressed ratio: %d, error: %d\n", impl->compressed_ratio,
           impl->error);
}

////////////////////////////////////////////////////////////////////////////////

// Конструктор
void rar_init(compressor_t* c, int cr)
{
    assert(c);
    c->impl_ = malloc(sizeof(rar_impl_t));
    rar_impl_t* impl = (rar_impl_t*)c->impl_;

    // Инициализируем `private` члены
    impl->time_to_finish = 5;
    impl->compressed_ratio = cr;
    impl->error = 0;

    // И `public` функции
    c->compress = &compress;
    c->uncompress = &uncompress;
    c->status = &status;
}

////////////////////////////////////////////////////////////////////////////////


//Деструктор
void rar_free(compressor_t* c)
{
    PREPARE_IMPL(c)
    free(impl);
}