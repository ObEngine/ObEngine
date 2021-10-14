#pragma once

#include <exception>
#include <string>

#include <fmt/core.h>

#include <Utils/StringUtils.hpp>

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
    constexpr auto getTypeName() -> std::string_view
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
        constexpr auto prefix = std::string_view { "getTypeName<" };
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
        void error(Args&&... args);
        /**
         * \nobind
         */
        template <class... Args>
        void hint(Args&&... args);
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
        ExceptionType nest(BaseException& exception);
    };

    inline BaseException::BaseException(const std::exception& e) noexcept
        : m_message(e.what())
    {
    }

    template <class ExceptionType>
    Exception<ExceptionType>::Exception(DebugInfo info)
    {
        m_message = fmt::format("Exception [{}] occured\n", getTypeName<ExceptionType>());
        m_message += fmt::format("  In file: '{}' (line {})\n", info.file, info.line);
        m_message += fmt::format("  In function: {}\n", info.function);
    }

    template <class... Args>
    void BaseException::error(Args&&... args)
    {
        const std::string errorMsg = fmt::format(std::forward<Args>(args)...);
        m_message += fmt::format("  Error: {}\n", errorMsg);
#if defined(_DEBUG)
        fprintf(stderr, "%s", m_message.c_str());
#endif
    }

    template <class... Args>
    void BaseException::hint(Args&&... args)
    {
        const std::string hintMsg = fmt::format(std::forward<Args>(args)...);
        m_message += fmt::format("  Hint: {}\n", hintMsg);
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
        ExceptionType nestedException(*this);
        nestedException.m_traceback = std::vector { std::runtime_error(exception.what()) };
        nestedException.m_message += "  Cause:\n";
        nestedException.m_message
            += "    " + Utils::String::replace(exception.what(), "\n", "\n    ");
        return nestedException;
    }

    template <class ExceptionType>
    ExceptionType Exception<ExceptionType>::nest(BaseException& exception)
    {
        ExceptionType nestedException(*this);
        const std::vector<std::runtime_error>& traceback = exception.traceback();
        nestedException.m_traceback = std::vector(traceback.begin(), traceback.end());
        nestedException.m_traceback.push_back(std::runtime_error(exception.what()));
        nestedException.m_message += "  Cause:\n";
        nestedException.m_message
            += "    " + Utils::String::replace(exception.what(), "\n", "\n    ");
        return nestedException;
    }
}
