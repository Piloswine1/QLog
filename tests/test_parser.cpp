#include <gtest/gtest.h>
#include <algorithm>
#include "parser.hpp"

TEST(PARSER, DISABLED_simple_parse_token)
{
    typedef QLog::ParsedToken pt;
    auto s1("#d some #s text #d");
    auto s2("#dsome#stext#d");
    auto s3("some#dsome#stext#dtext");

    auto v1 = QLog::Parser::parse_to_vec(s1);
    auto v2 = QLog::Parser::parse_to_vec(s2);
    auto v3 = QLog::Parser::parse_to_vec(s3);

    auto vec = {pt::DATA, pt::STRING, pt::DATA};

    ASSERT_TRUE(std::equal(vec.begin(), vec.end(), v1.begin())) << "vectors (v1 and vec) not equal";
    ASSERT_TRUE(std::equal(vec.begin(), vec.end(), v2.begin())) << "vectors (v2 and vec) not equal";
    ASSERT_TRUE(std::equal(vec.begin(), vec.end(), v3.begin())) << "vectors (v3 and vec) not equal";
}

//HELPER Functions______________________________
template<typename T>
void print_vec(const std::vector<T> &vec)
{
    for (const auto &i: vec){
        std::cout<<i;
    }
}

void print_vec(const std::vector<QLog::ParsedToken> &vec)
{
    typedef QLog::ParsedToken pt;
    for (const auto &i: vec){
        const auto val = (i==pt::DATA)? "DATA" :
                                        "STRING";
        std::cout<<val;
    }
}

bool operator==(const QLog::Parsed &a, const QLog::Parsed b) noexcept
{
    std::cout<<"TOKENS:"<<'\n';
    print_vec(a.tokens);
    std::cout<<'\n';
    print_vec(b.tokens);
    std::cout<<'\n';
    std::cout<<"STRINGS:"<<'\n';
    print_vec(a.strings);
    std::cout<<'\n';
    print_vec(b.strings);
    std::cout<<'\n';
    const auto t = std::equal(a.tokens.begin(), a.tokens.end(), b.tokens.begin());
    const auto s = std::equal(a.strings.begin(), a.strings.end(), b.strings.begin());
    return t && s;
}
//______________________________________________

TEST(PARSER, simple_test_with_structs)
{
    typedef QLog::ParsedToken pt;

    auto s1("#d some #s text #d");
    auto v1 = QLog::Parser::parse(s1);
    QLog::Parsed p1 = {
        .tokens = {pt::DATA, pt::STRING, pt::DATA},
        .strings = {"", " some ", " text ", ""}
    };
    ASSERT_TRUE(v1 == p1) << "structs not equal";

    auto s2("#dsome#stext#d");
    auto v2 = QLog::Parser::parse(s2);
    QLog::Parsed p2 = {
        .tokens = {pt::DATA, pt::STRING, pt::DATA},
        .strings = {"", "some", "text", ""}
    };
    ASSERT_TRUE(v2 == p2) << "structs not equal";

    auto s3("some#dsome#stext#dtext");
    auto v3 = QLog::Parser::parse(s3);
    QLog::Parsed p3 = {
        .tokens = {pt::DATA, pt::STRING, pt::DATA},
        .strings = {"some", "some", "text", "text"}
    };
    ASSERT_TRUE(v3 == p3) << "structs not equal";

}

TEST(PARSER, empty_string_or_fully_escaped)
{
    auto s1("");
    auto v1 = QLog::Parser::parse(s1);
    QLog::Parsed p1 = {
        .tokens = {},
        .strings = {""}
    };
    ASSERT_TRUE(v1 == p1) << "failed in empty string";

    auto s2("##dsome##stext##d");
    auto v2 = QLog::Parser::parse(s2);
    QLog::Parsed p2 = {
        .tokens = {},
        .strings = {"##dsome##stext##d"}
    };
    ASSERT_TRUE(v2 == p2) << "failed in full escape";
}

TEST(PARSER, escape_sequence)
{
    typedef QLog::ParsedToken pt;

    auto s1("##dsome#stext#d");
    auto v1 = QLog::Parser::parse(s1);
    QLog::Parsed p1 = {
        .tokens = {pt::STRING, pt::DATA},
        .strings = {"##dsome", "text", ""}
    };
    ASSERT_TRUE(v1 == p1) << "failed in escape";

    auto s2("#dsome#stext ##d");
    auto v2 = QLog::Parser::parse(s2);
    QLog::Parsed p2 = {
        .tokens = {pt::DATA, pt::STRING},
        .strings = {"", "some", "text ##d"}
    };
    ASSERT_TRUE(v2 == p2) << "failed in escape";

    auto s3("#dsome ##stext ##d");
    auto v3 = QLog::Parser::parse(s3);
    QLog::Parsed p3 = {
        .tokens = {pt::DATA},
        .strings = {"", "some ##stext ##d"}
    };
    ASSERT_TRUE(v3 == p3) << "failed in escape";

}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
