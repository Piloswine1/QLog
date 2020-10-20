#include <fstream>
#include <iostream>
#include <variant>
#include <algorithm>
#include <vector>
#include <memory>

namespace QLog {
enum class LogLevel { OFF,
                      FATAL,
                      ERROR,
                      WARN,
                      DEBUG,
                      INFO,
                      ALL };

struct LoggerBase
{
  typedef std::pair<std::string, LogLevel> LogOutput;
  LoggerBase();
  LoggerBase(const LoggerBase &l):
      _outputs(std::move(l._outputs))
  {};
  virtual ~LoggerBase();

protected:
  const std::array<std::string, 7> LogLevelNames = { "OFF",
                                                     "FATAL",
                                                     "ERROR",
                                                     "WARN",
                                                     "DEBUG",
                                                     "INFO",
                                                     "ALL" };
  LogLevel LogEnumFromString(const std::string &s) const;
  void _close_outputs();
  std::vector<LogOutput> _outputs;
  bool _useCout = false;
};

struct Logger : public LoggerBase
{
  Logger() = default;
  Logger(const LoggerBase &l) : LoggerBase(l){};

public:
  template<typename T>
  void invoke(const T &t)
  {
    _invoke_impl(t);
  }
  /**
             * TODO int or LogLevel m.b. typecast
             */
  void supress_to_level();

private:
  void _invoke_impl();
  void _invoke_impl(const std::string &s);
};

struct LogBuilder : public LoggerBase
{
  LogBuilder() = default;

public:
  /**
             * 
             * ? maybe generics too? or string 
             * @param print: string or vector?
             * @param format: json/plaintext/csv/... in own modules
             */

  LogBuilder &set_format(const std::string &s);
  /**
             *TODO: Make generics
             *    add_outputs(
             *        {
             *            {std::out, LogLevel::All},
             *            {std::fsoutput::open("warn.log"), LogLevel::Warn},
             *            {std::string("info.log"), LogLevel::INFO},
             *            {socket::ipv4 or unix_socket} //loglevel = default
             *        }
             *    )
             */

  template<typename A, typename ... T>
  LogBuilder &add_output(const A &a, const T &... args)
  {
    _parse_output(a);
    return add_output(args...);
  };

  template<typename A>
  LogBuilder &add_output(const A &a)
  {
    _parse_output(a);
    return *this;
  };

  //            LogBuilder& add_output(const std::string &s);
  /**
             *TODO: Make generics
             *    set_callback(
             *        {
             *            {[](){std::out<<"callback"}, LogLevel::All}
             *            {some_func(int a, float b, ...)} //loglevel = default
             *        }
             *    )
             */
  void set_callbacks();
  LogBuilder &use_cout();
  LogBuilder &use_cout(const LogLevel &l);
  LogBuilder &use_cout(const std::string &s);
  //TODO: build Logger
  Logger build();

  const std::vector<LogOutput> &get_outputs() const noexcept;

private:
  void _parse_output();
  template<typename T>
  void _parse_output(const T &val)
  {
    const auto type = typeid(T).name();
    throw std::invalid_argument(std::string("not available arg ").append(type).append(val));
  };
  void _parse_output(const std::string &s);
  void _parse_output(const std::pair<std::string, std::string> &t);
  void _parse_output(const std::pair<std::string, LogLevel> &t);
  void _parse_output(const std::string &file, const LogLevel &level);
};
}// namespace QLog
