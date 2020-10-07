#include "parser.hpp"

namespace QLog
{
    std::vector<std::string> Parser::parse_to_vec(const std::string &s)
    {
        std::vector<std::string> v;
        const std::regex reg_tokens("#(d|s)");

        const auto beginIt = std::sregex_iterator(s.begin(), s.end(), reg_tokens);
        const auto endIt = std::sregex_iterator();
        std::for_each(beginIt, endIt, [&v](const std::smatch _it){
            std::cout<<"prefix: "<<_it.prefix().str()<<"token: "<<_it.str()<<"\n";
            v.push_back(_it.str());
        });

        return v;
    };
    
}
