#pragma once

#include <exception>
#include <optional>
#include <string>
#include <typeinfo>

#include <fmt/format.h>

#include <vili/config.hpp>
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
#define VILI_EXC_INFO_WRAPPER() exceptions::debug_info(__FILE__, __LINE__, __FUNCTION__)
#define VILI_EXC_INFO VILI_EXC_INFO_WRAPPER()

    class base_exception : public std::exception
    {
    };

    template <class exception_type> class exception : public base_exception
    {
    private:
        std::string m_message;

    public:
        exception(debug_info info)
        {
            std::string exception_id = utils::string::replace(typeid(exception).name(),
                "class vili::exceptions::exception<class vili::exceptions::", "");
            exception_id = utils::string::replace(exception_id, ">", "");
            if (VERBOSE_EXCEPTIONS)
            {
                m_message = fmt::format("exception [{}] occured\n", exception_id);
                m_message
                    += fmt::format("  In file: '{}' (line {})\n", info.file, info.line);
                m_message += fmt::format("  In function: {}\n", info.function);
            }
            else
            {
                m_message = exception_id;
            }
        }
        template <class... Args> void error(Args&&... args)
        {
            const std::string errorMsg = fmt::format(std::forward<Args>(args)...);
            if (VERBOSE_EXCEPTIONS)
            {
                m_message += fmt::format("  Error: {}\n", errorMsg);
            }
            else
            {
                m_message += (": " + errorMsg);
            }
        }
        template <class... Args> void hint(Args&&... args)
        {
            const std::string hintMsg = fmt::format(std::forward<Args>(args)...);
            if (VERBOSE_EXCEPTIONS)
            {
                m_message += fmt::format("  Hint: {}\n", hintMsg);
            }
        }

        const char* what() const noexcept override;
        exception_type& nest(const std::exception& exception)
        {
            if (VERBOSE_EXCEPTIONS)
            {
                m_message += "  Cause:\n";
                m_message
                    += "    " + utils::string::replace(exception.what(), "\n", "\n    ");
            }
            else
            {
                m_message += "\n    "
                    + utils::string::replace(exception.what(), "\n", "\n    ");
            }
            return *static_cast<exception_type*>(this);
        }
    };

    template <class exception_type>
    inline const char* exception<exception_type>::what() const noexcept
    {
        return m_message.c_str();
    }

    class invalid_cast : public exception<invalid_cast>
    {
    public:
        invalid_cast(std::string_view cast, std::string_view real_type, debug_info info)
            : exception(info)
        {
            this->error("Tried to cast a value of type <{}> to <{}>", real_type, cast);
        }
    };

    class invalid_merge : public exception<invalid_merge>
    {
    public:
        invalid_merge(std::string_view merge_base_type, std::string_view merge_type,
            debug_info info)
            : exception(info)
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
            : exception(info), key(key)
        {
            this->error("Tried to access non-existent child node '{}'", key);
        }
    };

    class array_index_overflow : public exception<array_index_overflow>
    {
    public:
        array_index_overflow(size_t index, size_t maximum, debug_info info)
            : exception(info)
        {
            this->error(
                "Tried to access element {} of an array of size {}", index, maximum);
        }
    };

    class invalid_data_type : public exception<invalid_data_type>
    {
    public:
        invalid_data_type(debug_info info)
            : exception(info)
        {
            this->error("data_type is not a known value");
        }
    };

    class inconsistent_indentation : public exception<inconsistent_indentation>
    {
    public:
        inconsistent_indentation(
            int64_t indent_level, int64_t base_indentation, debug_info info)
            : exception(info)
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
            : exception(info)
        {
            this->error(
                "Block with {} levels of indentation is too indented", indent_level);
        }
    };

    class unknown_template : public exception<unknown_template>
    {
    public:
        unknown_template(std::string_view template_name, debug_info info)
            : exception(info)
        {
            this->error("Unable to get template with name '{}'", template_name);
        }
    };

    class parsing_error : public exception<parsing_error>
    {
    public:
        parsing_error(
            std::string_view source, size_t line, size_t column, debug_info info)
            : exception(info)
        {
            this->error("Error while parsing vili content '{}' (line {} column {})",
                source, line, column);
        }
    };

    class invalid_node_type : public exception<invalid_node_type>
    {
    public:
        invalid_node_type(std::string_view node_type, debug_info info)
            : exception(info)
        {
            this->error("'{}' is not a valid node_type");
        }
    };
}