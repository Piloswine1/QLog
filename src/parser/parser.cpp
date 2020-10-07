#include "parser.hpp"

namespace QLog
{

std::vector<StringWithTokens> Parser::parse(const std::string &s)
{
    std::vector<StringWithTokens> v;
    const std::regex reg_tokens("#(d|s)");

    auto parse_token = [](const std::string &_s){
        switch (_s[1]) {
        case 'd': return std::pair(ParsedToken::DATA, _s);
        case 's': return std::pair(ParsedToken::STRING, _s);
        default: throw std::invalid_argument("not of 'd' or 's'");
        }
    };

    const auto beginIt = std::sregex_iterator(s.begin(), s.end(), reg_tokens);
    const auto endIt = std::sregex_iterator();
    std::for_each(beginIt, endIt, [&v, &parse_token](const std::smatch _it){
        std::cout<<"prefix: "<<_it.prefix().str()<<"token: "<<_it.str()<<"\n";
        v.push_back(parse_token(_it.str()));
    });

    return v;
}

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
