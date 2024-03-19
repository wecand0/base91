#ifndef BASE91_C_BASE91_H
#define BASE91_C_BASE91_H

#include <stdint.h>
#include <string.h>

void base91_encode(const uint8_t *in_data, size_t in_data_size, uint8_t *out_data, size_t *out_data_size);
void base91_decode(const uint8_t *in_data, size_t in_data_size, uint8_t *out_data, size_t *out_data_size);

#endif//BASE91_C_BASE91_H
