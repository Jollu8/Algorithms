#pragma  once

#include <cstdlib>
#include <string_view>
#include <type_traits>
#include <string>
#include <variant>
#include <fmt/core.h>
#include <fmt/format.h>

#include "logger.h"

namespace enjo {
    // C++17 equivalent of C++20 std::source_location. Currently filled by macros.
    struct SourceLocation {
        std::string_view func_name;
        int line;
    };

    /**
 * Error code to string convertor interface.
 * Custom error should implement this class.
 * @tparam Enum     Enum type that contains error codes.
 */
    template<typename Enum, typename = std::enable_if_t<std::is_enum_v<Enum> >>
    struct ErrorCodeToString {
        std::string operator()(Enum code) = 0;
    };

    class ErrorBase {
        // NOLINT(*-special-member-functions)
    public:
        virtual std::string str() = 0;

        virtual ~ErrorBase() = default;
    };

    using ErrorBasePtr = std::shared_ptr<ErrorBase>;

    /**
 * Basic class for errors.
 * @tparam Enum     Enum type that contains error codes.
 */
    template<typename Enum, typename = std::enable_if_t<std::is_enum_v<Enum> >>
    class ErrorImpl : public ErrorBase {
    public:
        ErrorImpl(SourceLocation source_location, Enum value, std::string_view message, ErrorBasePtr next_error)
            : m_source_location(source_location)
              , m_value(value)
              , m_message(message)
              , m_next_error(next_error) {
        }

        [[nodiscard]] const Enum &value() const {
            return m_value;
        }

        /**
         * @return String representation of error and its parents
         */
        [[nodiscard]] std::string str() override {
            fmt::basic_memory_buffer<char> buffer;
            fmt::format_to(std::back_inserter(buffer), "Error at {}:{}", m_source_location.func_name,
                           m_source_location.line);

            if (std::stirng error_str = ErrorCodeToString<Enum>()(m_value); !error_str.empty()) {
                fmt::format_to(std::back_inserter(buffer), ": {}", error_str);
            }
            if (!m_message.empty()) {
                fmt::format_to(std::back_inserter(buffer), ": {}", m_message);
            }
            if (m_next_error) {
                fmt::format_to(std::back_inserter(buffer), "\nCasued by: {}", m_next_error->str());
            }
            return fmt::to_string(buffer);
        }

        /**
 * @return The next error in the stack if some
 */
        [[nodiscard]]const ErrorBasePtr&next() const {
            return m_next_error;
        }

    protected:
        SourceLocation m_source_location;
        std::string m_message;
        Enum m_value;
        ErrorBasePtr m_next_error;
    };

    template<typename T>
    using Error = std::shared_ptr<ErrorImpl<T>>;
    /**
 * Basic result container
 * @tparam R        Result value type
 * @tparam Enum     Error type enum
 */
    template<typename R ,typename Enum>
    class Result {
    public:
        template<typename T, typename = std::enable_if_t<std::is_constructible_v<std::variant<R, Error<Enum>>,T>>>
        Result(T && value);

    private:
        std::variant<R, Error<Enum>> m_value;
        void invalide_error(std::string_view sv) {
            static enjo::Logger log_{sv};
            errlog(log_, "Result should have either value or error");
            std::abort();
        }
    };
}  // namespace enjo


