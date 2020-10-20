#include "builder.hpp"

namespace QLog {
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

LogBuilder &LogBuilder::use_cout()
{
    _useCout = true;
    return *this;

}

//    LogBuilder &LogBuilder::add_output(const std::string &s)
//    {
//        return *this;
//    }

Logger LogBuilder::build()
{
//  for(auto &e: _outputs)
//  {
//      *(e.first)<<"test"<<'\n';
//  }
  return *this;
}

const std::vector<LoggerBase::LogOutput> &LogBuilder::get_outputs() const noexcept
{
  return _outputs;
}

void LogBuilder::_parse_output(const std::string &s)
{
  _parse_output(s, LogLevel::ALL);
}

void LogBuilder::_parse_output(const std::pair<std::string, std::string> &t)
{
  const auto &[f, _l] = t;
  const auto &l = LogEnumFromString(_l);
  _parse_output(f, l);
}

void LogBuilder::_parse_output(const std::pair<std::string, LogLevel> &t)
{
  const auto &[f, l] = t;
  _parse_output(f, l);
}

void LogBuilder::_parse_output(const std::string &file, const LogLevel &level)
{
    _outputs.emplace_back(file, level);
}

void Logger::_invoke_impl(const std::string &s)
{
    for(auto &e: _outputs){

    }
}

}// namespace QLog
