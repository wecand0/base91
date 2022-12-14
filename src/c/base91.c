#include <malloc.h>
#include "base91.h"

const uint8_t b91word_bit_c = 13;
const char basicAlphabet_c[91] = {
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
        'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
        'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
        'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '!', '#', '$',
        '%', '&', '(', ')', '*', '+', ',', '.', '/', ':', ';', '<', '=',
        '>', '?', '@', '[', ']', '^', '_', '`', '{', '|', '}', '~', '"'};

const uint8_t decAlphabet_c[256] = {
        91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91,
        91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91,
        91, 62, 90, 63, 64, 65, 66, 91, 67, 68, 69, 70, 71, 91, 72, 73,
        52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 74, 75, 76, 77, 78, 79,
        80, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
        15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 81, 91, 82, 83, 84,
        85, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
        41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 86, 87, 88, 89, 91,
        91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91,
        91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91,
        91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91,
        91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91,
        91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91,
        91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91,
        91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91,
        91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91};


void encode(const uint8_t *data, const uint32_t data_size, uint8_t *out, uint32_t *out_size) {
    if (data == NULL) {
        return;
    }

/*    uint32_t out_size_temp = data_size;
    out_size_temp <<= 4;
    if (out_size_temp % b91word_bit_c != 0)
    {
        out_size_temp /= b91word_bit_c;
        out_size_temp += 1;
    }
    else
    {
        out_size_temp /= b91word_bit_c;
    }*/

    const uint8_t *ib = (uint8_t *) data;
    uint32_t queue = 0;
    uint32_t nbits = 0;

    uint32_t counter = 0;
    for (uint32_t len = 0; len < data_size; len++) {
        queue |= *ib++ << nbits;
        nbits += 8;
        if (nbits > b91word_bit_c) { /* enough bits in queue */
            uint32_t val = queue & 8191;
            if (val > 88) {
                queue >>= b91word_bit_c;
                nbits -= b91word_bit_c;
            } else { /* we can take 14 bits */
                val = queue & 16383;
                queue >>= 14;
                nbits -= 14;
            }
            out[counter] = basicAlphabet_c[val % 91];
            counter++;
            out[counter]= basicAlphabet_c[val / 91];
            counter++;
        }
    }
    if (nbits) {
        out[counter] = basicAlphabet_c[queue % 91];
        counter++;
        if (nbits > 7 || queue > 90) {
            out[counter] = basicAlphabet_c[queue / 91];
            counter++;
        }
    }
    *out_size = counter;
}

void decode(const uint8_t *data, uint32_t data_size, uint8_t *out, uint32_t *out_size){
    if (data == NULL) {
        return;
    }

/*    uint32_t out_size_temp = data_size;
    out_size_temp *= b91word_bit_c;
    out_size_temp >>= 4;*/


    const uint8_t *ib = (uint8_t *) data;
    uint32_t queue = 0;
    uint32_t nbits = 0;
    uint32_t val = -1;

    uint32_t counter = 0;
    for (uint32_t len = 0; len < data_size; len++) {
        uint32_t d = decAlphabet_c[*ib++];
        if (d == 91)
            continue;


        if (val == -1)
            val = d;
        else {
            val += d * 91;
            queue |= val << nbits;
            nbits += (val & 8191) > 88 ? b91word_bit_c : 14;
            do {
                out[counter] = (queue);
                counter++;
                queue >>= 8;
                nbits -= 8;
            } while (nbits > 7);
            val = -1;
        }
    }
    if (val != -1) {
        out[counter] =  queue | val << nbits;
        counter++;
    }
    *out_size = counter;
}

