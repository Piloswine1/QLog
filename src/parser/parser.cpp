#include "parser.hpp"

namespace QLog
{

Parsed Parser::parse(const std::string &s)
{
    std::vector<ParsedToken> tokens;
    std::vector<std::string> strings;
    int _pos = 0;

    const std::regex reg_tokens("#(d|s)");

    auto parse_token = [&](const std::smatch &_it){
        // проверяем нужно ли вообще обрабатывать этот токен
        const auto isSkippable = _it.prefix().str().back() == '#';
        if (isSkippable) return;
        // разбиваем строку на подстроки без токенов
        strings.push_back(s.substr(_pos, _it.position() - _pos));
        _pos = _it.position() + _it.length();
        tokens.push_back(_assign_type(_it.str()));
    };

    const auto beginIt = std::sregex_iterator(s.begin(), s.end(), reg_tokens);
    const auto endIt = std::sregex_iterator();
    std::for_each(beginIt, endIt, parse_token);

    // оставшаяся подстрока
    strings.push_back(s.substr(_pos));
    return Parsed { tokens, strings };
}

std::vector<ParsedToken> Parser::parse_to_vec(const std::string &s)
{
    std::vector<ParsedToken> v;
    const std::regex reg_tokens("#(d|s)");

    const auto beginIt = std::sregex_iterator(s.begin(), s.end(), reg_tokens);
    const auto endIt = std::sregex_iterator();
    std::for_each(beginIt, endIt, [&v](const std::smatch _it){
        std::cout<<"prefix: "<<_it.prefix().str()<<"token: "<<_it.str()<<"\n";
        v.push_back(_assign_type(_it.str()));
    });

    return v;
}

ParsedToken Parser::_assign_type(const std::string &_s)
{
    switch (_s[1]) {
        case 'd': return ParsedToken::DATA;
        case 's': return ParsedToken::STRING;
        default: throw std::invalid_argument("not of 'd' or 's'");
    }
};
    
}
