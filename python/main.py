import base91

if __name__ == '__main__':
    src = "Man is distinguished, not only by his reason, but by this singular passion from other animals, which is a " \
          "lust of the mind, that by a perseverance of delight in the continued and indefatigable generation of " \
          "knowledge, exceeds the short vehemence of any carnal pleasure."
    e = base91.encode(src)
    print(e)

    d = base91.decode(e)
    print(d)