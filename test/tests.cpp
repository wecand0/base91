#include <gtest/gtest.h>
#include <base91.h>

TEST(DataTest, IsDecoded) {
    std::shared_ptr<Base91> base91 = std::make_shared<Base91>();

    std::string data{"Hello world!"};
    auto encoded_91 = base91->encode(data);
    auto decoded_91 = base91->decode(encoded_91);

    ASSERT_EQ("Hello world!", decoded_91);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
