#include <gtest/gtest.h>
#include <builder.hpp>

TEST(builder, builder_outpust)
{
    typedef QLog::LogLevel LL;
    auto builder = QLog::LogBuilder();
    auto logger = builder.set_format("#d some #s text #d")
            .add_output(
                "test.log",
                std::pair("test2.log", LL::WARN)
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
