#include <gtest/gtest.h>
#include <base91.h>

TEST(DataTest, IsDecoded) {
    std::shared_ptr<Base91> base91 = std::make_shared<Base91>();

    std::string data{"Man is distinguished, not only by his reason, but by this singular passion from other animals, which is a lust of the mind, that by a perseverance of delight in the continued and indefatigable generation of knowledge, exceeds the short vehemence of any carnal pleasure."};
    auto encoded_91 = base91->encode(data);
    auto decoded_91 = base91->decode(encoded_91);

    ASSERT_EQ("Man is distinguished, not only by his reason, but by this singular passion from other animals, which is a lust of the mind, that by a perseverance of delight in the continued and indefatigable generation of knowledge, exceeds the short vehemence of any carnal pleasure.", decoded_91);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
