#include <Bindings/Bindings.hpp>
#include <Bindings/DebugBindings.hpp>
#include <Debug/Console.hpp>

namespace obe::Bindings::DebugBindings
{
    void LoadConsoleMessage(kaguya::State* lua)
    {
        (*lua)["obe"]["ConsoleMessage"].setClass(
            kaguya::UserdataMetatable<Debug::ConsoleMessage>()
                .addFunction("getColor", &Debug::ConsoleMessage::getColor)
                .addFunction("getFormatedMessage", &Debug::ConsoleMessage::getFormatedMessage)
                .addFunction("getHeader", &Debug::ConsoleMessage::getHeader)
                .addFunction("getText", &Debug::ConsoleMessage::getText)
                .addFunction("setColor", &Debug::ConsoleMessage::setColor)
                .addFunction("setMessage", &Debug::ConsoleMessage::setMessage));
    }

    void LoadConsoleStream(kaguya::State* lua)
    {
        Load(lua, "obe.Identifiable");
        Load(lua, "obe.Togglable");
        (*lua)["obe"]["ConsoleStream"].setClass(
            kaguya::UserdataMetatable<Debug::ConsoleStream,
                kaguya::MultipleBase<Types::Identifiable, Types::Togglable>>()
                .addFunction("getColor", &Debug::ConsoleStream::getColor)
                .addFunction("push", &Debug::ConsoleStream::push)
                .addFunction("setColor", &Debug::ConsoleStream::setColor));
    }

    void LoadConsole(kaguya::State* lua)
    {
        (*lua)["obe"]["Console"].setClass(
            kaguya::UserdataMetatable<Debug::Console>()
                .addFunction("clearInputBuffer", &Debug::Console::clearInputBuffer)
                .addFunction("createStream", &Debug::Console::createStream)
                .addFunction("downHistory", &Debug::Console::downHistory)
                .addFunction("getInputBufferContent", &Debug::Console::getInputBufferContent)
                .addFunction("getStream", &Debug::Console::getStream)
                .addFunction("handleCommand", &Debug::Console::handleCommand)
                .addFunction("inputKey", &Debug::Console::inputKey)
                .addFunction("insertInputBufferContent", &Debug::Console::insertInputBufferContent)
                .addFunction("isVisible", &Debug::Console::isVisible)
                .addFunction("moveCursor", &Debug::Console::moveCursor)
                .addFunction("pushMessage", &Debug::Console::pushMessage)
                .addFunction("scroll", &Debug::Console::scroll)
                .addFunction("setInputBufferContent", &Debug::Console::setInputBufferContent)
                .addFunction("setVisible", &Debug::Console::setVisible)
                .addFunction("upHistory", &Debug::Console::upHistory));
    }
} // namespace obe::Bindings::DebugBindings