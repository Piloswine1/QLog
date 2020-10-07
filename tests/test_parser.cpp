#include <gtest/gtest.h>
#include <algorithm>
#include "parser.hpp"

TEST(PARSER, simple_parse_token)
{
    auto s1("#d some #s text #d");
    auto s2("#dsome#stext#d");
    auto s3("some#dsome#stext#dtext");

    auto v1 = QLog::Parser::parse_to_vec(s1);
    auto v2 = QLog::Parser::parse_to_vec(s2);
    auto v3 = QLog::Parser::parse_to_vec(s3);

    auto vec = {"#d", "#s", "#d"};

    ASSERT_TRUE(std::equal(vec.begin(), vec.end(), v1.begin())) << "vectors (v1 and vec) not equal";
    ASSERT_TRUE(std::equal(vec.begin(), vec.end(), v2.begin())) << "vectors (v2 and vec) not equal";
    ASSERT_TRUE(std::equal(vec.begin(), vec.end(), v3.begin())) << "vectors (v3 and vec) not equal";
}

TEST(PARSER, parser_to_pair)
{
    auto s1("#d some #s text #d");
    auto s2("#dsome#stext#d");
    auto s3("some#dsome#stext#dtext");

    auto v1 = QLog::Parser::parse(s1);
    auto v2 = QLog::Parser::parse(s2);
    auto v3 = QLog::Parser::parse(s3);

    auto vec = {
        std::make_pair(QLog::ParsedToken::DATA,    std::string("#d")),
        std::make_pair(QLog::ParsedToken::STRING,  std::string("#s")),
        std::make_pair(QLog::ParsedToken::DATA,    std::string("#d")),
    };

    ASSERT_TRUE(std::equal(vec.begin(), vec.end(), v1.begin())) << "vectors (v1 and vec) not equal";
    ASSERT_TRUE(std::equal(vec.begin(), vec.end(), v2.begin())) << "vectors (v2 and vec) not equal";
    ASSERT_TRUE(std::equal(vec.begin(), vec.end(), v3.begin())) << "vectors (v3 and vec) not equal";
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
