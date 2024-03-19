#include <catch2/catch_test_macros.hpp>
#include <iostream>

#include "base91.h"

TEST_CASE("CorrectDataEncoding", "[Base91Tests]"){
    Base91 base91;
    base91.encode("hello world");
    CHECK(base91.getData() == "TPwJh\\Io2Tv!lE");
}

TEST_CASE("CorrectDataDecoding", "[Base91Tests]"){
    Base91 base91;
    base91.decode("TPwJh\\Io2Tv!lE");
    CHECK(base91.getData() == "hello world");
}

TEST_CASE("EncodeThanDecodeData", "[Base91Tests]"){
    Base91 base91;
    base91.encode("hello world");
    auto eString = base91.getData();
    base91.decode(eString);
    auto dString = base91.getData();
    CHECK(dString == "hello world");
}

TEST_CASE("EmptyDataEncoding", "[Base91Tests]"){
    Base91 base91;
    REQUIRE_THROWS_AS(base91.encode({}), std::invalid_argument);
}

TEST_CASE("EmptyDataDecoding", "[Base91Tests]"){
    Base91 base91;
    REQUIRE_THROWS_AS(base91.decode({}), std::invalid_argument);
}