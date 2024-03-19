BasE91 with (safe) r'lyeh modification of standard alphabet. This implementation is friendly for json/xml.
I use calculating of encoding text size  and reserve it in capacity of input string.

___

# Pros and cons of using Base91
Joachim Henke created the base91 binary-to-text encoding technique, often known as basE91. The binary data stream is split into 13-bit packets, which are subsequently encoded as two ASCII characters[2]. In general, the size of the encoded data will be 316 times bigger than the original, assuming eight bits per ASCII character. This is more effective than base85's 14 increase and base64's 13 increase (which utilizes four characters to represent three bytes of data) (which uses five characters to represent four bytes of data).

## Advantages

1. Compared to base85, conversion is quick. Due to the packet's tiny size, a lookup table can be used instead of division or multiplication during encoding and decoding. Base85 would need a 232 lookup table of 5 bytes, which would need at least 5 GiB of RAM if implemented.
2. The overhead is only 23% compared to base64, which drops to 14% for 0-byte blocks.
3. Because backslash and single quotes are not utilized, many programming languages make it simple to quote.

## Disadvantages

1. Slower encoding and decoding than base64
2. Binary Coded Decimal is a type of binary encoding that uses 4 binary numbers to represent the 10 digits from 0 to 9 in a decimal number.

___
**Solved problem of challenging to utilize in double-quoted strings without escape characters or raw string because of the use $ and " in the digit alphabet.**
