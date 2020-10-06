#include <vector>
#include <utility>
#include <string>
#include <regex>
#include <algorithm>
#include <iterator>

namespace Qlog
{
    enum class ParsedToken { DATA, STRING };

    struct StringArrayWithTokens
    {
        std::vector<ParsedToken> t;
        std::vector<std::string>  s;
    };

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
        static StringArrayWithTokens parse(const std::string& s);
    };
}