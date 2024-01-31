#pragma once

#include <functional>
#include  <string>
#include <string_view>
#include <typeinfo>

#include <fmt/format.h>

namespace enjo {
    enum LogLevel {
        LOG_LEVEL_ERROR,
        LOG_LEVEL_WARN,
        LOG_LEVEL_INFO,
        LOG_LEVEL_DEBUG,
        LOG_LEVEL_TRACE
    };

    using LoggerCallback = std::function<void(LogLevel level, std::string_view formatted_message)>;

    class Logger {
    public:
#if _MSC_VER >= 1938
        template <typename... Ts>
        inline void log(LogLevel level, fmt::string_view fmt, Ts&&... args) const {
            vlog(level, fmt, fmt::make_format_args(args...));
        }
#else
        template<typename... Ts>
        [[clang::optnone]]
        inline void log(const LogLevel LEVEL, fmt::format_string<Ts...> fmt, Ts &&... args) const {
            vlog(LEVEL, fmt::string_view(fmt), fmt::make_format_args(args...));
        }
#endif
        explicit Logger(const std::string_view NAME): m_name(NAME) {
        }

        [[nodiscard]] bool is_enabled(LogLevel level) const;

        /**
        * Default logger callback implementation
        */
        static const LoggerCallback LOG_TO_STDERR;

        static void set_log_level(LogLevel level);

        static LogLevel get_log_level();

        static void set_callback(LoggerCallback callback);

        class LogToFile {
        public:
            explicit LogToFile(FILE *file) : m_file(file) {
            }

            void operator()(LogLevel level, std::string_view message);

        private:
            FILE *m_file;
        };

    private:
        std::string m_name;

        void vlog(LogLevel level, fmt::string_view format, fmt::format_args args) const;

        void log_impl(LogLevel level, std::string_view message) const;
    };

    template<typename T>
    static std::string typename_name_to_string(T &t) {
        return std::string(typeid(t).name());
    }


#define errlog(l, fmt_, ...) (l).log(::ag::LOG_LEVEL_ERROR, FMT_STRING("{}: " fmt_), ::fmt::string_view{__func__}, ##__VA_ARGS__)
#define warnlog(l, fmt_, ...) (l).log(::ag::LOG_LEVEL_WARN, FMT_STRING("{}: " fmt_), ::fmt::string_view{__func__}, ##__VA_ARGS__)
#define infolog(l, fmt_, ...) (l).log(::ag::LOG_LEVEL_INFO, FMT_STRING("{}: " fmt_), ::fmt::string_view{__func__}, ##__VA_ARGS__)
#define dbglog(l, fmt_, ...) do { if ((l).is_enabled(::ag::LOG_LEVEL_DEBUG)) (l).log(::ag::LOG_LEVEL_DEBUG, FMT_STRING("{}: " fmt_), ::fmt::string_view{__func__}, ##__VA_ARGS__); } while(0)
#define tracelog(l, fmt_, ...) do { if ((l).is_enabled(::ag::LOG_LEVEL_TRACE)) (l).log(::ag::LOG_LEVEL_TRACE, FMT_STRING("{}: " fmt_), ::fmt::string_view{__func__}, ##__VA_ARGS__); } while(0)
} // namespace enjo
