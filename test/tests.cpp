//
// Created by user on 14.12.22.
//

#include "base91.h"

#include <gtest/gtest.h>

TEST(DataTest, IsDecoded) {
    std::shared_ptr<Base91> base91 = std::make_shared<Base91>();

    std::string data{"Hello world!"};

    std::string encoded_91 = base91->encode(data);
    std::string decoded_91 = base91->decode(encoded_91);

    ASSERT_EQ("Hello world!", base91->decode(encoded_91));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
