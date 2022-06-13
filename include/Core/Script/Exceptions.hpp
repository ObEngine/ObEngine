#pragma once

#include <fmt/format.h>
#include <string_view>

#include <Exception.hpp>

namespace obe::script::exceptions
{
    class NoSuchComponent : public Exception<NoSuchComponent>
    {
    public:
        using Exception::Exception;
        NoSuchComponent(std::string_view component_type, std::string_view object_type,
            std::string_view object_id, DebugInfo info)
            : Exception(info)
        {
            this->error("GameObject '{}' (type: '{}') has no {} component", object_id, object_type,
                component_type);
            this->hint("Try to check in the {}.obj.vili if you correctly created the "
                       "{} section",
                object_type, component_type);
        }
    };

    class ObjectDefinitionNotFound : public Exception<ObjectDefinitionNotFound>
    {
    public:
        using Exception::Exception;
        ObjectDefinitionNotFound(std::string_view object_type, DebugInfo info)
            : Exception(info)
        {
            this->error(
                "Can't find a GameObject Definition File for GameObjects of type '{}'", object_type);
            this->hint("Try to check if there is a file named "
                       "GameObject/{0}/{0}.obj.vili",
                object_type);
        }
    };

    class ScriptFileNotFound : public Exception<ScriptFileNotFound>
    {
    public:
        using Exception::Exception;
        ScriptFileNotFound(std::string_view object_type, std::string_view object_id,
            std::string_view script_path, DebugInfo info)
            : Exception(info)
        {
            this->error("GameObject '{}' of type '{}' tried to load script file at path "
                        "'{}' but could not find it",
                object_id, object_type, script_path);
        }
    };

    class WrongSourceAttributeType : public Exception<WrongSourceAttributeType>
    {
    public:
        using Exception::Exception;
        WrongSourceAttributeType(std::string_view object_type, std::string_view attribute_name,
            std::string_view expected_type, std::string_view real_type, DebugInfo info)
            : Exception(info)
        {
            this->error("GameObject '{}' tried to use attribute '{}' as a '{}' where it "
                        "should be a '{}'",
                object_type, attribute_name, real_type, expected_type);
        }
    };

    class InvalidScript : public Exception<InvalidScript>
    {
    public:
        using Exception::Exception;
        InvalidScript(std::string_view path, std::string_view error, DebugInfo info)
            : Exception(info)
        {
            this->error("Lua Error encountered while loading script at '{}' : {}", path, error);
        }
    };

    class GameObjectScriptError : public Exception<GameObjectScriptError>
    {
    public:
        using Exception::Exception;
        GameObjectScriptError(std::string_view object_type, std::string_view object_id,
            std::string_view callback, DebugInfo info)
            : Exception(info)
        {
            this->error("Lua Error encountered while executing callback '{}' of "
                        "GameObject '{}' of type '{}'",
                callback, object_id, object_type);
        }
    };

    class LuaExecutionError : public Exception<LuaExecutionError>
    {
    public:
        using Exception::Exception;
        LuaExecutionError(const std::exception& err, DebugInfo info)
            : Exception(info)
        {
            this->error("Lua encountered an error");
            this->nestInPlace(err);
        }
    };

    class LuaNestedExceptionError : public Exception<LuaNestedExceptionError>
    {
    public:
        using Exception::Exception;
        LuaNestedExceptionError(const std::exception& err, DebugInfo info)
            : Exception(info)
        {
            this->error("An exception occured while trying to retrieve the previous exception");
            this->nestInPlace(err);
        }
    };
}
