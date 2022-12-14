#ifndef BASE91_H
#define BASE91_H

#include <stdint.h>
#include <unistd.h>

void encode(const uint8_t *data, uint32_t data_size, uint8_t *out, uint32_t *out_size);
void decode(const uint8_t *data, uint32_t data_size, uint8_t *out, uint32_t *out_size);

#endif//BASE91_H
