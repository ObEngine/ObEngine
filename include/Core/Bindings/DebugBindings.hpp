#pragma once

namespace kaguya { class State; }

namespace obe::Bindings::DebugBindings
{
    void LoadLog(kaguya::State* lua);
}