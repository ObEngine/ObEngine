#pragma once

#include <fmt/core.h>

#include <Utils/StringUtils.hpp>
#include <exception>
#include <string>

namespace obe
{
    /**
     * \brief wrapper class containing informations about the place that threw an exception
     */
    class DebugInfo
    {
    public:
        std::string_view file;
        int line;
        std::string_view function;
        /**
         * \paramrename{function,funcname}
         */
        DebugInfo(std::string_view file, int line, std::string_view function)
            : file(file)
            , line(line)
            , function(function)
        {
        }
    };
#define EXC_INFO_WRAPPER() DebugInfo(__FILE__, __LINE__, __func__)
#define EXC_INFO EXC_INFO_WRAPPER()

    template <typename T>
    constexpr auto get_type_name() -> std::string_view
    {
#if defined(__clang__)
        constexpr auto prefix = std::string_view { "[T = " };
        constexpr auto suffix = "]";
        constexpr auto function = std::string_view { __PRETTY_FUNCTION__ };
#elif defined(__GNUC__)
        constexpr auto prefix = std::string_view { "with T = " };
        constexpr auto suffix = "; ";
        constexpr auto function = std::string_view { __PRETTY_FUNCTION__ };
#elif defined(_MSC_VER)
        constexpr auto prefix = std::string_view { "get_type_name<" };
        constexpr auto suffix = ">(void)";
        constexpr auto function = std::string_view { __FUNCSIG__ };
#else
#error Unsupported compiler
#endif

        const auto start = function.find(prefix) + prefix.size();
        const auto end = function.find(suffix);
        const auto size = end - start;

        return function.substr(start, size);
    }

    class BaseException : public std::exception
    {
    protected:
        std::string m_message;
        std::vector<std::runtime_error> m_traceback;

        void nest_in_place(const std::exception& exception);
        void nest_in_place(const BaseException& exception);

    public:
        BaseException() = default;
        /**
         * \nobind
         */
        explicit BaseException(const std::exception& e) noexcept;
        /**
         * \nobind
         */
        template <class... Args>
        void error(fmt::format_string<Args...> message, Args&&... args);
        /**
         * \nobind
         */
        template <class... Args>
        void hint(fmt::format_string<Args...> message, Args&&... args);
        [[nodiscard]] const char* what() const noexcept override;
        const std::vector<std::runtime_error>& traceback() const;
    };

    template <class ExceptionType>
    class Exception : public BaseException
    {
    public:
        using BaseException::BaseException;
        explicit Exception(DebugInfo info);
        ExceptionType nest(const std::exception& exception);
        ExceptionType nest(const BaseException& exception);
    };

    inline void BaseException::nest_in_place(const std::exception& exception)
    {
        m_traceback = std::vector { std::runtime_error(exception.what()) };
        std::string cause = "  Cause:\n";
        cause += "    " + utils::string::replace(exception.what(), "\n", "\n    ");
        m_message += cause;
        fprintf(stderr, "%s", cause.c_str());
    }

    inline void BaseException::nest_in_place(const BaseException& exception)
    {
        const std::vector<std::runtime_error>& traceback = exception.traceback();
        m_traceback = std::vector<std::runtime_error>(traceback.begin(), traceback.end());
        m_traceback.push_back(std::runtime_error(exception.what()));
        std::string cause = "  Cause:\n";
        cause += "    " + utils::string::replace(exception.what(), "\n", "\n    ");
        m_message += cause;
        fprintf(stderr, "%s", cause.c_str());
    }

    inline BaseException::BaseException(const std::exception& e) noexcept
        : m_message(e.what())
    {
    }

    template <class ExceptionType>
    Exception<ExceptionType>::Exception(DebugInfo info)
    {
        m_message = fmt::format("Exception [{}] occured\n", get_type_name<ExceptionType>());
#if defined _DEBUG
        m_message += fmt::format("  In file: '{}' (line {})\n", info.file, info.line);
        m_message += fmt::format("  In function: {}\n", info.function);
#endif
    }

    template <class... Args>
    void BaseException::error(fmt::format_string<Args...> message, Args&&... args)
    {
        const std::string error_msg = fmt::format(message, std::forward<Args>(args)...);
        m_message += fmt::format("  Error: {}\n", error_msg);
        fprintf(stderr, "%s", m_message.c_str());
    }

    template <class... Args>
    void BaseException::hint(fmt::format_string<Args...> message, Args&&... args)
    {
        const std::string hint_msg = fmt::format(message, std::forward<Args>(args)...);
        m_message += fmt::format("  Hint: {}\n", hint_msg);
    }

    inline const char* BaseException::what() const noexcept
    {
        return m_message.c_str();
    }

    inline const std::vector<std::runtime_error>& BaseException::traceback() const
    {
        return m_traceback;
    }

    template <class ExceptionType>
    ExceptionType Exception<ExceptionType>::nest(const std::exception& exception)
    {
        ExceptionType nested_exception(*this);
        nested_exception.nest_in_place(exception);
        return nested_exception;
    }

    template <class ExceptionType>
    ExceptionType Exception<ExceptionType>::nest(const BaseException& exception)
    {
        ExceptionType nested_exception(*this);
        nested_exception.nest_in_place(exception);
        return nested_exception;
    }
} // namespace obe
