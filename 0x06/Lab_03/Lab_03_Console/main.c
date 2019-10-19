#include <stdio.h>
#include "compressor_interface.h"
#include "rar.h"
#include "zip.h"
#include "logging_compressor.h"

#define DATA_SIZE 10
#define COMP_RATIO 4
#define VOLUMES 3

void work(compressor_t* c, void* data_to_compress, void* data_to_decompress)
{
    c->compress(c, data_to_compress);
    c->uncompress(c, data_to_decompress);
    c->status(c);
}

int main()
{
    void* uncompressed_data[DATA_SIZE];
    void* compressed_data[DATA_SIZE];

    compressor_t rar;
    rar_init(&rar, COMP_RATIO);
    work(&rar, uncompressed_data, compressed_data);
    rar_free(&rar);

    printf("\n");

    compressor_t zip;
    zip_init(&zip, VOLUMES);
    work(&zip, uncompressed_data, compressed_data);
    zip_free(&zip);

    logging_compressor_t lc;
    lc.base.compress(lc);

    return 0;
}