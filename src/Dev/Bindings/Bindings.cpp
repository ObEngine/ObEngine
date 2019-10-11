#include <Bindings/Bindings.hpp>
#include <Bindings/DebugBindings.hpp>
#include <Bindings/EditorBindings.hpp>

namespace obe::Bindings
{
    void IndexBindings()
    {
        IndexBaseBindings();

        BindTree["obe"]
            // Debug
            .add("Console", &DebugBindings::LoadConsole)
            .add("ConsoleMessage", &DebugBindings::LoadConsoleMessage)
            .add("ConsoleStream", &DebugBindings::LoadConsoleStream)
            // Editor
            .add("EditorGrid", &EditorBindings::LoadEditorGrid);

        IndexPluginsBindings();
    }
} // namespace obe::Bindings