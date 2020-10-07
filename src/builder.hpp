#include <vector>
#include <utility>
#include <iostream>
#include <string>

namespace QLog
{
    enum class LogLevel { OFF, FATAL, ERROR, WARN, DEBUG, INFO, ALL }; 

    struct LoggerBase
    {
        LoggerBase();
        virtual ~LoggerBase();

        private: 
            std::vector<std::pair<std::ostream, LogLevel>> _outputs = {};
            /**
             * TODO: add some default
             * like "#d #s #n" 
             * #d - date, #s - string, #n - number, ...
             * ? maybe some struct?
             */
            std::string _format = "";
    };

    struct Logger: public LoggerBase
    {
        Logger() = default;
        ~Logger() = default;

        public:
            void invoke();
            /**
             * TODO int or LogLevel m.b. typecast
             */
            void supress_to_level();
    };

    struct LogBuilder: public LoggerBase
    {
        LogBuilder() = default;
        ~LogBuilder() = default;

        public:
            /**
             * 
             * ? maybe generics too? or string 
             * @param print: string or vector?
             * @param format: json/plaintext/csv/... in own modules
             */
            void set_format();
            /**
             *TODO: Make generics
             *    set_outputs(
             *        {
             *            {std::out, LogLevel::All},
             *            {std::fsoutput::open("warn.log"), LogLevel::Warn},
             *            {std::string("info.log"), LogLevel::INFO},
             *            {socket::ipv4 or unix_socket} //loglevel = default
             *        }
             *    )
             */
            void set_outputs();
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
            Logger build() {return std::move(Logger());};
    };
}