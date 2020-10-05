#include <gtest/gtest.h>

TEST(simple, ok_assert)
{
	ASSERT_EQ(1, 1) << "1 is not equal 1";
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}