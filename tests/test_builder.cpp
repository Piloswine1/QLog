#include <gtest/gtest.h>
#include <builder.hpp>

TEST(builder, builder_outpust)
{
    typedef QLog::LogLevel LL;
    QLog::LogBuilder b;
    auto logger = b.set_format("#d some #s text #d")
            .add_output(
                std::string("test.log"),
                std::pair(std::string("test2.log"), LL::DEBUG)
            )
            .build();
//    logger.invoke();
    ASSERT_TRUE(false);
}

TEST(builder, DISABLED_failing_assert)
{
    ASSERT_NE(1, 0) << "1 is not equal 0";
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
