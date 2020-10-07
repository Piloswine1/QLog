#include <vector>
#include <utility>
#include <string>
#include <regex>
#include <algorithm>
#include <iterator>
#include <iostream>

namespace QLog
{
    enum class ParsedToken { DATA, STRING };

    typedef std::pair<ParsedToken, std::string> StringWithTokens;

    struct Parser
    {
        Parser() = delete;
        /**
         * @return структура с токенами и строками
         * {
         *  t { DATA, STRING, DATA}
         *  s {"", "text", "blalba"} 
         * }
         * мб лучше сразу в строку типо printf
         * т.е. %dtext%sblabla%d, но по мне тупо как то
         */
        static std::vector<StringWithTokens> parse(const std::string& s);
        static std::vector<std::string> parse_to_vec(const std::string& s);
    };
}
