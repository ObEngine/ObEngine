#pragma once

#include <exception>
#include <optional>
#include <string>
#include <typeinfo>

#include <fmt/format.h>

#include <vili/config.hpp>
#include <vili/types.hpp>
#include <vili/utils.hpp>

namespace vili::exceptions
{
    class debug_info
    {
    public:
        std::string_view file;
        int line;
        std::string_view function;
        debug_info(std::string_view file, int line, std::string_view function)
            : file(file)
            , line(line)
            , function(function)
        {
        }
    };
#define VILI_EXC_INFO_WRAPPER()                                                          \
    vili::exceptions::debug_info(__FILE__, __LINE__, __FUNCTION__)
#define VILI_EXC_INFO VILI_EXC_INFO_WRAPPER()

    class base_exception : public std::exception
    {
    protected:
        std::string m_message;

    public:
        const char* what() const noexcept override;
        template <class... Args> void error(Args&&... args);
        template <class... Args> void hint(Args&&... args);
    };

    template <class exception_type> class exception : public base_exception
    {
    public:
        exception(std::string_view exception_name, debug_info info)
        {
            if constexpr (VERBOSE_EXCEPTIONS)
            {
                m_message = fmt::format("Exception [{}] occured\n", exception_name);
#if defined _DEBUG
                m_message
                    += fmt::format("  In file: '{}' (line {})\n", info.file, info.line);
                m_message += fmt::format("  In function: {}\n", info.function);
#endif
            }
            else
            {
                m_message = exception_name;
            }
        }

        exception_type& nest(const std::exception& exception)
        {
            if constexpr (VERBOSE_EXCEPTIONS)
            {
                m_message += "  Cause:\n";
                m_message += utils::string::indent(exception.what());
            }
            else
            {
                m_message += "\n" + utils::string::indent(exception.what());
            }
            return *static_cast<exception_type*>(this);
        }
    };

    inline const char* base_exception::what() const noexcept
    {
        return m_message.c_str();
    }

    template <class... Args> void base_exception::error(Args&&... args)
    {
        const std::string errorMsg = fmt::format(std::forward<Args>(args)...);
        if constexpr (VERBOSE_EXCEPTIONS)
        {
            m_message += fmt::format("  Error: {}\n", errorMsg);
        }
        else
        {
            m_message += (": " + errorMsg);
        }
    }
    template <class... Args> void base_exception::hint(Args&&... args)
    {
        const std::string hintMsg = fmt::format(std::forward<Args>(args)...);
        if constexpr (VERBOSE_EXCEPTIONS)
        {
            m_message += fmt::format("  Hint: {}\n", hintMsg);
        }
    }

    class invalid_cast : public exception<invalid_cast>
    {
    public:
        invalid_cast(std::string_view cast, std::string_view real_type, debug_info info)
            : exception("invalid_cast", info)
        {
            this->error("Tried to cast a value of type <{}> to <{}>", real_type, cast);
        }
    };

    class invalid_merge : public exception<invalid_merge>
    {
    public:
        invalid_merge(std::string_view merge_base_type, std::string_view merge_type,
            debug_info info)
            : exception("invalid_merge", info)
        {
            this->error("Tried to merge a value of type <{}> with a value of type <{}>",
                merge_base_type, merge_type);
        }
    };

    class unknown_child_node : public exception<unknown_child_node>
    {
    public:
        std::string key;
        unknown_child_node(std::string_view key, debug_info info)
            : exception("unknown_child_node", info)
            , key(key)
        {
            this->error("Tried to access non-existent child node '{}'", key);
        }
    };

    class array_index_overflow : public exception<array_index_overflow>
    {
    public:
        array_index_overflow(size_t index, size_t maximum, debug_info info)
            : exception("array_index_overflow", info)
        {
            this->error(
                "Tried to access element {} of an array of size {}", index, maximum);
        }
    };

    class invalid_data_type : public exception<invalid_data_type>
    {
    public:
        invalid_data_type(debug_info info)
            : exception("invalid_data_type", info)
        {
            this->error("data_type is not a known value");
        }
    };

    class inconsistent_indentation : public exception<inconsistent_indentation>
    {
    public:
        inconsistent_indentation(
            int64_t indent_level, int64_t base_indentation, debug_info info)
            : exception("inconsistent_indentation", info)
        {
            this->error("Line uses an inconsistent level of indentation ({}) where base "
                        "indentation is {}",
                indent_level, base_indentation);
        }
    };

    class too_much_indentation : public exception<too_much_indentation>
    {
    public:
        too_much_indentation(int64_t indent_level, debug_info info)
            : exception("too_much_indentation", info)
        {
            this->error(
                "Block with {} levels of indentation is too indented", indent_level);
        }
    };

    class parsing_error : public exception<parsing_error>
    {
    public:
        parsing_error(
            std::string_view source, size_t line, size_t column, debug_info info)
            : exception("parsing_error", info)
        {
            this->error("Error while parsing vili content '{}' (line {} column {})",
                source, line, column);
        }
    };

    class invalid_node_type : public exception<invalid_node_type>
    {
    public:
        invalid_node_type(std::string_view node_type, debug_info info)
            : exception("invalid_node_type", info)
        {
            this->error("'{}' is not a valid node_type", node_type);
        }
    };

    class file_not_found : public exception<file_not_found>
    {
    public:
        file_not_found(std::string_view path, debug_info info)
            : exception("file_not_found", info)
        {
            this->error("Could not open file located at '{}'", path);
        }
    };

    class integer_dump_error : public exception<integer_dump_error>
    {
    public:
        integer_dump_error(vili::integer value, debug_info info)
            : exception("integer_dump_error", info)
        {
            this->error("Could not dump integer value : [{}]", value);
        }
    };

    class number_dump_error : public exception<number_dump_error>
    {
    public:
        number_dump_error(vili::number value, debug_info info)
            : exception("number_dump_error", info)
        {
            this->error("Could not dump number value : [{}]", value);
        }
    };
}