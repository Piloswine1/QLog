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

    struct Parsed
    {
       std::vector<ParsedToken> tokens;
       std::vector<std::string> strings;
    };

    struct Parser
    {
        Parser() = delete;
        /**
         * @deprecated
         */
        static std::vector<ParsedToken> parse_to_vec(const std::string& s);
        /**
         * @return структура с токенами и строками
         * {
         *  t { DATA, STRING, DATA}
         *  s {"", "text", "blalba"}
         * }
         * мб лучше сразу в строку типо printf
         * т.е. %dtext%sblabla%d, но по мне тупо как то
         */
        static Parsed parse(const std::string& s);
    private:
        static ParsedToken _assign_type(const std::string &_s);
    };
}
