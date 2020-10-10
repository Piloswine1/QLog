#include "builder.hpp"

namespace QLog
{
    LoggerBase::LoggerBase()
    {
        /** тут надо буит перегрузить мб под аргументы
         */
    }

    LoggerBase::~LoggerBase()
    {
        /** вроде я смотрел челика, он говорил что нахуй не нузжны деконструкторы
         * типо стандартные обьекты дефолтно уничтожаться
         */
    }

    LogLevel LoggerBase::LogEnumFromString(const std::string &s) const
    {
        const auto it = std::find(LogLevelNames.begin(), LogLevelNames.end(), s);
        if (it == LogLevelNames.end()) throw std::invalid_argument("no such LogLevel");
        const auto pos = std::distance(LogLevelNames.begin(), it);
        return static_cast<LogLevel>(pos);
    }

//    LogBuilder& LogBuilder::set_format(const std::string &s)
//    {
//        const auto p = Parser::parse(s);
//        _p = p;
//        return *this;
//    }

//    const Logger& LogBuilder::build()
//    {
//        if(    _outputs.empty()
//            || _p.strings.empty()
//            || _p.tokens.empty()) throw std::runtime_error("not full class");
//        Logger l = *this;
//        return std::move(l);
//    }

    LogBuilder &LogBuilder::set_format(const std::string &s)
    {
        return *this;
    }

    Logger LogBuilder::build()
    {
        return std::move(*this);
    }

    const std::vector<LoggerBase::LogOutput> &LogBuilder::get_outputs() const noexcept
    {
        return _outputs;
    }

    void LogBuilder::_parse_output(const std::string &s)
    {
        auto f = std::ofstream(s);
        _parse_output(&f, LogLevel::ALL);
    }

    void LogBuilder::_parse_output(std::ostream *s)
    {
        _parse_output(s, LogLevel::ALL);
    }

    void LogBuilder::_parse_output(const std::pair<std::string, std::string> &t)
    {
        const auto& _l = std::get<1>(t);
        const auto& l = LogEnumFromString(_l);
        auto f = std::ofstream(std::get<0>(t));
        _parse_output(&f, l);
    }

    void LogBuilder::_parse_output(const std::pair<std::string, LogLevel> &t)
    {
        const auto& l = std::get<1>(t);
        auto f = std::ofstream(std::get<0>(t));
        _parse_output(&f, l);
    }

    void LogBuilder::_parse_output(const std::pair<std::ostream*, LogLevel> &t)
    {
        const auto& l = t.second;
        auto f = t.first;
        _parse_output(f, l);
    }

    void LogBuilder::_parse_output(std::ostream* s, const LogLevel &l)
    {
        _outputs.emplace_back(std::make_shared<std::ostream*>(s), l);
    }

    template<typename ...T>
    LogBuilder& LogBuilder::add_output(const T &...args)
    {
//        [](){}(_parse_output(args)...); //LOL вроде даже работает
        for(const auto &v: {args...}) {
            _parse_output(v);
        }
        return *this;
    }

    template<typename ...T>
    void Logger::invoke(const T &...args) const
    {
        _invoke_impl(args...);
    }

}
