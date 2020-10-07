#include "parser.hpp"

namespace QLog
{

    StringArrayWithTokens Parser::parse(const std::string& s)
    {
        std::vector<ParsedToken> _t;
        std::vector<std::string> _s;
        std::string no_tokens;
        // парсим дата или строка должна идти здесь
        auto parse_token = [&_t, &_s](const char &ch){
            switch(ch) {
                case 'd': return _t.push_back(ParsedToken::DATA);
                case 's': return _t.push_back(ParsedToken::STRING);
                default: throw std::invalid_argument("recieved wrong char");
            }
        };
        // выйдет ли за границу массива?, по идее нет
        for(auto it = s.begin(); it < s.end();) {
            // собираем строки в вектор,
            // чтобы потом между ними вставлять кастомные токены
            no_tokens.push_back(*it);
            if (*it == '#') {
                // вот здесь бы бля паттерн матчинг помог ебать
                if(it == s.begin()) {
                    parse_token(*std::next(it));
                    _s.push_back(std::string()); // подумал, что б обозначить начало используем пустую строку
                    ++it;
                } else if (*std::prev(it)) {
                    parse_token(*std::next(it));
                    _s.push_back(no_tokens);
                    no_tokens.clear(); // собираем новую стороку
                    ++it;
                }
            }
            ++it;
        }
        
        return StringArrayWithTokens {.t = _t, .s = _s};
    };
    
}
