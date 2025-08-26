#include "base91.h"
#include <iostream>

int main() {
    try {
        Base91 base91;
        base91.encode("hello world");

        const auto eString = base91.getData();
        std::cout << eString << std::endl;

        base91.decode(eString);

        std::cout << base91.getData();

    } catch (const std::exception &e) {
        std::cout << e.what();
    }

    return 0;
}