#pragma once

#include <algorithm>
#include <ostream>
#include <vector>

#include <magic_enum/magic_enum.hpp>

#include <Exception.hpp>

namespace obe::Types
{
    class UnknownEnumEntry : public Exception<UnknownEnumEntry>
    {
    public:
        using Exception::Exception;
        UnknownEnumEntry(std::string_view enumName, std::string_view entryName,
            const std::vector<std::string>& allEntries, DebugInfo info)
            : Exception(info)
        {
            this->error("Enum '{}' does not have entry '{}'", enumName, entryName);
            std::vector<std::string> suggestions
                = Utils::String::sortByDistance(entryName.data(), allEntries, 5);
            std::transform(
                suggestions.begin(), suggestions.end(), suggestions.begin(), Utils::String::quote);
            suggestions.emplace_back("...");
            this->hint("Try one of ({})", fmt::join(suggestions, ", "));
        }
    };

    template <class Enum>
    class SmartEnum
    {
    public:
        [[nodiscard]] static std::string name();
        [[nodiscard]] static Enum fromString(const std::string& value);
        [[nodiscard]] static std::string toString(Enum value);
        [[nodiscard]] static std::vector<std::string> entries();

        friend std::ostream& operator<<(std::ostream& os, const Enum& value)
        {
            os << SmartEnum<Enum>::name() << "::" << SmartEnum<Enum>::toString(value);
            return os;
        }
    };

    template <class Enum>
    std::string SmartEnum<Enum>::name()
    {
        return magic_enum::enum_type_name<Enum>();
    }

    template <class Enum>
    Enum SmartEnum<Enum>::fromString(const std::string& value)
    {
        auto enumValue = magic_enum::enum_cast<Enum>(value);
        if (enumValue.has_value())
        {
            return enumValue.value();
        }

        throw UnknownEnumEntry(magic_enum::enum_type_name<Enum>(), value, SmartEnum<Enum>::entries(),  EXC_INFO);
    }

    template <class Enum>
    std::string SmartEnum<Enum>::toString(Enum value)
    {
        return magic_enum::enum_name(value).data();
    }

    template <class Enum>
    std::vector<std::string> SmartEnum<Enum>::entries()
    {
        constexpr auto enumNames = magic_enum::enum_names<Enum>();
        std::vector<std::string> enumNamesVec;
        enumNamesVec.reserve(enumNames.size());
        for (const auto& enumName : enumNames)
        {
            enumNamesVec.push_back(enumName.data());
        }
        return enumNamesVec;
    }
}
