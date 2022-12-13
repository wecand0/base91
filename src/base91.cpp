#include "base91.h"

bool Base91::encode(std::string &out, const std::string &binary) {
    const uint8_t *ib = (uint8_t *) binary.c_str();
    uint32_t queue {};
    uint32_t nbits {};

    for (size_t len = binary.size(); len--;) {
        queue |= *ib++ << nbits;
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
            out += basicAlphabet_[val % 91];
            out += basicAlphabet_[val / 91];
        }
    }

    if (nbits) {
        out += basicAlphabet_[queue % 91];
        if (nbits > 7 || queue > 90){
            out += basicAlphabet_[queue / 91];
        }
    }
    return true;
}

bool Base91::decode(std::string &out, const std::string &text) {
    const uint8_t *ib = (uint8_t *) text.c_str();

    uint32_t queue {};
    uint32_t nbits {};
    uint32_t val = -1;

    for (size_t len = text.size(); len--;) {
        uint32_t d = decAlphabet_[*ib++];
        if (d == 91)
            continue; /* ignore non-alphabet chars */
        if (val == -1)
            val = d; /* start next value */
        else {
            val += d * 91;
            queue |= val << nbits;
            nbits += (val & 8191) > 88 ? 13 : 14;
            do {
                out += char(queue);
                queue >>= 8;
                nbits -= 8;
            } while (nbits > 7);
            val = -1; /* mark value complete */
        }
    }

    /* process remaining bits; write at most 1 byte */
    if (val != -1)
        out += char(queue | val << nbits);
    return true;
}
