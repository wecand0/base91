package base91

func decode(src []byte) []byte {
	// b and n must be at least uint32
	var b, n uint32 = 0, 0
	v := -1
	decoded := []byte{}

	for i := 0; i < len(src); i++ {
		p := decTab[src[i]]
		if p > 90 {
			// skip invalid character silently
			continue
		}
		if v < 0 {
			v = int(p)
			continue
		}
		v += int(p) * 91
		b |= uint32(v) << n
		if v&0x1fff > 88 {
			n += 13
		} else {
			n += 14
		}
		for {
			decoded = append(decoded, uint8(b))
			b >>= 8
			n -= 8
			if n <= 7 {
				break
			}
		}
		v = -1
	}

	if v > -1 {
		decoded = append(decoded, uint8(b|uint32(v)<<n))
	}

	return decoded
}

// DecodeString returns the bytes represented by the base91 string s, probably
// what you want.
func DecodeString(s string) []byte {
	return decode([]byte(s))
}
