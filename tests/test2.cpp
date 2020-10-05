#include <gtest/gtest.h>
#include <test2.h>

TEST(simple, with_header)
{
	ASSERT_EQ(MAGIC, 20) << "header is not compiled";
}

TEST(simple, failing_assert)
{
    ASSERT_NE(1, 0) << "1 is not equal 0";
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}