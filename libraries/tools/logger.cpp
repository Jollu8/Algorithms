#include "tools/logger.h"
#include "tools/defs.h"
#include "tools/utils.h"

namespace enjo {
    static constexpr std::string_view ENUM_NAMES[] = {
        "ERROR",
        "WARN",
        "INFO",
        "DEBUG",
        "TRACE",
    };

    static constexpr size_t ENUM_NAMES_NUMBER = std::size(ENUM_NAMES);

    static void log_to_file(FILE *file, LogLevel level, std::string_view message);

    const LoggerCallback Logger::LOG_TO_STDERR = LogToFile(stderr);

    static std::atomic<LogLevel> g_log_level{LOG_LEVEL_INFO};
    static std::shared_ptr<LoggerCallback> g_log_callback = std::make_shared<LoggerCallback>(Logger::LOG_TO_STDERR);

    static constexpr const char *TIME_FORMAT = "%d.%m.%Y %H:%M:%S.%f";

    void Logger::set_log_level(LogLevel level) {
        g_log_level = level;
    }

    void Logger::set_callback(LoggerCallback callback) {
        if (callback) {
            std::atomic_store(&g_log_callback, std::make_shared<LoggerCallback>(std::move(callback)));
        } else {
            std::atomic_store(&g_log_callback, std::make_shared<LoggerCallback>(LOG_TO_STDERR));
        }
    }

    void Logger::log_impl(LogLevel level, std::string_view message) const {
        auto callback = std::atomic_load(&g_log_callback);
        (*callback)(level, message);
    }

    bool Logger::is_enabled(LogLevel level) const {
        return level <= g_log_level;
    }

    LogLevel Logger::get_log_level() {
        return g_log_level;
    }

    void Logger::vlog(LogLevel level, fmt::string_view format, fmt::format_args args) const {
        if (is_enabled(level)) {
            fmt::basic_memory_buffer<char> buffer;
            constexpr std::string_view SPACE = " ";

            buffer.append(m_name);
            buffer.append(SPACE);
            fmt::detail::vformat_to(buffer, format, args);

            log_impl(level, std::string_view{buffer.data(), buffer.size()});
        }
    }

    static void log_to_file(FILE *file, LogLevel level, std::string_view message) {
        std::string_view level_str = (level >= 0 && level < ENUM_NAMES_NUMBER) ? ENUM_NAMES[level] : "UNKNOWN";
        SystemTime now = std::chrono::system_clock::now();
        std::string ts = utils::format_localtime(now, TIME_FORMAT);
        fmt::print(file, "{} {:5} [{}] {}\n", ts, level_str, enjo::utils::gettid(), message);
    };

    void Logger::LogToFile::operator()(LogLevel level, std::string_view message) {
        log_to_file(m_file, level, message);
    };
} // namespace enjo
