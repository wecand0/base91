#include <stdio.h>
#include <string.h>
#include <malloc.h>

#include <base91.h>

int main() {
   const char *data = "hello world";

   //Encoded string size ~= (16 * original size) / 13.
    uint64_t encodedSize = 1 + strlen(data) * 16 / 13;
    uint8_t *encoded = (uint8_t *) calloc(encodedSize , 1);
    uint8_t *decoded = (uint8_t *) calloc(strlen(data), 1);
    size_t out_size = 0;
    base91_encode((uint8_t *)data, strlen(data), encoded, &out_size);

    printf("Encoded text: %s" "   \t,size: ""%zu\n", encoded, out_size);

    base91_decode(encoded, out_size, decoded, &out_size);

    printf("Decoded text: %s" "   \t,size: ""%zu\n", decoded, out_size);

    free(encoded);
    free(decoded);
}