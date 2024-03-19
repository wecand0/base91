package main

func main() {
	encoded := EncodeToString([]byte("hello world"))
	println(encoded)

	decoded := DecodeString(encoded)
	println(string(decoded))
}
