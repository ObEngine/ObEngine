#pragma once

#include <exception>
#include <string>

#include <fmt/core.h>

#include <Utils/StringUtils.hpp>
#include <Utils/TypeUtils.hpp>

namespace obe
{
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
        explicit Exception(std::source_location location);
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
    Exception<ExceptionType>::Exception(std::source_location location)
    {
        m_message = fmt::format(
            "Exception [{}] occured\n", obe::utils::types::get_type_name<ExceptionType>());
#if defined _DEBUG
        m_message
            += fmt::format("  In file: '{}' (line {})\n", location.file_name(), location.line());
        m_message += fmt::format("  In function: {}\n", location.function_name());
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
