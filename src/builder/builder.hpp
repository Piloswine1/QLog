#include <fstream>
#include <iostream>
#include <variant>
#include <algorithm>
#include <vector>
#include <memory>

namespace QLog
{
    enum class LogLevel { OFF, FATAL, ERROR, WARN, DEBUG, INFO, ALL };

    struct LoggerBase
    {
        typedef std::pair<std::shared_ptr<std::ostream*>, LogLevel> LogOutput;
        LoggerBase();
        virtual ~LoggerBase();

        protected:
            const std::array<std::string, 7> LogLevelNames = { "OFF", "FATAL", "ERROR", "WARN", "DEBUG", "INFO", "ALL"};
            LogLevel LogEnumFromString(const std::string &s) const;
            void _close_outputs();
            std::vector<LogOutput> _outputs;
    };

    struct Logger: public LoggerBase
    {
        Logger() = default;
        Logger(const LoggerBase &l): LoggerBase(l) {};

        public:
        template<typename ...T>
            void invoke(const T &...args) const;
            /**
             * TODO int or LogLevel m.b. typecast
             */
            void supress_to_level();
        private:
            void _invoke_impl();
            void _invoke_impl(const std::string &s);
    };

    struct LogBuilder: public LoggerBase
    {
        LogBuilder() = default;

        public:
            /**
             * 
             * ? maybe generics too? or string 
             * @param print: string or vector?
             * @param format: json/plaintext/csv/... in own modules
             */

            LogBuilder& set_format(const std::string &s);
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

            template<typename ...T>
            LogBuilder& add_output(const T &...args);



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
            //TODO: build Logger
            Logger build();

            const std::vector<LogOutput>& get_outputs() const noexcept;

        private:
            void _parse_output();
            template<typename ...T>
            void _parse_output(const T &...val);
            void _parse_output(const std::string &s);
            void _parse_output(std::ostream *s);
            void _parse_output(const std::pair<std::string, std::string> &t);
            void _parse_output(const std::pair<std::string, LogLevel> &t);
            void _parse_output(const std::pair<std::ostream*, LogLevel> &t);
            void _parse_output(std::ostream *s, const LogLevel &l);
    };
}
