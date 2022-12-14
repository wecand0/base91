#include "base91.h"

#include <iostream>
#include <memory>
#include <string_view>

int main() {
    std::shared_ptr<Base91> base91 = std::make_shared<Base91>();

    std::string data{"Hello world !"};

    std::string encoded_91 = base91->encode(data);
    std::string decoded_91 = base91->decode(encoded_91);

    std::cout << "Encoded : " << encoded_91 << "\r\n"
              << "Decoded : " << decoded_91;
}