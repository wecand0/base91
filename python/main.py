import base91

if __name__ == '__main__':
    encoded = base91.encode("Hello world")
    decoded = base91.decode(encoded)
    print("Encoded", encoded)
    print("Decoded", decoded)
