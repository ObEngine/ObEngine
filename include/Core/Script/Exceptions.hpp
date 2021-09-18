#pragma once

#include <fmt/format.h>
#include <string_view>

#include <Exception.hpp>

namespace obe::Script::Exceptions
{
    class NoSuchComponent : public Exception<NoSuchComponent>
    {
    public:
        using Exception::Exception;
        NoSuchComponent(std::string_view componentType, std::string_view objectType,
            std::string_view objectId, DebugInfo info)
            : Exception(info)
        {
            this->error("GameObject '{}' (type: '{}') has no {} component", objectId,
                objectType, componentType);
            this->hint("Try to check in the {}.obj.vili if you correctly created the "
                       "{} section",
                objectType, componentType);
        }
    };

    class ObjectDefinitionNotFound : public Exception<ObjectDefinitionNotFound>
    {
    public:
        using Exception::Exception;
        ObjectDefinitionNotFound(std::string_view objectType, DebugInfo info)
            : Exception(info)
        {
            this->error(
                "Can't find a GameObject Definition File for GameObjects of type '{}'",
                objectType);
            this->hint("Try to check if there is a file named "
                       "GameObject/{0}/{0}.obj.vili",
                objectType);
        }
    };

    class ScriptFileNotFound : public Exception<ScriptFileNotFound>
    {
    public:
        using Exception::Exception;
        ScriptFileNotFound(std::string_view objectType, std::string_view objectId,
            std::string_view scriptPath, DebugInfo info)
            : Exception(info)
        {
            this->error("GameObject '{}' of type '{}' tried to load script file at path "
                        "'{}' but could not find it",
                objectId, objectType, scriptPath);
        }
    };

    class WrongSourceAttributeType : public Exception<WrongSourceAttributeType>
    {
    public:
        using Exception::Exception;
        WrongSourceAttributeType(std::string_view objectType,
            std::string_view attributeName, std::string_view expectedType,
            std::string_view realType, DebugInfo info)
            : Exception(info)
        {
            this->error("GameObject '{}' tried to use attribute '{}' as a '{}' where it "
                        "should be a '{}'",
                objectType, attributeName, realType, expectedType);
        }
    };

    class InvalidScript : public Exception<InvalidScript>
    {
    public:
        using Exception::Exception;
        InvalidScript(std::string_view path, std::string_view error, DebugInfo info)
            : Exception(info)
        {
            this->error(
                "Lua Error encountered while loading script at '{}' : {}", path, error);
        }
    };

    class GameObjectScriptError : public Exception<GameObjectScriptError>
    {
    public:
        using Exception::Exception;
        GameObjectScriptError(std::string_view objectType, std::string_view objectId, std::string_view callback, DebugInfo info) : Exception(info)
        {
            this->error("Lua Error encountered while executing callback '{}' of "
                        "GameObject '{}' of type '{}'",
                callback, objectId, objectType);
        }
    };

    class LuaExecutionError : public Exception<LuaExecutionError>
    {
    public:
        using Exception::Exception;
        LuaExecutionError(std::string_view errorMessage, DebugInfo info)
            : Exception(info)
        {
            this->error(
                "Lua encountered an error while executing code :\n{}", errorMessage);
        }
    };
}