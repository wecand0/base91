package base91

func encode(src []byte) []byte {
	var b, n uint32 = 0, 0
	encoded := []byte{}

	for i := 0; i < len(src); i++ {
		b |= uint32(src[i]) << n
		n += 8

		if n <= 13 {
			continue
		}

		v := b & 0x1fff
		if v > 88 {
			b >>= 13
			n -= 13
		} else {
			v = b & 0x3fff
			b >>= 14
			n -= 14
		}

		encoded = append(encoded, encTab[v%91], encTab[v/91])
	}

	if n != 0 {
		encoded = append(encoded, encTab[b%91])
		if n > 7 || b > 90 {
			encoded = append(encoded, encTab[b/91])
		}
	}

	return encoded
}

// Encode encodes src into dst. It returns the number of bytes written to dst.
func Encode(dst, src []byte) int {
	return copy(dst, encode(src))
}

// EncodeToString returns the encoded base91 string of src, probably what you
// want.
func EncodeToString(src []byte) string {
	return string(encode(src))
}
