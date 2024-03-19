#include "base91.h"
#include <string.h>

const char basicAlphabet_[91] = {
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', //00..12
        'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', //13..25
        'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', //26..38
        'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', //39..51
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '!', '#', '$', //52..64
        '%', '&', '(', ')', '*', '+', ',', '.', '/', ':', ';', '-', '=', //65..77
        '\\', '?', '@', '[', ']', '^', '_', '`', '{', '|', '}', '~', '\''//78..90
};

const uint8_t decAlphabet_[256] = {
        91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91,//000..015
        91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91,//016..031
        91, 62, 91, 63, 64, 65, 66, 90, 67, 68, 69, 70, 71, 76, 72, 73,//032..047 // @34: ", @39: ', @45: -
        52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 74, 75, 91, 77, 91, 79,//048..063 // @60: <, @62: >
        80, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,          //064..079
        15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 81, 78, 82, 83, 84,//080..095 // @92: slash
        85, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,//096..111
        41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 86, 87, 88, 89, 91,//112..127
        91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91,//128..143
        91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91,//144..159
        91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91,//160..175
        91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91,//176..191
        91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91,//192..207
        91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91,//208..223
        91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91,//224..239
        91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91 //240..255
};

void base91_encode(const uint8_t *in_data, size_t in_data_size, uint8_t *out_data, size_t *out_data_size) {
    uint32_t queue = 0;
    uint32_t nbits = 0;
    size_t position = 0;

    while (in_data_size--) {
        queue |= *in_data++ << nbits;
        nbits += 8;
        if (nbits > 13) { /* enough bits in queue */
            uint32_t val = queue & 8191;
            if (val > 88) {
                queue >>= 13;
                nbits -= 13;
            } else { /* we can take 14 bits */
                val = queue & 16383;
                queue >>= 14;
                nbits -= 14;
            }
            out_data[position++] = basicAlphabet_[val % 91];
            out_data[position++] = basicAlphabet_[val / 91];
        }
    }

    if (nbits) {
        out_data[position++] = basicAlphabet_[queue % 91];
        if (nbits > 7 || queue > 90) {
            out_data[position++] = basicAlphabet_[queue / 91];
        }
    }
    *out_data_size = position;
}

void base91_decode(const uint8_t *in_data, size_t in_data_size, uint8_t *out_data, size_t *out_data_size) {
    uint32_t queue = 0;
    uint32_t nbits = 0;
    uint32_t val = -1;
    size_t position = 0;

    while (in_data_size--) {
        uint32_t d = decAlphabet_[*in_data++];
        if (d == 91)
            continue; /* ignore non-alphabet chars */
        if (val == -1)
            val = d; /* start next value */
        else {
            val += d * 91;
            queue |= val << nbits;
            nbits += (val & 8191) > 88 ? 13 : 14;
            do {
                out_data[position++] = (uint8_t) queue;
                queue >>= 8;
                nbits -= 8;
            } while (nbits > 7);
            val = -1; /* mark value complete */
        }
    }
    /* process remaining bits; write at most 1 byte */
    if (val != -1) {
        out_data[position++] = (uint8_t) (queue | val << nbits);
    }
    *out_data_size = position;
}