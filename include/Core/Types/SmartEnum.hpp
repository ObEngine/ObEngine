#pragma once

#include <algorithm>
#include <ostream>
#include <vector>

#include <fmt/format.h>
#include <magic_enum/magic_enum.hpp>

#include <Exception.hpp>

namespace obe::Types
{
    class UnknownEnumEntry : public Exception<UnknownEnumEntry>
    {
    public:
        using Exception::Exception;
        UnknownEnumEntry(std::string_view enum_name, std::string_view entry_name,
            const std::vector<std::string>& all_entries, DebugInfo info)
            : Exception(info)
        {
            this->error("Enum '{}' does not have entry '{}'", enum_name, entry_name);
            std::vector<std::string> suggestions
                = Utils::String::sort_by_distance(entry_name.data(), all_entries, 5);
            std::ranges::transform(suggestions
                , suggestions.begin(), Utils::String::quote);
            suggestions.emplace_back("...");
            this->hint("Try one of ({})", fmt::join(suggestions, ", "));
        }
    };

    template <class Enum>
    class SmartEnum
    {
    public:
        [[nodiscard]] static std::string name();
        [[nodiscard]] static Enum from_string(const std::string& value);
        [[nodiscard]] static std::string to_string(Enum value);
        [[nodiscard]] static std::vector<std::string> entries();

        friend std::ostream& operator<<(std::ostream& os, const Enum& value)
        {
            os << SmartEnum<Enum>::name() << "::" << SmartEnum<Enum>::to_string(value);
            return os;
        }
    };

    template <class Enum>
    std::string SmartEnum<Enum>::name()
    {
        return magic_enum::enum_type_name<Enum>();
    }

    template <class Enum>
    Enum SmartEnum<Enum>::from_string(const std::string& value)
    {
        auto enum_value = magic_enum::enum_cast<Enum>(value);
        if (enum_value.has_value())
        {
            return enum_value.value();
        }

        throw UnknownEnumEntry(magic_enum::enum_type_name<Enum>(), value, SmartEnum<Enum>::entries(),  EXC_INFO);
    }

    template <class Enum>
    std::string SmartEnum<Enum>::to_string(Enum value)
    {
        return magic_enum::enum_name(value).data();
    }

    template <class Enum>
    std::vector<std::string> SmartEnum<Enum>::entries()
    {
        constexpr auto enum_names = magic_enum::enum_names<Enum>();
        std::vector<std::string> enum_names_vec;
        enum_names_vec.reserve(enum_names.size());
        for (const auto& enum_name : enum_names)
        {
            enum_names_vec.push_back(enum_name.data());
        }
        return enum_names_vec;
    }
}
